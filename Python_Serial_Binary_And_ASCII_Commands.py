#!/usr/bin/python
# use Python Version 3.8

# The following script is an example of how to update the baud rate 
# and send ASCII commands as well as serial binary commands to a 
# Copley Controls servo drive.

# To change baud rate:
#     1. Set baud rate of python to 9600.
#  	  2. Break(True); Sleep 50ms; Break(False);
#     3. Port.Flush;
#     4. Send ASCII command to change baud rate in drive. “s r0x90 115200”
#     5. Sleep 200ms.
#     6. Port.Flush; 
#     7. Set baud rate of python to 115200.

from math import sqrt, ceil
import serial, time

def main():

    ser = serial.Serial('COM4', baudrate=9600, timeout= 0.1)
    print("Drive Connected at 9600 baud")

    # Get Baud Rate
    SendAsciiCmd(ser, 'g r0x90')

    ser.break_condition = True
	
    # sleep for 50 milliseconds.
    time.sleep(0.05)

    ser.break_condition = False

    # flush the serial port.
    ser.flush()

    # send ASCII command to change the baud rate in the drive.
    SendAsciiCmd(ser, 's r0x90 115200')

    # sleep for 200 milliseconds.
    time.sleep(.2)
	
    # flush the serial port.
    ser.flush()
	
    # Update Python's baud rate
    ser.baudrate = 115200

    # Get Baud Rate
    SendAsciiCmd(ser, 'g r0x90')

    # Disable the drive
    SendAsciiCmd(ser, 's r0x24 0')  # Set Desired State = 0

    # Clear latched encoder faults
    # SendAsciiCmd(ser, 'enc clear') # only available on absolute encoders

    # Clear latched fault status register
    SendAsciiCmd(ser, 's r0xa4 0xffff')

    # Enable the drive by setting the Desired State to Software Position Programmed Mode
    SendAsciiCmd(ser, 's r0x24 21')

    # Set the Trajectory Configuration to Velocity Mode
    SendAsciiCmd(ser, 's r0xc8 2')

    # Send a serial binary command using a byte array.
    # Delete CVM Sequence 0 by sending 00 4f 02 14 00 03 00 00
    packet = bytearray([0x00, 0x4f, 0x02, 0x14, 0x00, 0x03, 0x00, 0x00])
    
    print("Sending serial binary command to delete CVM Sequence 0")
    ser.write(packet)
    print("Serial binary command sent")
    ReadSerialBinaryResponse(ser)
	
    ser.close()

# Send an ASCII command and return the drive's response
def SendAsciiCmd(ser, cmd):
    cmd = cmd + '\r'
    ser.write(cmd.encode())
    print("ASCII Cmd Sent: " + cmd)
    return SerReadASCIIResponse(ser)

# Collects all ASCII responses from drive
def SerReadASCIIResponse(ser):
    ret = ser.readline()
    if(len(ret) > 0):
        retStr = str(ret) # "b'ok\r" is typical response. We want to remove everything except "ok"
        retStr = retStr[2:(len(retStr) - 3)]  # chop off the 'b at beginning and carriage return (\r) at end
        print("ASCII Response: " + retStr)
        return(retStr)

# Collects all serial binary response data
def ReadSerialBinaryResponse(ser):
    ret = []
    while (True):
        ch = ser.read(1)
        if (len(ch) < 1 or ch == '\r'):
            print("Serial Binary Response: " + (" ".join(ret)))
            return(ret)
        ch = ch.hex()
        ret.append(ch)

main()
