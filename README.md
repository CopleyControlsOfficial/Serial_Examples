# Serial_Examples
Copley drives can be controlled via serial commands. 
Serial commands can be either ASCII or serial-binary format. 
- ASCII commands are strings sent to the drive in a specific format. Please read AN139 ASCII Command Examples, which is provided in this repository (PDF). The app note demonstrates single and dual axes moves, jogging, homing, and trajectory sequencing. Also in this repository is the ASCII Programmer’s Guide (PDF).
- Serial-binary commands are byte arrays. Please read AN112 Binary Serial Interface provided in this repository to learn more about the serial-binary format (supported op-codes, checksum calculation, etc.).

Many languages support serial communication: C++, C#, Visual Basic, Python, Java, etc. 
Copley has provided a few examples found in this repository written in the following languages: C++, C#, and Python. 
The examples illustrate both ASCII and serial-binary format. 

PLEASE VISIT OUR YOUTUBE PAGE FOR LIVE DEMOS AND STEP BY STEP TUTORIALS.

- Python Serial Example Demo: https://www.youtube.com/watch?v=iuDyhDxzadk 
- Serial-Binary Checksum Calculation: https://www.youtube.com/watch?v=RXtOt6xRiT4 
- Serial-Binary over CAN: https://www.youtube.com/watch?v=SU2RYYsDMdE 
