// CopleySerial.h
// This file contains the class definition of SerialExample.
// 
// The class contains methods and variables used to establish connection
// with a serial port. Additionally, methods for sending and receiving 
// ASCII/serial binary commands and setting the baud rate are declared in this
// file.
// 
// Member variables portName and baudRate are given values based on a local 
// configuration and should be adjusted as needed before runtime.  
//

#pragma once
#include <iostream>
#include <string>
#include <list>
#include <windows.h>
#include <iomanip>
using namespace std;

class SerialExample
{
public:
	SerialExample();
	SerialExample(string comm, int baud);
	~SerialExample();
	void sendAsciiCommand(string s);
	void sendSerialBinaryCommand(const char* sbCommand);
	void setBaudRate(int rate);
	void getBaudRate();
	void openSerialPort();
	void closeSerialPort();

private:
	HANDLE hSerial;					// Handle that is used to communicate to the serial port
	string portName;	// Name of the serial port
	DCB dcbSerialParams;			// A struct containing settings for our Serial Port
	COMMTIMEOUTS timeouts;			// A struct containing specifications for timeouts
	bool breakCondition = false;
	DWORD baudRate;	// Default baud rate of Copley drives on power cycle or startup

	string readAsciiResponse();		// Method called by sendAsciiCommand()
	void readSerialBinaryResponse(const char* sbCommand);	// Method called by sendSerialBinaryCommand()
};


