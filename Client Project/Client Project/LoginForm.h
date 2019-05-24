#pragma once
#include "Client.h"

namespace ClientProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Text;
	using namespace System::Data;
	using namespace System::IO;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;

	/// <summary>
	/// Summary for LoginForm
	/// </summary>
	public ref class LoginForm : public System::Windows::Forms::Form
	{
	public:Socket^ sender;

	public:
		LoginForm(void)
		{
			InitializeComponent();
			StartPosition = FormStartPosition::CenterScreen;
		}



	private: void ExecuteClient()
	{
		IPHostEntry^ ipHost = Dns::GetHostEntry(Dns::GetHostName());

		// Get ip from textbox
		String^ ip = txtIPAddr1->Text + "." + txtIPAddr2->Text + "." +
							txtIPAddr3->Text + "." + txtIPAddr4->Text;

		// Convert string ip to IPAdress
		IPAddress^ ipAddr = IPAddress::Parse(ip);
		IPEndPoint^ localEndPoint = gcnew IPEndPoint(ipAddr, 9999);

		// Connect to the server
		sender = gcnew Socket(ipAddr->AddressFamily,
			SocketType::Stream, ProtocolType::Tcp);
		EndPoint^ end_point = localEndPoint;
		sender->Connect(end_point);
		SendNicknameToServer();
		MessageBox::Show("Connected to Server");

		// Send the nickname to server
	}

	private:void GetFeedBack()
	{
		array<Byte>^ FeedBack = gcnew array<Byte>(1024);

		// Receive message
		sender->Receive(FeedBack);
		if ('y' == FeedBack[0])
		{
			Client^ ClientForm = gcnew Client(sender);
			// buffer
			sender->Send(FeedBack);
			
			// Receive number of questions
			Array::Clear(FeedBack, 0, FeedBack->Length);
			sender->Receive(FeedBack);
			ClientForm->_NumQuestion = int::Parse(Encoding::ASCII->GetString(FeedBack));

			// Buffer
			sender->Send(FeedBack);
			//
			
			ClientForm->GetQuestionFromServer();
			ClientForm->ShowDialog();
		}
		else
		{
			txtIPAddr1->Enabled = false;
			txtIPAddr2->Enabled = false;
			txtIPAddr3->Enabled = false;
			txtIPAddr4->Enabled = false;
			txtPort->Enabled = false;
			button1->Click += gcnew System::EventHandler(this, &LoginForm::SendToServer);
			MessageBox::Show("The nickname has exists! Please select another nickname!");
		}
	}

	private:void SendToServer(System::Object^ sender, System::EventArgs^ e)
	{
		SendNicknameToServer();
	}

	private:void SendNicknameToServer()
	{
		String^ Nickname = txtNickname->Text;
		array<Byte>^ data = Encoding::ASCII->GetBytes(Nickname);
		sender->Send(data);
	}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LoginForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ txtNickname;

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ txtPort;
	private: System::Windows::Forms::Label^ lbIP;
	private: System::Windows::Forms::TextBox^ txtIPAddr1;
	private: System::Windows::Forms::TextBox^ txtIPAddr2;
	private: System::Windows::Forms::TextBox^ txtIPAddr3;
	private: System::Windows::Forms::TextBox^ txtIPAddr4;




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txtNickname = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txtPort = (gcnew System::Windows::Forms::TextBox());
			this->lbIP = (gcnew System::Windows::Forms::Label());
			this->txtIPAddr1 = (gcnew System::Windows::Forms::TextBox());
			this->txtIPAddr2 = (gcnew System::Windows::Forms::TextBox());
			this->txtIPAddr3 = (gcnew System::Windows::Forms::TextBox());
			this->txtIPAddr4 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 30, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(166, 24);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(226, 64);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Sign Up";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(24, 208);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(127, 30);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Nickname";
			// 
			// txtNickname
			// 
			this->txtNickname->Location = System::Drawing::Point(171, 212);
			this->txtNickname->Name = L"txtNickname";
			this->txtNickname->Size = System::Drawing::Size(291, 26);
			this->txtNickname->TabIndex = 2;
			this->txtNickname->Text = L"User";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(359, 252);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(103, 34);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Sign Up";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &LoginForm::Button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(29, 252);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 34);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Close";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &LoginForm::Button2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(24, 161);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(60, 30);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Port";
			this->label3->Click += gcnew System::EventHandler(this, &LoginForm::Label3_Click);
			// 
			// txtPort
			// 
			this->txtPort->Location = System::Drawing::Point(171, 166);
			this->txtPort->Name = L"txtPort";
			this->txtPort->Size = System::Drawing::Size(100, 26);
			this->txtPort->TabIndex = 6;
			this->txtPort->Text = L"9999";
			this->txtPort->TextChanged += gcnew System::EventHandler(this, &LoginForm::TextBox1_TextChanged);
			// 
			// lbIP
			// 
			this->lbIP->AutoSize = true;
			this->lbIP->Font = (gcnew System::Drawing::Font(L"Mongolian Baiti", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbIP->Location = System::Drawing::Point(24, 119);
			this->lbIP->Name = L"lbIP";
			this->lbIP->Size = System::Drawing::Size(136, 30);
			this->lbIP->TabIndex = 7;
			this->lbIP->Text = L"IP Address";
			this->lbIP->Click += gcnew System::EventHandler(this, &LoginForm::Label4_Click);
			// 
			// txtIPAddr1
			// 
			this->txtIPAddr1->Location = System::Drawing::Point(171, 119);
			this->txtIPAddr1->Name = L"txtIPAddr1";
			this->txtIPAddr1->Size = System::Drawing::Size(70, 26);
			this->txtIPAddr1->TabIndex = 8;
			this->txtIPAddr1->Text = L"192";
			this->txtIPAddr1->TextChanged += gcnew System::EventHandler(this, &LoginForm::TxtIPAddr1_TextChanged);
			// 
			// txtIPAddr2
			// 
			this->txtIPAddr2->Location = System::Drawing::Point(247, 119);
			this->txtIPAddr2->Name = L"txtIPAddr2";
			this->txtIPAddr2->Size = System::Drawing::Size(71, 26);
			this->txtIPAddr2->TabIndex = 9;
			this->txtIPAddr2->Text = L"168";
			// 
			// txtIPAddr3
			// 
			this->txtIPAddr3->Location = System::Drawing::Point(324, 119);
			this->txtIPAddr3->Name = L"txtIPAddr3";
			this->txtIPAddr3->Size = System::Drawing::Size(68, 26);
			this->txtIPAddr3->TabIndex = 10;
			this->txtIPAddr3->Text = L"0";
			// 
			// txtIPAddr4
			// 
			this->txtIPAddr4->Location = System::Drawing::Point(398, 119);
			this->txtIPAddr4->Name = L"txtIPAddr4";
			this->txtIPAddr4->Size = System::Drawing::Size(64, 26);
			this->txtIPAddr4->TabIndex = 11;
			this->txtIPAddr4->Text = L"11";
			// 
			// LoginForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(517, 338);
			this->Controls->Add(this->txtIPAddr4);
			this->Controls->Add(this->txtIPAddr3);
			this->Controls->Add(this->txtIPAddr2);
			this->Controls->Add(this->txtIPAddr1);
			this->Controls->Add(this->lbIP);
			this->Controls->Add(this->txtPort);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->txtNickname);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"LoginForm";
			this->Text = L"LoginForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Button1_Click(System::Object^ sender, System::EventArgs^ e) {
		//// Check valid nickname
		//if (txtNickname->Text == String::Empty)
		//{
		//	MessageBox::Show("The nickname is empty! Invalid", "Notification Error");
		//	return;
		//}

		//if (txtPort->Text == String::Empty)
		//{
		//	MessageBox::Show("Port is empty! Invalid", "Notification Error");
		//	return;
		//}
		////


		////
		//TcpClient^ client = gcnew TcpClient();
		//client->Connect("192.168.0.1", 
		//	int::Parse(txtPort->Text));

		//Stream^ stream = client->GetStream();
		//array<unsigned char>^ buff = gcnew array<unsigned char>(1024);

		//// Copy user nickname -> buff
		//for (int i = 0; i < txtNickname->Text->Length; ++i) {
		//	buff[i] = txtNickname->Text[i];
		//}

		//stream->Write(buff, 0, txtNickname->Text->Length);
		//stream->Read(buff, 0, 1);

		//if (buff[0] == 'n')
		//{
		//	MessageBox::Show("This nickname has exist!", "Error!");
		//	return;
		//}
		//else 
		//{
		//	MessageBox::Show("Success!", "Congratulation!");
		//	txtPort->ReadOnly = true;
		//	txtNickname->ReadOnly = true;
		//	button1->Hide();
		//	button2->Hide();
		//	Client^ clientForm = gcnew Client(client, stream);
		//	clientForm->ShowDialog();
		//	this->Close();
		//}

		ExecuteClient();
		GetFeedBack();
	}

private: System::Void Button2_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Close();
}

		// Not Use
private: System::Void Label3_Click(System::Object^ sender, System::EventArgs^ e) {
}

private: System::Void TextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}

private: System::Void Label4_Click(System::Object^ sender, System::EventArgs^ e) {
}

private: System::Void TxtIPAddr1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
