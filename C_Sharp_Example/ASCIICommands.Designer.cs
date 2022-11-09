namespace ASCII_Commands
{
    partial class ASCIICommands
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.portNameSelectionComboBox = new System.Windows.Forms.ComboBox();
            this.baudRateSelectionComboBox = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SendGroupBox = new System.Windows.Forms.GroupBox();
            this.sendAsciiCommandButton = new System.Windows.Forms.Button();
            this.asciiCommandTextBox = new System.Windows.Forms.TextBox();
            this.openSerialPortButton = new System.Windows.Forms.Button();
            this.RecievedGroupBox = new System.Windows.Forms.GroupBox();
            this.dataRecievedTextBox = new System.Windows.Forms.TextBox();
            this.statusProgressBar = new System.Windows.Forms.ProgressBar();
            this.closeSerialPortButton = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.connectionStatusBarTimer = new System.Windows.Forms.Timer(this.components);
            this.SendGroupBox.SuspendLayout();
            this.RecievedGroupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // portNameSelectionComboBox
            // 
            this.portNameSelectionComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.portNameSelectionComboBox.FormattingEnabled = true;
            this.portNameSelectionComboBox.Location = new System.Drawing.Point(30, 38);
            this.portNameSelectionComboBox.Name = "portNameSelectionComboBox";
            this.portNameSelectionComboBox.Size = new System.Drawing.Size(121, 21);
            this.portNameSelectionComboBox.TabIndex = 0;
            // 
            // baudRateSelectionComboBox
            // 
            this.baudRateSelectionComboBox.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.baudRateSelectionComboBox.FormattingEnabled = true;
            this.baudRateSelectionComboBox.Items.AddRange(new object[] {
            "9600",
            "115200",
            "230400"});
            this.baudRateSelectionComboBox.Location = new System.Drawing.Point(286, 38);
            this.baudRateSelectionComboBox.Name = "baudRateSelectionComboBox";
            this.baudRateSelectionComboBox.Size = new System.Drawing.Size(121, 21);
            this.baudRateSelectionComboBox.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(27, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(62, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Port Names";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(283, 22);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(58, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Baud Rate";
            // 
            // SendGroupBox
            // 
            this.SendGroupBox.Controls.Add(this.sendAsciiCommandButton);
            this.SendGroupBox.Controls.Add(this.asciiCommandTextBox);
            this.SendGroupBox.Location = new System.Drawing.Point(30, 90);
            this.SendGroupBox.Name = "SendGroupBox";
            this.SendGroupBox.Size = new System.Drawing.Size(200, 105);
            this.SendGroupBox.TabIndex = 4;
            this.SendGroupBox.TabStop = false;
            this.SendGroupBox.Text = "Command:";
            // 
            // sendAsciiCommandButton
            // 
            this.sendAsciiCommandButton.Enabled = false;
            this.sendAsciiCommandButton.Location = new System.Drawing.Point(6, 56);
            this.sendAsciiCommandButton.Name = "sendAsciiCommandButton";
            this.sendAsciiCommandButton.Size = new System.Drawing.Size(188, 36);
            this.sendAsciiCommandButton.TabIndex = 6;
            this.sendAsciiCommandButton.Text = "Send";
            this.sendAsciiCommandButton.UseVisualStyleBackColor = true;
            this.sendAsciiCommandButton.Click += new System.EventHandler(this.sendAsciiCommandButton_Click);
            // 
            // asciiCommandTextBox
            // 
            this.asciiCommandTextBox.Enabled = false;
            this.asciiCommandTextBox.Location = new System.Drawing.Point(6, 19);
            this.asciiCommandTextBox.Multiline = true;
            this.asciiCommandTextBox.Name = "asciiCommandTextBox";
            this.asciiCommandTextBox.Size = new System.Drawing.Size(188, 31);
            this.asciiCommandTextBox.TabIndex = 5;
            // 
            // openSerialPortButton
            // 
            this.openSerialPortButton.Location = new System.Drawing.Point(517, 90);
            this.openSerialPortButton.Name = "openSerialPortButton";
            this.openSerialPortButton.Size = new System.Drawing.Size(92, 50);
            this.openSerialPortButton.TabIndex = 7;
            this.openSerialPortButton.Text = "Open Port";
            this.openSerialPortButton.UseVisualStyleBackColor = true;
            this.openSerialPortButton.Click += new System.EventHandler(this.openPortButton_Click);
            // 
            // RecievedGroupBox
            // 
            this.RecievedGroupBox.Controls.Add(this.dataRecievedTextBox);
            this.RecievedGroupBox.Location = new System.Drawing.Point(286, 90);
            this.RecievedGroupBox.Name = "RecievedGroupBox";
            this.RecievedGroupBox.Size = new System.Drawing.Size(200, 105);
            this.RecievedGroupBox.TabIndex = 7;
            this.RecievedGroupBox.TabStop = false;
            this.RecievedGroupBox.Text = "Response:";
            // 
            // dataRecievedTextBox
            // 
            this.dataRecievedTextBox.Location = new System.Drawing.Point(6, 19);
            this.dataRecievedTextBox.Multiline = true;
            this.dataRecievedTextBox.Name = "dataRecievedTextBox";
            this.dataRecievedTextBox.ReadOnly = true;
            this.dataRecievedTextBox.Size = new System.Drawing.Size(188, 73);
            this.dataRecievedTextBox.TabIndex = 5;
            // 
            // statusProgressBar
            // 
            this.statusProgressBar.ForeColor = System.Drawing.Color.LawnGreen;
            this.statusProgressBar.Location = new System.Drawing.Point(517, 38);
            this.statusProgressBar.Name = "statusProgressBar";
            this.statusProgressBar.Size = new System.Drawing.Size(92, 23);
            this.statusProgressBar.TabIndex = 8;
            // 
            // closeSerialPortButton
            // 
            this.closeSerialPortButton.Enabled = false;
            this.closeSerialPortButton.Location = new System.Drawing.Point(517, 146);
            this.closeSerialPortButton.Name = "closeSerialPortButton";
            this.closeSerialPortButton.Size = new System.Drawing.Size(92, 50);
            this.closeSerialPortButton.TabIndex = 9;
            this.closeSerialPortButton.Text = "Close Port";
            this.closeSerialPortButton.UseVisualStyleBackColor = true;
            this.closeSerialPortButton.Click += new System.EventHandler(this.closeSerialPortButtonClick);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(514, 22);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(37, 13);
            this.label3.TabIndex = 10;
            this.label3.Text = "Status";
            // 
            // connectionStatusBarTimer
            // 
            this.connectionStatusBarTimer.Interval = 500;
            this.connectionStatusBarTimer.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // ASCIICommands
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(636, 232);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.closeSerialPortButton);
            this.Controls.Add(this.statusProgressBar);
            this.Controls.Add(this.RecievedGroupBox);
            this.Controls.Add(this.openSerialPortButton);
            this.Controls.Add(this.SendGroupBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.baudRateSelectionComboBox);
            this.Controls.Add(this.portNameSelectionComboBox);
            this.Name = "ASCIICommands";
            this.Text = "ASCII Commands";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.ASCIICommands_FormClosed);
            this.SendGroupBox.ResumeLayout(false);
            this.SendGroupBox.PerformLayout();
            this.RecievedGroupBox.ResumeLayout(false);
            this.RecievedGroupBox.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox portNameSelectionComboBox;
        private System.Windows.Forms.ComboBox baudRateSelectionComboBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox SendGroupBox;
        private System.Windows.Forms.Button sendAsciiCommandButton;
        private System.Windows.Forms.TextBox asciiCommandTextBox;
        private System.Windows.Forms.Button openSerialPortButton;
        private System.Windows.Forms.GroupBox RecievedGroupBox;
        private System.Windows.Forms.TextBox dataRecievedTextBox;
        private System.Windows.Forms.ProgressBar statusProgressBar;
        private System.Windows.Forms.Button closeSerialPortButton;
        private System.Windows.Forms.Label label3;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Timer connectionStatusBarTimer;
    }
}

