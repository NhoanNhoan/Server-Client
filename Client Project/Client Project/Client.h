#pragma once
#include <string>

namespace ClientProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Data;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Text;
	using namespace System::IO;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Net;
	using namespace System::Net::Sockets;

	/// <summary>
	/// Summary for Client
	/// </summary>
	public ref class Client : public System::Windows::Forms::Form
	{
	private:TcpClient^ client;
	private: System::Windows::Forms::Timer^ timerCountTime;
	private: System::Windows::Forms::Label^ lbTimeRemaining;
	private: System::Windows::Forms::Label^ lbCountTime;
	private:Stream^ stream;

	private:Socket^ ClientSocket;

	public:
		Client(void)
		{
			InitializeComponent();
		}

	public:
		Client(TcpClient^ client, Stream^ stream) {
			InitializeComponent();
			StartPosition = FormStartPosition::CenterScreen;
			this->client = client;
			this->stream = stream;
			GetQuestionFromServer();
			timerCountTime->Enabled = true;
		}

		Client(Socket^ ClientSocket)
		{
			InitializeComponent();
			this->ClientSocket = ClientSocket;
			timerCountTime->Enabled = true;
		}

	public:
		void GetQuestionFromServer()
		{
			array<Byte>^ Question = gcnew array<Byte>(1024);
			ClientSocket->Receive(Question);
			richTextBoxQuestion->Text = Encoding::ASCII->GetString(Question);
		}

	private:
		bool SendAnswerToServer()
		{
			if (txtAnswer->Text == String::Empty)
			{
				MessageBox::Show("Your answer is empty! Invalid!", "Error");
				return false;
			}

			ClientSocket->Send(Encoding::ASCII->GetBytes(txtAnswer->Text));
			return true;
		}

		void GetRightAnswerFromServer()
		{
			array<Byte>^ RightAnswer = gcnew array<Byte>(1024);
			ClientSocket->Receive(RightAnswer);
			MessageBox::Show(Encoding::ASCII->GetString(RightAnswer), "Notification the answer");
		}

		// OLD
	public:
		System::Void GetQuestion() {
			richTextBoxQuestion->Text = "";
			array<unsigned char>^ question = gcnew array<unsigned char>(1024);

			// Get the question from the server
			stream->Read(question, 0, 1024);

			// Show the question
			richTextBoxQuestion->Text = Encoding::ASCII->GetString(question);
	}

		System::Boolean SendAnswer() {
			array<unsigned char>^ answer = gcnew array<unsigned char>(1024);

			if (txtAnswer->Text == String::Empty)
			{
				MessageBox::Show("Your answer is empty! Invalid!", "Error Empty The Anwers");
				return false;
			}

			answer = Encoding::ASCII->GetBytes(txtAnswer->Text);
			txtAnswer->Text = "";

			// Send the answer to the server
			stream->Write(answer, 0, answer->Length);

			return true;
		}

		System::Void GetRightAnswer() {
			array<unsigned char>^ answer = gcnew array<unsigned char>(1024);

			// Receive right answer from the server
			stream->Read(answer, 0, 1024);

			// Display notification
			MessageBox::Show(Encoding::ASCII->GetString(answer), "Notification the answer");
		}
		// OLD

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Client()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:





	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ btnSend;
	private: System::Windows::Forms::Button^ btnSurrender;
	private: System::Windows::Forms::GroupBox^ groupBoxQuestion;


	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::TextBox^ txtAnswer;
	private: System::Windows::Forms::RichTextBox^ richTextBoxQuestion;
	private: System::ComponentModel::IContainer^ components;



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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->btnSend = (gcnew System::Windows::Forms::Button());
			this->btnSurrender = (gcnew System::Windows::Forms::Button());
			this->groupBoxQuestion = (gcnew System::Windows::Forms::GroupBox());
			this->richTextBoxQuestion = (gcnew System::Windows::Forms::RichTextBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->txtAnswer = (gcnew System::Windows::Forms::TextBox());
			this->timerCountTime = (gcnew System::Windows::Forms::Timer(this->components));
			this->lbTimeRemaining = (gcnew System::Windows::Forms::Label());
			this->lbCountTime = (gcnew System::Windows::Forms::Label());
			this->groupBoxQuestion->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"OCR A Extended", 40, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(275, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(419, 83);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Let\'s Go";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(742, 501);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(108, 20);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Số câu còn lại";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(865, 497);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(55, 26);
			this->textBox1->TabIndex = 7;
			// 
			// btnSend
			// 
			this->btnSend->Font = (gcnew System::Drawing::Font(L"Wide Latin", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnSend->Location = System::Drawing::Point(750, 89);
			this->btnSend->Name = L"btnSend";
			this->btnSend->Size = System::Drawing::Size(147, 45);
			this->btnSend->TabIndex = 8;
			this->btnSend->Text = L"Send";
			this->btnSend->UseVisualStyleBackColor = true;
			this->btnSend->Click += gcnew System::EventHandler(this, &Client::BtnSend_Click);
			// 
			// btnSurrender
			// 
			this->btnSurrender->Font = (gcnew System::Drawing::Font(L"Wide Latin", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnSurrender->Location = System::Drawing::Point(7, 89);
			this->btnSurrender->Name = L"btnSurrender";
			this->btnSurrender->Size = System::Drawing::Size(117, 45);
			this->btnSurrender->TabIndex = 9;
			this->btnSurrender->Text = L"Surrender";
			this->btnSurrender->UseVisualStyleBackColor = true;
			this->btnSurrender->Click += gcnew System::EventHandler(this, &Client::BtnSurrender_Click);
			// 
			// groupBoxQuestion
			// 
			this->groupBoxQuestion->Controls->Add(this->richTextBoxQuestion);
			this->groupBoxQuestion->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->groupBoxQuestion->Location = System::Drawing::Point(12, 111);
			this->groupBoxQuestion->Name = L"groupBoxQuestion";
			this->groupBoxQuestion->Size = System::Drawing::Size(908, 192);
			this->groupBoxQuestion->TabIndex = 12;
			this->groupBoxQuestion->TabStop = false;
			this->groupBoxQuestion->Text = L"Question";
			// 
			// richTextBoxQuestion
			// 
			this->richTextBoxQuestion->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 19, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->richTextBoxQuestion->Location = System::Drawing::Point(7, 33);
			this->richTextBoxQuestion->Name = L"richTextBoxQuestion";
			this->richTextBoxQuestion->ReadOnly = true;
			this->richTextBoxQuestion->Size = System::Drawing::Size(891, 153);
			this->richTextBoxQuestion->TabIndex = 0;
			this->richTextBoxQuestion->Text = L"";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->txtAnswer);
			this->groupBox2->Controls->Add(this->btnSend);
			this->groupBox2->Controls->Add(this->btnSurrender);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->groupBox2->Location = System::Drawing::Point(13, 323);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(907, 140);
			this->groupBox2->TabIndex = 13;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Answer";
			// 
			// txtAnswer
			// 
			this->txtAnswer->Location = System::Drawing::Point(7, 35);
			this->txtAnswer->Name = L"txtAnswer";
			this->txtAnswer->Size = System::Drawing::Size(890, 34);
			this->txtAnswer->TabIndex = 0;
			// 
			// timerCountTime
			// 
			this->timerCountTime->Interval = 1000;
			this->timerCountTime->Tick += gcnew System::EventHandler(this, &Client::TimerCountTime_Tick);
			// 
			// lbTimeRemaining
			// 
			this->lbTimeRemaining->AutoSize = true;
			this->lbTimeRemaining->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbTimeRemaining->Location = System::Drawing::Point(15, 494);
			this->lbTimeRemaining->Name = L"lbTimeRemaining";
			this->lbTimeRemaining->Size = System::Drawing::Size(188, 29);
			this->lbTimeRemaining->TabIndex = 14;
			this->lbTimeRemaining->Text = L"Time remaining:";
			// 
			// lbCountTime
			// 
			this->lbCountTime->AutoSize = true;
			this->lbCountTime->Font = (gcnew System::Drawing::Font(L"Nirmala UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbCountTime->Location = System::Drawing::Point(196, 478);
			this->lbCountTime->Name = L"lbCountTime";
			this->lbCountTime->Size = System::Drawing::Size(62, 48);
			this->lbCountTime->TabIndex = 15;
			this->lbCountTime->Text = L"60";
			// 
			// Client
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(932, 535);
			this->Controls->Add(this->lbCountTime);
			this->Controls->Add(this->lbTimeRemaining);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBoxQuestion);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"Client";
			this->Text = L"Client";
			this->groupBoxQuestion->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: 
	System::Void BtnSend_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		SendAnswerToServer();
		GetRightAnswerFromServer();
		//ClientSocket->Send(gcnew array<Byte>(1));
		++_CurQuestion;
		txtAnswer->Text = String::Empty;

		if (_CurQuestion < _NumQuestion)
		{
			GetQuestionFromServer();
			_curTime = 60;
			lbCountTime->Text = _curTime.ToString();
		}
		else
		{
			lbCountTime->Text = "0";
			timerCountTime->Enabled = false;
			MessageBox::Show("End game");
		}
	}

	System::Void BtnSurrender_Click(System::Object^ sender, System::EventArgs^ e) {
	client->Close();
	stream->Close();
	this->Close();
}

private:
	static int _curTime = 60;
	bool FirstTime = true;

public:
	int _NumQuestion;
	int _CurQuestion = 0;

private: System::Void TimerCountTime_Tick(System::Object^ sender, System::EventArgs^ e) {
	if (_curTime > 0) 
	{
		--_curTime;
		lbCountTime->Text = _curTime.ToString();
	}
	else 
	{
		timerCountTime->Enabled = false;
		MessageBox::Show("Time up!", "Notification");
		txtAnswer->Text = ".32ae12esd";
		SendAnswer();
		GetRightAnswer();
		GetQuestion();
		_curTime = 60;
		timerCountTime->Enabled = true;
		lbCountTime->Text = _curTime.ToString();
	}
}
};
}
