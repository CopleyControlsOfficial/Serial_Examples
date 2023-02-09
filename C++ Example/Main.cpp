// Main.cpp
// This file contains examples of how to set the baud rate and send ASCII commands
// as well as serial binary commands to a Copley Controls servo drive.
// 
// To change baud rate: 
//	1. Set baud rate of SerialExample to match the drive (9600 is Copley default on powerup or reset)
//	2. Send ASCII command to change baud rate in drive -> example: "s r0x90 115200"
//	3. Sleep 200ms
//	4. Close port and reopen at new baud rate, simulating flush 
//

#include "CopleySerial.h"

int main()
{
	// Initialize our SerialExample object
	SerialExample ser = SerialExample("COM3", 9600);
	char* byteArray{};	// Buffer for serial binary commands

	Sleep(100);

	// Get the drive's baud rate
	ser.getBaudRate();

	// Set the drive's baud rate
	ser.setBaudRate(115200);

	// Get current baud rate of the drive (this time to make sure we've set the baud rate correctly)
	ser.getBaudRate();

	// ASCII command to get desired state of the drive
	ser.sendAsciiCommand("g f0x24");

	// Get the drive's event status register
	ser.sendAsciiCommand("g r0xa0");

	// Clear latched fault event register
	ser.sendAsciiCommand("s r0xa4 0xffff");

	// Serial binary command to check operational mode
	byteArray = new char[4]{ 0x00, 0x5d, 0x00, 0x07 };
	ser.sendSerialBinaryCommand(byteArray);
	delete[] byteArray; // Once we're done, free up the memory we used for the array

	// Issue trajectory update
	byteArray = new char[6]{ 0x00, 0x5b, 0x01, 0x11, 0x10, 0x01 };
	ser.sendSerialBinaryCommand(byteArray);
	delete[] byteArray;

	// Check event status register
	byteArray = new char[6]{ 0x00, char(0xf7), 0x01, 0x0c, 0x00, char(0xa0) };
	ser.sendSerialBinaryCommand(byteArray);
	delete[] byteArray;

	return 0;
}