#!/usr/bin/python
# use Python Version 3.8

# The following script is an example of how to send ASCII commands 
# to set the baud rate and track the time of each move segment 

from math import sqrt, ceil, pow
import serial
import time

global breakCond

def main():
    global breakCond
    ser = serial.Serial('COM12', baudrate=9600, timeout=0.1)

    print("Drive Connected")

    global error_bit
    error_bit = 0
    ser.baudrate = 9600

    # Change Baud Rate
    # 
    # Since we haven't adjusted our serial port's baud rate, the response is garbage
    # This messes with the string encoding, so we ignore the response
    breakCond = True
    SendAsciiCmd(ser, 's r0x90 115200')

    # Wait for 10 ms before we try to communicate with the drive again
    # Change the baud rate for the serial port to match that of the drive
    time.sleep(0.01)
    ser.baudrate = 115200
    
    # Check our work and that the baud rate is set
    SendAsciiCmd(ser, 'g r0x90')
    StartTime = EndTime = 0

    # Perform 5 moves back and forth the same distance
    for i in range(5):
            # Poll the drive to check Event Status Register bit 27 (in-motion)
            while(1):
                status = SendAsciiCmd(ser, 'g r0xa0')
                status = status[1:]               
                
                # perform a bitwise AND operation with 0xa0 bit 27
                # if set, this will render the statement false and loop again 
                # if the bit is not set, exit the loop
                if((int(status) & (1 << 27)) == 0):
                    EndTime = time.time()
                    print('Total time of move: ' + str(EndTime - StartTime))
                    break
                    
             
            # Load the position command into the trajectory generator
            SendAsciiCmd(ser, 's r0xca 4000')

            # Issue a trajectory update to start the move
            SendAsciiCmd(ser, 't 1')
            StartTime = time.time()
            
            # Load the same position command into the trajectory generator
            SendAsciiCmd(ser, 's r0xca -4000')

            # Poll the drive to check Event Status Register bit 27 (in-motion)
            while(1):
                status = SendAsciiCmd(ser, 'g r0xa0')
                status = status[1:]

                # Perform a bitwise AND operation with 0xa0 bit 27
                # If set, this will render the statement false and loop again 
                # If the bit is not set, exit the loop
                if((int(status) & (1 << 27)) == 0):
                    EndTime = time.time()
                    print('Total time of move: ' + str(EndTime - StartTime))
                    break
             
            # Issue trajectory update to start the move
            SendAsciiCmd(ser, 't 1')
            StartTime = time.time()                

    ser.close()

# Send an ASCII command and return the drive's response
def SendAsciiCmd(ser, cmd):
    cmd = cmd + '\r'
    ser.write(cmd.encode())
    print("ASCII Cmd Sent: " + cmd)
    return SerReadASCIIResponse(ser)

# Collects all ASCII responses from drive
def SerReadASCIIResponse(ser):
    global breakCond
    ret = ''
    while (True):
        ch = ser.read(1)
        if (breakCond):
            breakCond = False
            return ret
        if (len(ch) < 1 or str(ch, 'utf-8') == '\r'):
            print("ASCII Response: " + ret)
            return ret
        ret += str(ch, 'utf-8')

main()