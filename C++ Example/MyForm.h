#pragma once
#include <windows.h>
#include <list>
#include <string>
#include <iostream>

namespace serialexample {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO::Ports;
	using namespace System::Threading;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{

			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ SendButton;
	private: System::Windows::Forms::Button^ ReadButton;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ PortsComboBox;
	private: System::Windows::Forms::ComboBox^ BaudRateComboBox;


	private: System::Windows::Forms::Label^ label2;
	private: System::IO::Ports::SerialPort^ serialPort1;
	event System::IO::Ports::SerialDataReceivedEventHandler^ DataReceived;
	private: System::Windows::Forms::Button^ OpenPortButton;
	private: System::Windows::Forms::Button^ ClosePortButton;
	private: System::Windows::Forms::TextBox^ SendDataTextBox;
	private: System::Windows::Forms::TextBox^ ReadDataTextBox;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::Label^ label4;


	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->SendButton = (gcnew System::Windows::Forms::Button());
			this->ReadButton = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->PortsComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->BaudRateComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->OpenPortButton = (gcnew System::Windows::Forms::Button());
			this->ClosePortButton = (gcnew System::Windows::Forms::Button());
			this->SendDataTextBox = (gcnew System::Windows::Forms::TextBox());
			this->ReadDataTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// SendButton
			// 
			this->SendButton->BackColor = System::Drawing::Color::Bisque;
			this->SendButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SendButton->Location = System::Drawing::Point(51, 115);
			this->SendButton->Name = L"SendButton";
			this->SendButton->Size = System::Drawing::Size(214, 44);
			this->SendButton->TabIndex = 0;
			this->SendButton->Text = L"Send";
			this->SendButton->UseVisualStyleBackColor = false;
			this->SendButton->Click += gcnew System::EventHandler(this, &MyForm::SendButton_Click);
			// 
			// ReadButton
			// 
			this->ReadButton->BackColor = System::Drawing::Color::Bisque;
			this->ReadButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ReadButton->Location = System::Drawing::Point(51, 217);
			this->ReadButton->Name = L"ReadButton";
			this->ReadButton->Size = System::Drawing::Size(214, 44);
			this->ReadButton->TabIndex = 1;
			this->ReadButton->Text = L"Read";
			this->ReadButton->UseVisualStyleBackColor = false;
			this->ReadButton->Click += gcnew System::EventHandler(this, &MyForm::ReadButton_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(379, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(45, 17);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Ports:";
			// 
			// PortsComboBox
			// 
			this->PortsComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->PortsComboBox->FormattingEnabled = true;
			this->PortsComboBox->Location = System::Drawing::Point(430, 21);
			this->PortsComboBox->Name = L"PortsComboBox";
			this->PortsComboBox->Size = System::Drawing::Size(121, 24);
			this->PortsComboBox->TabIndex = 3;
			// 
			// BaudRateComboBox
			// 
			this->BaudRateComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->BaudRateComboBox->FormattingEnabled = true;
			this->BaudRateComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"9600" });
			this->BaudRateComboBox->Location = System::Drawing::Point(430, 65);
			this->BaudRateComboBox->Name = L"BaudRateComboBox";
			this->BaudRateComboBox->Size = System::Drawing::Size(121, 24);
			this->BaudRateComboBox->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(345, 68);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(79, 17);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Baud Rate:";
			// 
			// serialPort1
			// 
			this->serialPort1->ReadTimeout = 500;
			this->serialPort1->WriteTimeout = 500;
			// 
			// OpenPortButton
			// 
			this->OpenPortButton->BackColor = System::Drawing::Color::LawnGreen;
			this->OpenPortButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->OpenPortButton->Location = System::Drawing::Point(432, 104);
			this->OpenPortButton->Name = L"OpenPortButton";
			this->OpenPortButton->Size = System::Drawing::Size(119, 60);
			this->OpenPortButton->TabIndex = 6;
			this->OpenPortButton->Text = L"Open Port";
			this->OpenPortButton->UseVisualStyleBackColor = false;
			this->OpenPortButton->Click += gcnew System::EventHandler(this, &MyForm::OpenPortButton_Click);
			// 
			// ClosePortButton
			// 
			this->ClosePortButton->BackColor = System::Drawing::Color::Red;
			this->ClosePortButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ClosePortButton->ForeColor = System::Drawing::Color::White;
			this->ClosePortButton->Location = System::Drawing::Point(432, 170);
			this->ClosePortButton->Name = L"ClosePortButton";
			this->ClosePortButton->Size = System::Drawing::Size(119, 60);
			this->ClosePortButton->TabIndex = 7;
			this->ClosePortButton->Text = L"Close Port";
			this->ClosePortButton->UseVisualStyleBackColor = false;
			this->ClosePortButton->Click += gcnew System::EventHandler(this, &MyForm::ClosePortButton_Click);
			// 
			// SendDataTextBox
			// 
			this->SendDataTextBox->Location = System::Drawing::Point(51, 84);
			this->SendDataTextBox->Name = L"SendDataTextBox";
			this->SendDataTextBox->Size = System::Drawing::Size(214, 22);
			this->SendDataTextBox->TabIndex = 8;
			// 
			// ReadDataTextBox
			// 
			this->ReadDataTextBox->Location = System::Drawing::Point(51, 189);
			this->ReadDataTextBox->Name = L"ReadDataTextBox";
			this->ReadDataTextBox->ReadOnly = true;
			this->ReadDataTextBox->Size = System::Drawing::Size(214, 22);
			this->ReadDataTextBox->TabIndex = 9;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(47, 17);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(78, 17);
			this->label3->TabIndex = 10;
			this->label3->Text = L"Port Status";
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(132, 9);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(100, 32);
			this->progressBar1->TabIndex = 11;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(51, 63);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(143, 17);
			this->label4->TabIndex = 12;
			this->label4->Text = L"ASCII Command Line:";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::SeaShell;
			this->ClientSize = System::Drawing::Size(596, 281);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->ReadDataTextBox);
			this->Controls->Add(this->SendDataTextBox);
			this->Controls->Add(this->ClosePortButton);
			this->Controls->Add(this->OpenPortButton);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->BaudRateComboBox);
			this->Controls->Add(this->PortsComboBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->ReadButton);
			this->Controls->Add(this->SendButton);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void SendButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		// add sender name
		String^ name = this->serialPort1->PortName;
		// grab text and store in send buffer
		String^ message = this->SendDataTextBox->Text;
		
		if (this->serialPort1->IsOpen) 
		{
			try 
			{
				// Send ASCII Command from the SendDataTextBox
				this->serialPort1->WriteLine(message);

				/*
				// Uncomment to send serial binary command
				// 0x00 0x45 0x01 0x14 0x00 0x0a = stop cvm program
				cli::array <System::Byte>^ buffer = { 0x00, 0x45, 0x01, 0x14, 0x00, 0x0a };
				// 0 is the offset. 6 is the size of the array.
				this->serialPort1->Write(buffer, 0, 6);
				*/
			}
			catch (TimeoutException^) 
			{
				this->ReadDataTextBox->Text = "Write Timeout Exception";
			}
		}
		else 
		{
			this->ReadDataTextBox->Text = "Port Not Opened";
		}
	}

	private: System::Void ReadButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		// check if port is ready for reading
		if (this->serialPort1->IsOpen) 
		{
			// reset the text in the result textbox
			this->ReadDataTextBox->Text = String::Empty;
			try 
			{
				/*
				// Uncomment for serial binary response		
				int number_of_serial_binary_bytes = serialPort1->BytesToRead;
				std::list<byte> bytes_list;
				if (number_of_serial_binary_bytes > 0) 
				{
					// the entire serial binary response will be found in this list
					for (auto i = 0; i < number_of_serial_binary_bytes; i++) 
					{
						bytes_list.push_back(serialPort1->ReadByte());
					}
				}
				else
				{
					this->ReadDataTextBox->Text = "No Response to serial binary command";
				}
				*/

				// Read and display ASCII Response
				// If using serial binary, comment out the next two lines.
				String^ indata = serialPort1->ReadExisting();
				this->ReadDataTextBox->Text = indata;				
			}
			catch (TimeoutException^) 
			{
				this->ReadDataTextBox->Text = "Timeout Exception";
			}
			this->OpenPortButton->Enabled = false;
		}
		else 
		{
			this->ReadDataTextBox->Text = "Port Not Opened";
		}
	}

	private: System::Void OpenPortButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		this->ClosePortButton->Enabled = true;
		this->OpenPortButton->Enabled = false;
		this->SendDataTextBox->Text = String::Empty;
		this->ReadDataTextBox->Text = String::Empty;
		if (this->BaudRateComboBox->Text == String::Empty || this->PortsComboBox->Text == String::Empty) 
		{
			this->ReadDataTextBox->Text = "Please Select Port Number and Baud Rate";
		}
		else 
		{
			try
			{
				// make sure port is not open
				if (!this->serialPort1->IsOpen)
				{
					this->serialPort1->PortName = this->PortsComboBox->Text;
					this->serialPort1->BaudRate = Int32::Parse(this->BaudRateComboBox->Text);
					// open port
					this->serialPort1->Open();
					this->progressBar1->Value = 100;					
				}
				else
				{
					this->ReadDataTextBox->Text = "Unable to open port";
				}
			}
			catch (UnauthorizedAccessException^) 
			{
				this->ReadDataTextBox->Text = "Unauthorized Access";
			}
		}
	}

    private: System::Void ClosePortButton_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		// close serial port
		this->serialPort1->Close();
		// update progress bar
		this->progressBar1->Value = 0;
		// enable init button
		this->OpenPortButton->Enabled = true;
		// disable the "close port" button
		this->ClosePortButton->Enabled = false;
		// enable read button
		this->ReadButton->Enabled = true;
	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) 
	{
		FindPorts();

		// disable "close port" button because serial port has not been opened yet.
		this->ClosePortButton->Enabled = false;
	}

	private: void FindPorts(void) 
	{		
		// get port names
		array<Object^>^ ObjectArray = serialPort1->GetPortNames();
		// add string to combobox
		this->PortsComboBox->Items->AddRange(ObjectArray);
	}

};
}
