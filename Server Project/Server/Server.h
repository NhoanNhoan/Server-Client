#pragma once

namespace Server {

	using namespace System;
	using namespace System::Text;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Net;
	using namespace System::Net::Sockets;
	using namespace System::Threading::Tasks;
	using namespace System::Threading;

	/// <summary>
	/// Summary for Server
	/// </summary>
	public ref class Server : public System::Windows::Forms::Form
	{
	private: const int BUFFER_SIZE = 1024;
	private: const int PORT_NUMBER = 9999;
	private: IPAddress ^address = IPAddress::Parse("192.168.0.1");
	private:TcpListener^ listener = gcnew TcpListener(address, PORT_NUMBER);
	private:Socket^ ServerSocket;
	private: System::Windows::Forms::Label^ lbStatus;
	private:array<Socket^>^ Clients = gcnew array<Socket^>(10);
	private:int _CurNumClient = 0;
	private:int _NumQuestion = 2;
	private: int _NumClient = 0;
	private: int _CurQuestion = 0;


		//
	IPHostEntry^ ipHost = Dns::GetHostEntry(Dns::GetHostName());
	IPAddress^ ipAddr = ipHost->AddressList[3];
	IPEndPoint^ localEndPoint = gcnew IPEndPoint(ipAddr, 9999);

	private: static ASCIIEncoding ^encoding = gcnew ASCIIEncoding();
	public:
		Server(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	private:System::Void InitSocket() 
		{
		ServerSocket = gcnew Socket(ipAddr->AddressFamily,
			SocketType::Stream, ProtocolType::Tcp);
		ServerSocket->Bind(localEndPoint);
		ServerSocket->Listen(1);
	}

	private:String^ GetNicknameFromClient()
	{
		array<Byte>^ data = gcnew array<Byte>(1024);
		Clients[_CurNumClient]->Receive(data);

		return Encoding::ASCII->GetString(data);
	}

	private:bool CheckValidNickname(String^ Nickname)
	{
		return true;
	}

	private:void AcceptANewClient()
	{
		Clients[_CurNumClient] = ServerSocket->Accept();

		String^ clientName = GetNicknameFromClient();
		while (!CheckValidNickname(clientName))
		{
			clientName = GetNicknameFromClient();
			SendMessageToAClient(_CurNumClient, "n");
		}

		SendMessageToAClient(_CurNumClient, "y");
		lvClients->Items->Add(gcnew ListViewItem(clientName));
	}

	private:void SendMessageToAClient(int NumClient, String^ Message)
	{
		array<Byte>^ data = Encoding::ASCII->GetBytes(Message);
		Clients[NumClient]->Send(data);
	}

	// Question and Answer
	private:System::String^ GetQuestionFromFile() {
		array<String^>^ lines = File::ReadAllLines("E:/DataServer/Questions.txt");
		++_CurQuestion;
		return lines[_CurQuestion - 1];
	}

	private:String^ GetAnswerFromFile() {
		array<String^>^ lines = File::ReadAllLines("E:/DataServer/Answers.txt");
		return lines[_CurQuestion - 1];
	}

	private:void SendQuestionToClient(int NumClient) {
		String^ Question = GetQuestionFromFile();
		Clients[NumClient]->Send(Encoding::ASCII->GetBytes(Question));
	}

	private:void GetAnswerFromClient(int NumClient)
	{
		array<Byte>^ ClientAnswer = gcnew array<Byte>(BUFFER_SIZE);
		String^ RightAnswer = GetAnswerFromFile();
		String^ MessageForClient = "The right answer is " + RightAnswer;
		
		Clients[_CurNumClient]->Receive(ClientAnswer);
		String^ Answer = Encoding::ASCII->GetString(ClientAnswer);

		if (Answer->ToUpper() == RightAnswer->ToUpper())
		{
			MessageForClient += ". Congratulate!";
		}
		else
		{
			MessageForClient += ". Good luck again!";
		}

		SendMessageToAClient(_CurNumClient, MessageForClient);
	}
	//

		// Old
	/*private:Socket^ AddNewClient() {
		clients[_CurNumClient++] = socket->Accept();
		return clients[_CurNumClient - 1];
	}

	private:Void GetQuestionFromClient(Socket^ client) {
		array<Byte>^ clientAnswer = gcnew array<Byte>(BUFFER_SIZE);
		client->Receive(clientAnswer);
		String^ answerString = Encoding::ASCII->GetString(clientAnswer);
		String^ rightAnswer = GetAnswerFromFile();
		String^ announce = "The right answer is " + rightAnswer;

		if (answerString->ToUpper() == rightAnswer->ToUpper()) {
			announce += " Congratulate!";
		}
		else {
			announce += " Good luck again!";
		}

		SendAnnouceToClient(client, announce);
	}

	private:Void SendAnnouceToClient(Socket^ client, String^ annouce) {
		array<Byte>^ data = Encoding::ASCII->GetBytes(annouce);
		client->Send(data);
	}*/
		// End Old

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Server()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnStart;
	protected:
	private: System::Windows::Forms::Button^ btnClose;
	private: System::Windows::Forms::ListView^ lvClients;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ lbNumClient;

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
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->btnClose = (gcnew System::Windows::Forms::Button());
			this->lvClients = (gcnew System::Windows::Forms::ListView());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->lbNumClient = (gcnew System::Windows::Forms::Label());
			this->lbStatus = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// btnStart
			// 
			this->btnStart->Location = System::Drawing::Point(323, 443);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(108, 42);
			this->btnStart->TabIndex = 0;
			this->btnStart->Text = L"Start";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &Server::BtnStart_Click);
			// 
			// btnClose
			// 
			this->btnClose->Location = System::Drawing::Point(934, 443);
			this->btnClose->Name = L"btnClose";
			this->btnClose->Size = System::Drawing::Size(107, 42);
			this->btnClose->TabIndex = 1;
			this->btnClose->Text = L"Close";
			this->btnClose->UseVisualStyleBackColor = true;
			// 
			// lvClients
			// 
			this->lvClients->Dock = System::Windows::Forms::DockStyle::Left;
			this->lvClients->Location = System::Drawing::Point(0, 0);
			this->lvClients->Name = L"lvClients";
			this->lvClients->Size = System::Drawing::Size(245, 509);
			this->lvClients->TabIndex = 2;
			this->lvClients->UseCompatibleStateImageBehavior = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 468);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(58, 20);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Online:";
			// 
			// lbNumClient
			// 
			this->lbNumClient->AutoSize = true;
			this->lbNumClient->Location = System::Drawing::Point(76, 468);
			this->lbNumClient->Name = L"lbNumClient";
			this->lbNumClient->Size = System::Drawing::Size(18, 20);
			this->lbNumClient->TabIndex = 4;
			this->lbNumClient->Text = L"0";
			// 
			// lbStatus
			// 
			this->lbStatus->AutoSize = true;
			this->lbStatus->Location = System::Drawing::Point(251, 9);
			this->lbStatus->Name = L"lbStatus";
			this->lbStatus->Size = System::Drawing::Size(78, 20);
			this->lbStatus->TabIndex = 5;
			this->lbStatus->Text = L"No clients";
			// 
			// Server
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1053, 509);
			this->Controls->Add(this->lbStatus);
			this->Controls->Add(this->lbNumClient);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->lvClients);
			this->Controls->Add(this->btnClose);
			this->Controls->Add(this->btnStart);
			this->Name = L"Server";
			this->Text = L"Server";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void BtnStart_Click(System::Object^ sender, System::EventArgs^ e) {
		/*
		InitSocket();

		Socket^ client = AddNewClient();
		lbStatus->Text = "Connected a client!";
		++_NumClient;
		lbNumClient->Text = _NumClient.ToString();
		array<Byte>^ data = gcnew array<Byte>(BUFFER_SIZE);
		client->Receive(data);
		String^ clientName = Encoding::ASCII->GetString(data);

		lvClients->Items->Add(gcnew ListViewItem(clientName));

		while (_CurQuestion < _NumQuestion) {
			SendQuestionToClient(client);
			GetQuestionFromClient(client);
		}*/
		lbStatus->Text = "Waiting connection...";
		InitSocket();
		AcceptANewClient();
		lbStatus->Text = "";

		int count = 0;
		while (count++ < _NumQuestion)
		{
			SendQuestionToClient(_CurNumClient);
			GetAnswerFromClient(_CurNumClient);
		}
	}
};
}
