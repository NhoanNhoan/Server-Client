#include "SocketConnect.h"

using namespace System;
using namespace System::Text;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;

#define  PORT 25000

void Connect() {
	TcpClient^ client = gcnew TcpClient();
	client->Connect("127.0.0.1", PORT);
}