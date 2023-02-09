// CopleySerial.cpp : 
// This file contains definitions of the member functions of the SerialExample class
// which is defined in the file "CopleySerial.h"

#include "CopleySerial.h"

// SerialExample default constructor
SerialExample::SerialExample()
{
	portName = "COM3";
	baudRate = 9600;

	cout << "Opening serial port...";
	this->openSerialPort();
	cout << "OK\n";
}

// Copy constructor so that we can assign baud rate and comm port in main()
SerialExample::SerialExample(string comm, int baud)
{
	this->portName = comm;
	this->baudRate = baud;

	cout << "Opening serial port...";
	this->openSerialPort();
	cout << "OK\n";
}

// SerialExample deconstructor
SerialExample::~SerialExample()
{
	cout << "Closing serial port...";
	this->closeSerialPort();
	cout << "OK\n";
}

void SerialExample::openSerialPort()
{
	// Convert the port name to LPCWSTR so that CreateFile will accept it as an argument
	wstring temp = wstring(portName.begin(), portName.end());
	LPCWSTR commPort = temp.c_str();

	// Open the serial port
	hSerial = CreateFile(commPort, GENERIC_READ | GENERIC_WRITE,
		0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_TEMPORARY, 0);
	if (hSerial == INVALID_HANDLE_VALUE) {
		if (GetLastError() == ERROR_FILE_NOT_FOUND) {
			//serial port does not exist. Inform user.
			cout << "Serial port " << portName << " not found.\n";
			exit(1);
		}
		//some other error occurred. Inform user.
	}
	else
	{
		//cout << "OK\n";
		Sleep(1000);
	}

	// Configure the serial port settings according to Copley defaults
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (!GetCommState(hSerial, &dcbSerialParams)) {
		//error getting state
		cout << "Error getting serial port state\n";
		exit(1);
	}

	// User should adjust this value before runtime if their drive is using a different baud rate
	dcbSerialParams.BaudRate = this->baudRate;	// Default = 9600 baud

	// Do NOT adjust these settings
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;

	if (!SetCommState(hSerial, &dcbSerialParams)) {
		//error setting serial port state
		cout << "Error setting serial port state\n";
		exit(1);
	}

	// Configure timeouts (in milliseconds) 
	timeouts.ReadIntervalTimeout = 100;
	timeouts.ReadTotalTimeoutConstant = 100;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 100;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	if (!SetCommTimeouts(hSerial, &timeouts)) {
		//error occureed. Inform user
		cout << "Error setting timeouts for " << portName << endl;
		exit(1);
	}

}

void SerialExample::closeSerialPort()
{
	// Close the handle when we're done. 
	if (!CloseHandle(hSerial))
	{
		cout << "Error closing serial port " << portName << endl;
		exit(1);
	}
}

// Send command in ASCII format
void SerialExample::sendAsciiCommand(string s)
{
	string asciiCommand = s;
	string response = "";
	asciiCommand.append("\r"); // Necessary formatting to send the ASCII command
	DWORD bytesWritten = 0;
	int temp = asciiCommand.length();

	cout << "ASCII cmd sent: " << s << endl;
	while (WriteFile(hSerial, asciiCommand.c_str(), temp, &bytesWritten, NULL))
	{
		if (this->breakCondition)	// Only enter this conditional if we are issuing a change to the baud rate
		{
			Sleep(200);
			this->closeSerialPort(); // Force a flush of the serial port by closing the handle (and thus severing comms)
			this->openSerialPort();	// Reopen the port and reestablish comms at the new baud rate

			this->breakCondition = false;
			Sleep(100);
			continue;	// Don't read the response yet, as we will not be able to understand it
		}
		response = readAsciiResponse();	// Continue polling the drive until we get something back

		// Did we actually get anything back?
		if (!response.empty())
		{
			cout << "ASCII response: ";
			cout << response << endl;
			return;
		}
	}

	// Should never get here
	cout << "Error sending ASCII command\n";
	return;
}

// Called by SendAsciiCommand, receives the response from the drive in ASCII format
string SerialExample::readAsciiResponse()
{
	char sBuff[32 + 1] = { 0 };		// Buffer must be null-terminated, so the 32-bit response is stored with one element left over
	DWORD bytesRead = 0;
	string asciiResponse = "";
	string temp = "";
	string baudRate = "";

	if (!ReadFile(hSerial, sBuff, 32, &bytesRead, NULL))
	{
		return "Error reading ASCII response\n";
	}
	else
	{
		for (int i = 0; i < bytesRead; i++)
		{
			temp = sBuff[i];
			asciiResponse += temp;
		}
	}

	return asciiResponse;
}

// Send serial binary command and record the response
void SerialExample::sendSerialBinaryCommand(const char* sbCommand)
{
	char sbBuff[32 + 1] = { 0 };
	DWORD bytesWritten = 0;
	int temp = sizeof(sbCommand);

	if (!WriteFile(hSerial, sbCommand, temp, &bytesWritten, NULL))
	{
		cout << "Error sending serial binary command\n";
		return;
	}
	else
	{
		Sleep(100);
		readSerialBinaryResponse(sbCommand);
	}

	return;
}

// Private method to poll for a response to a serial binary command
void SerialExample::readSerialBinaryResponse(const char* sbCommand)
{
	char sbBuff[32 + 1] = { 0 };
	DWORD bytesRead = 0;
	int temp = sizeof(sbCommand);

	if (!ReadFile(hSerial, sbBuff, 32, &bytesRead, NULL))
	{
		cout << "Error reading serial binary response";
		return;
	}
	else
	{
		cout << "Serial binary command sent\n";
		cout << "Response received: ";

		while (!bytesRead) // Did we actually receive anything?
		{

			if (WriteFile(hSerial, sbCommand, temp, 0, NULL))
			{
				if (ReadFile(hSerial, sbBuff, 32, &bytesRead, NULL))
				{
					continue;
				}
			}
		}

		// Use a few iomanip methods to change formatting
		// Type cast the char buffer entries to unsigned so we can change them to hex
		for (int i = 0; i < bytesRead; i++)
		{
			cout << hex << setw(2) << setfill('0') << unsigned(sbBuff[i]) << " ";
		}

		cout << endl;
	}
}

// Public method to change the baud rate
void SerialExample::setBaudRate(int rate)
{
	string command("s r0x90 ");
	command += to_string(rate);

	this->breakCondition = true;
	this->baudRate = rate;
	this->sendAsciiCommand(command);
}

// Allow users to get the current baud rate of the drive
void SerialExample::getBaudRate()
{
	string command("g r0x90");
	this->sendAsciiCommand(command);
}
