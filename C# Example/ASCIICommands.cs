using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using System.Collections;
using System.IO.Ports;

/// <summary>
///    Developed in Visual Studio 2019.
///    The following is a C# application demonstrating how to send ASCII and serial binary commands to a Copley Controls Drive.
///    It is similar to CME's ASCII Command Line.
///    Please read the ASCII Programmer's Guide found in CME\Help\All Documents\ASCII Programmer's Guide.
/// </summary>


namespace ASCII_Commands
{
    public partial class ASCIICommands : Form
    {        
        // buffer containing the response from the drive.
        List<byte> dataReceivedList = new List<byte>();

        // the string form of the receive buffer.
        string dataReceivedString;

        // Create a delegate to close down the application in a thread safe way
        delegate void CloseApp();

        public ASCIICommands()
        {
            InitializeComponent();
            getAvailablePorts();
        }

        // retrieve the available serial ports from the system at startup.
        void getAvailablePorts()
        {            
            // populate the ports array with the names of the available serial ports
            String[] ports = SerialPort.GetPortNames();

            // append the ports the to the port names combobox
            portNameSelectionComboBox.Items.AddRange(ports);

            // link the data received event handler with the event handler function
            serialPort1.DataReceived += serialPortDataReceivedEventHandler;

            // link the key down event with the enter key pressed function.
            asciiCommandTextBox.KeyDown += sendTextBoxEnterKeyPressed;

            // set the default selected baud rate to 9600 baud.
            baudRateSelectionComboBox.SelectedItem = "9600"; // default set to 9600 baud
            
            // set the timeout value for the serial port read command.
            serialPort1.ReadTimeout = 500;

            // set the timeout value for the serial port write command.
            serialPort1.WriteTimeout = 500;
        }       

        // handles the event of data received over the serial port.
        private void serialPortDataReceivedEventHandler(object sender, SerialDataReceivedEventArgs e)
        {
            // while there is data received by the serial port, append it to the buffer.
            while (serialPort1.BytesToRead > 0)
            {
                dataReceivedList.Add((byte)serialPort1.ReadByte());
            }
            
            // NEXT TWO LINES FOR ASCII RESPONSE
            ASCIIEncoding encoding = new ASCIIEncoding(); // ASCII response. Comment this line for serial binary response.
            dataReceivedString = encoding.GetString(dataReceivedList.ToArray()); // ASCII response. Comment this line for serial binary response.

            // COMMENT PREVIOUS TWO LINES (ASCII RESPONSE) AND UNCOMMENT 
            // NEXT TWO LINES TO DISPLAY SERIAL BINARY RESPONSE IN GUI
            /*
            dataReceivedList.ToString();
            dataReceivedString = string.Join(" ", dataReceivedList);
            */

            // invoke the ShowData function, which updates the GUI.
            this.Invoke(new EventHandler(displayResponseFromDrive));
        }

        // display the response from the drive to the data received text box
        private void displayResponseFromDrive(object sender, EventArgs e)
        {
            // sleep for 100 milliseconds to allow all of the data to be received.
            Thread.Sleep(100);

            // do not display garbage
            if(dataReceivedString == "?")
            {
                dataReceivedString = "";
            }

            // display the data in the dataIN byte array.
            dataRecievedTextBox.Text = dataReceivedString;              
        }

        // user closed the application.
        private void ASCIICommands_FormClosed(object sender, FormClosedEventArgs e)
        {
            try
            {
                Environment.Exit(Environment.ExitCode);
            }
            catch (Exception ex)
            {
                DisplayError(ex);
            }
        }

        // display the error to the user.
        public void DisplayError(Exception ex)
        {
            DialogResult errormsgbox;
            errormsgbox = MessageBox.Show("Error Message: " + ex.Message + "\n" + "Error Source: "
                + ex.Source, "Error", MessageBoxButtons.OKCancel);
            if (errormsgbox == DialogResult.Cancel)
            {
                // it is possible that this method was called from a thread other than the 
                // GUI thread - if this is the case we must use a delegate to close the application.
                //Dim d As New CloseApp(AddressOf ThreadSafeClose)
                CloseApp d = new CloseApp(ThreadSafeClose);
                this.Invoke(d);
            }
        }

        // close the application in a thread safe way.
        public void ThreadSafeClose()
        {
            //If the calling thread is different than the GUI thread, then use the
            //delegate to close the application, otherwise call close() directly
            if (this.InvokeRequired)
            {
                CloseApp d = new CloseApp(ThreadSafeClose);
                this.Invoke(d);
            }
            else
            {                
                Close();
            }
        }

        // send the data in the Send textbox to the drive.
        private void sendAsciiCommandButton_Click(object sender, EventArgs e)
        {
            try
            {
                dataReceivedList.Clear(); // clear the internal receive buffer
                
                // clear the received textbox.
                dataRecievedTextBox.Text = String.Empty;
                
                // send the ASCII command.
                serialPort1.WriteLine(asciiCommandTextBox.Text);

                // COMMENT PREVIOUS TWO LINES (ASCII Command) AND UNCOMMENT NEXT TWO LINES 
                // TO SEND SERIAL BINARY COMMAND

                /*
                // 0x00 0x45 0x01 0x14 0x00 0x0a = stop cvm program
                byte[] serial_binary_array = new byte[6] { 0x00, 0x45, 0x01, 0x14, 0x00, 0x0a };
                serialPort1.Write(serial_binary_array, 0, 6); // 0 is the offset. 6 is the size of the array.
                */                
            }
            catch(Exception ex)
            {
                DisplayError(ex);
            }
        }

        // if the user presses the enter key, perform the button click.
        private void sendTextBoxEnterKeyPressed(object sender, KeyEventArgs e)
        {
            // makes use of the Enter Key
            if (e.KeyCode == Keys.Enter)
            {
                sendAsciiCommandButton.PerformClick();
                e.SuppressKeyPress = true;
                e.Handled = true;
            }
        }

        // open the port, establishing a connection with the drive.
        private void openPortButton_Click(object sender, EventArgs e)
        {
            try
            {
                if (dataRecievedTextBox.Text == "Please select port settings")
                {
                    dataRecievedTextBox.Text = "";
                }
                if (portNameSelectionComboBox.Text == ""||baudRateSelectionComboBox.Text == "")
                {
                    dataRecievedTextBox.Text = "Please select port settings";
                }
                else
                {
                    // set the port name to the one selected in the GUI (For example: COM4).
                    serialPort1.PortName = portNameSelectionComboBox.Text;

                    // set the baud rate to the default baud rate of the drive.
                    serialPort1.BaudRate = 9600;

                    // establish a connection with the drive at 9600 baud.
                    serialPort1.Open();

                    // send the break command
                    serialPort1.BreakState = true;

                    // wait 50 milliseconds
                    Thread.Sleep(50);

                    // remove the break state
                    serialPort1.BreakState = false;

                    // flush the serial port
                    dataReceivedList.Clear();

                    // send command to drive to change to 115200
                    serialPort1.WriteLine(createBaudRateAsciiCommand(baudRateSelectionComboBox.SelectedItem));

                    // flush the serial port again
                    dataReceivedList.Clear();

                    // clear the received textbox.
                    dataRecievedTextBox.Text = String.Empty;

                    // wait for 200 milliseconds
                    Thread.Sleep(200);

                    // flush the serial port again
                    dataReceivedList.Clear();

                    // clear the received textbox.
                    dataRecievedTextBox.Text = "";

                    // set the baud rate of the drive to the one selected in the GUI.
                    serialPort1.BaudRate = Convert.ToInt32(baudRateSelectionComboBox.SelectedItem);                    
                    
                    // start the progress bar (connection monitor)
                    connectionStatusBarTimer.Start();
                }
            }
            catch(UnauthorizedAccessException)
            {
                dataRecievedTextBox.Text = "Unauthorized Access";
            }
            catch(Exception ex)
            {
                DisplayError(ex);
            }
        }

        // create ASCII command to change the baud rate (ASCII parameter 0x90).
        public string createBaudRateAsciiCommand(object inputBaudRate)
        {
            // create a string builder
            StringBuilder asciiCommand = new StringBuilder();

            // append data to the string builder
            asciiCommand.Append("s r0x90 ");

            // append the user's baud rate
            asciiCommand.Append(Convert.ToString(inputBaudRate));

            // return the properly formatted ASCII command.
            return (asciiCommand.ToString());
        }

        // user pressed the close port button.
        private void closeSerialPortButtonClick(object sender, EventArgs e)
        {
            // try to close the port.
            try
            {
                // close the serial port.
                serialPort1.Close();

                // set the status progress bar to its minimum value.
                statusProgressBar.Value = statusProgressBar.Minimum;

                // set the focus (cursor) on the ASCII command line
                asciiCommandTextBox.Focus();

                // enable/disable appropriate buttons.
                sendAsciiCommandButton.Enabled = false;
                openSerialPortButton.Enabled = true;
                closeSerialPortButton.Enabled = false;
                baudRateSelectionComboBox.Enabled = true;
                portNameSelectionComboBox.Enabled = true;
            }
            catch(Exception ex)
            {
                DisplayError(ex);
            }
        }

        // turn off the timer that handles the connection status bar.
        private void timerOFF()
        {
            // invoke the changes to the GUI, since they are not on the same 
            // thread as this one.
            this.BeginInvoke((Action)delegate ()
            {
                // stop the connection status bar
                connectionStatusBarTimer.Stop();

                // display the error to the user.
                MessageBox.Show("No Drive Detected");
                
                // close the serial port.
                serialPort1.Close();

                // set the focus (cursor) on the ASCII command line.
                asciiCommandTextBox.Focus();
            });
        }

        // handles when the user is selecting a port to open. 
        // Once a port has been opene, this timer stops.
        // When the port is closed, this timer is restarted.
        private void timer1_Tick(object sender, EventArgs e)
        {
            // if the serial port is not open, set the progress bar value to 0, and stop the timer.
            if (serialPort1.IsOpen == false)
            {
                statusProgressBar.Value = 0;
                timerOFF();
            }
            
            // The serial port is open.
            else
            {
                // set the progress bar value to its maximum value.
                statusProgressBar.Value = statusProgressBar.Maximum;
                
                // enable/disable the appropriate GUI buttons
                sendAsciiCommandButton.Enabled = true;
                asciiCommandTextBox.Enabled = true;
                openSerialPortButton.Enabled = false;
                closeSerialPortButton.Enabled = true;
                baudRateSelectionComboBox.Enabled = false;
                portNameSelectionComboBox.Enabled = false;
                
                // stop the status progress bar timer.
                connectionStatusBarTimer.Stop();

                // send the focus to (cursor) to the command line.
                asciiCommandTextBox.Focus();
            }
        }
    }
}
