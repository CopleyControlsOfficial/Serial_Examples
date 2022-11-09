#!/usr/bin/python
# use Python Version 3.8

from math import sqrt, ceil
import serial

# Example Python program which creates an s-curve move with different acceleration and deceleration
# values and sends the move to the drive as a PVT move using the ASCII interface

def main():
   ser = serial.Serial('COM4', baudrate = 9600, timeout = 0.1)
   
   print("Drive Connected")
   
   global error_bit
   error_bit = 0
   
   # Disable the drive 
   SendAsciiCmd(ser, 's r0x24 0') # Set Desired State = 0
   
   # Clear latched encoder faults
   # SendAsciiCmd(ser, 'enc clear')
   
   # Clear latched fault status register
   SendAsciiCmd(ser, 's r0xa4 0xffff')
   
   # Enable the drive by setting the Desired State to Software Position Programmed Mode
   SendAsciiCmd(ser, 's r0x24 21') 
   
   # Clear the trajectory buffer
   SendAsciiCmd(ser, 's r0x115 0x8000')
   
   # Get the current commanded position
   starting_position = GetCmdPos( ser )
   
   # Set the trajectory mode to 3 for PVT moves
   SendAsciiCmd( ser, 's r0xc8 3' )
   
   # Calculate the move   
   ending_position = starting_position + 10000000
   velocity = 3000000
   accel = 600000
   decel = 600000
   jerk = 120000
   pvt = CalcMove( starting_position, ending_position, velocity, accel, decel, jerk ) 
   
   '''
   # Returns list filled with PVT Points
   for s in pvt:
      print '%12.3f  %9.3f  %7.3f' % s
   '''
   
   # See how many segments will fit in the buffer right now
   # Normally this is 32 although the latest plus drive firmware allows 64
   ct = GetTrjBuff( ser ) # find the capacity of the trajectory buffer (normally 32)
   if( ct > len(pvt) ):   # if capacity is greater than the length of the list of calculated PVT Points
      ct = len(pvt)       # than the capacity will be set to be smaller and match the length of the move.
   
   # Load PVT Buffer with points
   Initial_PVT_Load(ser, pvt)
   
   # Start the move
   SendAsciiCmd(ser, 't 1')
   print("Trajectory Update Issued - T 1 Command")

   # If there are still PVT segments left to send, then just keep
   # reading the number of free spaces left in the buffer and send
   # new points to keep it full.
   
   count = 0
   while((len(pvt)>0) and (error_bit==0)):
      current_buffer_space = GetTrjBuff(ser)
      Check_In_Motion = Check_Motion(ser)
      if(current_buffer_space > 0):
         SendPVT(ser, pvt[0])
         print("PVT Point Added: ", pvt[0])
         del(pvt[0])
         count = count + 1
         if (count > 4):
            SendAsciiCmd(ser, 't 0x1004') # update trajectory generator command
            count = 0
      elif(Check_In_Motion == "NOT-IN-MOTION"):
            count = count + 1
            if(count > 4):
                SendAsciiCmd(ser, 't 0x1004')
                count = 0
                print("Attempted to begin move with no success.")
                error_bit = 1
   ser.close()
   
   # OK, all the points have been sent.  The drive is still running the
   # move, so in a real program I'd wait for the move to finish and then
   # start the next one.

def Initial_PVT_Load(ser, pvt):
   # Fill the buffer with PVT segments
   while(len(pvt)>0):
      current_buffer_space = GetTrjBuff(ser)
      if (current_buffer_space > 0):
         SendPVT( ser, pvt[0] )
         print("PVT Point sent: ", pvt[0])
         del(pvt[0])
      else:
         break

# Send an ASCII command and return the drive's response
def SendAsciiCmd( ser, cmd ):
   cmd = cmd + '\r'
   ser.write(cmd.encode())
   #print("ASCII Cmd Sent: " + cmd)
   return SerReadLine( ser )

# Collects all ASCII responses from drive
def SerReadLine(ser):
   ret = ''
   while( True ):
      ch = ser.read(1)
      if( len(ch) < 1 or ch == '\r' ):
         #print("Returned value is: " + ret)
         return ret
      ret += str(ch, 'utf-8')

# Inputs are a number and bit and function returns if the bit is set or not
# The function is indexed at 1 so In-Motion Bit (bit 27) is input as 28 here.
def isKthBitSet(n, k):
   if n & (1 << (k - 1)): 
      return( "SET") 
   else: 
      return("NOT SET") 

# Reads the In-Motion Bit to determine if motor in motion
def Check_Motion(ser):
   Event_Status_Register = SendAsciiCmd(ser, 'g r0xa0')
   Event_Status_Register = Event_Status_Register[1:].strip()
   number = int(Event_Status_Register)
   In_Motion_Bit_State = isKthBitSet(number, 28)
   if (In_Motion_Bit_State == "SET"):
      print("IN-MOTION")
      return("IN-MOTION")
   else:
      print("NOT-IN-MOTION")
      return("NOT-IN-MOTION")

# Get the current commanded position
def GetCmdPos( ser ):
   command = ('g r0x2d')
   rsp = SendAsciiCmd(ser, command)
   x = rsp.split()
   if( len(x) < 2 or x[0] != 'v' ): 
      return -1
   print("Current Commanded Position is: ", int(x[1]))
   return int(x[1])

# Read the trajectory buffer parameter and return the number of free positions in the buffer
def GetTrjBuff(ser):
   rsp = SendAsciiCmd( ser, 'g r0x115' )
   x = rsp.split()
   if( len(x) < 3 or x[0] != 'v' ): 
      return -1
   print("Number of free positions in the buffer: ", int(x[1]))
   return int(x[1])

# Send a PVT point to the drive by writing to parameter 0x115.
# When sending points to the drive, position is in encoder counts, velocity
# is in 0.1 cts/sec and time is milliseconds
def SendPVT( ser, seg ):
   P = int(round(seg[0]))
   V = int(round(seg[1]*10))
   T = int(round(seg[2]*1000))
   cmd = 's r0x115 %d %d %d' % (T,P,V)
   rsp = SendAsciiCmd( ser, cmd )
   #print ("PVT Point Sent: " + cmd)


###################################################################################
# Calculate the s-curve move using the following constraints:
#    P - move distance in encoder count units
#    V - Maximum velocity (cts/sec)
#    A - Maximum accel (cts/sec/sec)
#    D - Maximum decel (cts/sec/sec)
#    J - Jerk limit (cts/sec/sec/sec)
#
# This returns a list of the PVT segments needed to make the move.
# Each segment is a tuple of (position, velocity, time) where position
# is in counts, velocity is in cts/sec, and time is seconds.
###################################################################################
def CalcMove( starting_position, end, V, A, D, J ):

   # Make sure all the inputs are floats and not ints.  
   starting_position = float(starting_position)
   end = float(end)
   V = float(V)
   A = float(A)
   D = float(D)
   J = float(J)

   # First, some quick sanity checks
   if( V <=0 or A <=0 or D <=0 or J <=0 ):
      return None

   # Find the move distance
   P = end-starting_position;

   # Assume positive moves for simplicity.  We'll fix this in the end if necessary.
   negMove = (P<0);
   if( negMove ):
      P *= -1.0;

   if( P == 0 ):
      return [(starting_position,0,0)]

   # Make sure A <= D.  This reduces the number of tests I need to do later.  
   # I'll fix this at the end of the calculation.
   swapAD = (A > D);

   if( swapAD ):
      tmp = A; 
      A = D; 
      D = tmp;
   
   # I'll lower jerk to ensure that my jerk segments are at least 1 millisecond long.
   if( J > A*1e3 ): J = A * 1e3;
   if( J > V*1e6 ): J = V * 1e6;
   if( J > P*5e8 ): J = P * 5e8;

   # These are the key variables I'll need to find.
   #   tj = time to increase/decrease acceleration
   #   ta = time to run at constant accel
   #   tv = time to run at constant velocity
   #   td = time to run at constant decel
   #   tk = time to increase/decrease deceleration

   # First, see if a simple jerk limited move will handle this.  
   # In this case, the move will be 4 segments each of the same time.
   tj = pow( P/(2*J), 1.0/3.0 );
   if( (J*tj < A) and (J*tj*tj < V) ):
      ta = td = tv = 0;

      # Adjust time & Jerk to the next higher millisecond
      tk = tj = 0.001 * ceil( tj*1000 );

      J  = P / (2 * tj*tj*tj);

   # We know we'll hit either the accel or velocity 
   # limit.  See if the accel limit is too high.
   # If so, this must be a Jerk & Velocity move.
   elif( J*V < A*A ):
      ta = td = 0;
      tj = sqrt( V/J );

      # Adjust the times so they are integer multiples
      # of milliseconds.  I'll adjust J & V to compensate
      tk = tj = 0.001 * ceil( tj*1000 );
      tv = P/V - 2*tj;

      tv = 0.001 * ceil( tv*1000 );

      V = P / (tv + 2*tj);
      J = V / (tj*tj);

   else:
      # At this point we know we will hit the accel limit.
      # We may or may not hit the velocity & decel limits.
      # I'll start by assuming that I'll hit the velocity limit.
      tj = A/J;
      vj = A*tj / 2.0;

      ta = (V - 2*vj) / A;

      if( J*V < D*D ):
         td = 0.0;
         tk = sqrt(V/J);
         vk = V/2;
      else:
         tk = D/J;
         td = (V-J*tk*tk) / D;
         vk = D*tk / 2.0;

      # Find the distance moved getting up to and down from V
      pa = tj*vj*2 + ta*vj + A*ta*tj + ta*ta*A/2.0;
      pd = tk*vk*2 + td*vk + D*td*tk + td*td*D/2.0;

      # If this distance is less then the total move,
      # then I've found my solution.  Otherwise, the
      # velocity limit isn't reached.
      if( pa+pd <= P ):
         tv = (P-pa-pd) / V;

      else:
         #  At this point, we know we will hit the accel 
         #  limit, but not the velocity limit.  The only 
         #  question now is whether the decel limit will 
         #  be reached.
         # 
         #  I'll try no decel limit first.

         tv = 0.0;
         tk = (sqrt( sqrt(2*P*A)*4*J +A*A ) - A) / (2*J);

         if( J*tk <= D ):
            ta = (J*tk*tk - J*tj*tj) / A;
            td = 0.0;
         else:
            tk = D/J;

            a = J*A*(D+A);
            b = 3*A*A*D -2*A*D*D +2*A*A*A +3*A*D*D;
            c = (A*A + D*D + 2*A*D) * A*A/J - 2*P*J*D;

            ta = (-b + sqrt(b*b -4*a*c)) / (2*a);
            td = (J*tj*tj + A*ta - J*tk*tk)/D;

   # If I previously swapped A & D, fix that now.
   if( swapAD ):
      tmp = ta; ta = td; td = tmp;
      tmp = tj; tj = tk; tk = tmp;
      tmp =  A;  A =  D;  D = tmp;

   # Adjust for negative moves as necessary
   if( negMove ):
      P  *= -1.0;
      J  *= -1.0;

   # These are the times and jerks used for the full s-curve.
   # Note that some of the times may be zero
   time = [tj, ta, tj, tv, tk, td, tk]
   jerk = [ J,  0, -J,  0, -J,  0,  J]

   # Now build up the list of PVT segments that describe the move.
   pvt = []
   pos = starting_position;
   vel = 0; 
   acc = 0;
   T = 0
   for i in range(len(time)):
      J = jerk[i]
      T = time[i]

      T = int(round(T*1000))

      while( T > 0 ):
         # Find the time limited to 255ms which is the max I can send in one segment
         if( T > 511 ):
            t = 255
         elif( T > 255 ):
            t = T/2
         else:
            t = T

         T -= t
         t *= 0.001
            
         # Each segment consists of the starting position & velocity and the 
         # time until the beginning of the next segment.
         pvt.append( (pos, vel, t) )

         pos += vel*t + acc*t*t/2 + J*t*t*t/6;
         vel += acc*t + J*t*t/2;
         acc += J*t;

   # Add the final segment with a zero time.
   # The zero time indicates the end of the move
   pvt.append( (end, 0, 0) )

   return pvt

main()
