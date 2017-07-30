#include "stdafx.h"
#include "NetUtil.h"

//获取今天的日期
std::string GetDate(const char* format)
{
	time_t tm;
	struct  tm* now;
	char timebuf[20];
	time(&tm);
	now = localtime(&tm);
	strftime(timebuf, sizeof(timebuf) / sizeof(char), format, now);
	return std::string(timebuf);
}

//接受数据线程
void Receive(PVOID param)
{
	StruReceive* receiveStru = (StruReceive*)param;
	char buf[2048];

	int bytes;
	while (1)
	{
		//接受数据
		if ((bytes = recv(*receiveStru->m_Socket, buf, sizeof(buf), 0)) == SOCKET_ERROR)
		{
			cout << "接受数据失败！" << endl;
			_endthread();//终止当前线程
		}
		buf[bytes] = '\0';
		cout << "客户端说：" << buf << endl;
		receiveStru->m_FileLog->Write("客户端    ").WriteLine(GetDate("%Y-%m-%d %H:%M:%S").c_str()).WriteLine(buf);//记录聊天内容 
	}
}

//获取本机IP  
in_addr GetHostName(void)
{
	char host_name[255];
	//获取本地主机名称  
	if (gethostname(host_name, sizeof(host_name)) == SOCKET_ERROR) {
		cout << "Error %d when getting local host name." << WSAGetLastError();
		Sleep(3000);
		exit(-1);
	}

	//从主机名数据库中得到对应的“IP”   
	struct hostent *phe = gethostbyname(host_name);
	if (phe == 0) {
		cout << "Yow! Bad host lookup.";
		Sleep(3000);
		exit(-1);
	}
	struct in_addr addr;
	memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));
	return addr;
}

//启动服务器  
SOCKET StartServer(void)
{
	//创建套接字  
	SOCKET serverSocket;
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		cout << "创建套接字失败！";
		Sleep(3000);
		exit(-1);
	}
	short port = 1986;
	struct sockaddr_in serverAddress;
	//初始化指定的内存区域  
	memset(&serverAddress, 0, sizeof(sockaddr_in));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(port);

	//绑定  
	if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		cout << "套接字绑定到端口失败！端口:" << port;
		Sleep(3000);
		exit(-1);
	}

	//进入侦听状态  
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		cout << "侦听失败！";
		Sleep(3000);
		exit(-1);
	}

	//获取服务器IP  
	struct in_addr addr = GetHostName();
	cout << "Server " << inet_ntoa(addr) << " : " << port << " is listening......" << endl;
	return serverSocket;
}


//接收客户端连接  
SOCKET ReceiveConnect(SOCKET &serverSocket)
{
	SOCKET clientSocket;//用来和客户端通信的套接字  
	struct sockaddr_in clientAddress;//用来和客户端通信的套接字地址  
	memset(&clientAddress, 0, sizeof(clientAddress));//初始化存放客户端信息的内存  
	int addrlen = sizeof(clientAddress);

	//接受连接  
	if ((clientSocket = accept(serverSocket, (sockaddr*)&clientAddress, &addrlen)) == INVALID_SOCKET) {
		cout << "接受客户端连接失败！";
		Sleep(3000);
		exit(-1);
	}
	cout << "Accept connection from " << inet_ntoa(clientAddress.sin_addr) << endl;
	return clientSocket;
}


//发送数据  
void SendMsg(SOCKET &clientSocket, FileLog &fileLog)
{
	char buf[2048];
	while (1) {
		cout << "服务器说：";
		gets_s(buf);
		if (send(clientSocket, buf, strlen(buf), 0) == SOCKET_ERROR) {
			cout << "发送数据失败！" << endl;
			Sleep(3000);
			exit(-1);
		}
		fileLog.Write("服务器   ").WriteLine(GetDate("%Y-%m-%d %H:%M:%S").c_str()).WriteLine(buf);//记录聊天内容  
	}
}

//server
//int main(int argc, char* argv[]) {
//	WSADATA wsa;//WSADATA结构被用来保存函数WSAStartup返回的Windows Sockets初始化信息  
//
//				//MAKEWORD(a,b)是将两个byte型合并成一个word型，一个在高8位(b)，一个在低8位(a)   
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
//		cout << "套接字初始化失败!";
//		Sleep(3000);
//		exit(-1);
//	}
//
//	SOCKET serverSocket = StartServer();//启动服务器  
//	SOCKET clientSocket = ReceiveConnect(serverSocket);//接收客服端的链接  
//
//	FileLog fileLog;
//	fileLog.Open(GetDate("%Y%m%d").append(".log").c_str());//打开记录聊天内容文件  
//
//	ReceiveStruct receiveStruct(&clientSocket, &fileLog);
//	_beginthread(receive, 0, &receiveStruct);//启动一个接收数据的线程  
//
//	SendMsg(clientSocket, fileLog);//发送数据  
//
//	fileLog.Close();//关闭文件  
//	closesocket(clientSocket);//关闭客户端套接字（马上发送FIN信号，所有没有接收到或是发送完成的数据都会丢失）  
//	closesocket(serverSocket);//关闭服务器套接字  
//
//							  //清理套接字占用的资源  
//	WSACleanup();
//	return 0;
//}


//客户端
//接收数据  
void ClientReceive(PVOID param)
{
	char buf[2096];
	while (1)
	{
		SOCKET* sock = (SOCKET*)param;
		int bytes;
		if ((bytes = recv(*sock, buf, sizeof(buf), 0)) == SOCKET_ERROR) {
			printf("接收数据失败!\n");
			exit(-1);
		}
		buf[bytes] = '\0';
		cout << "服务器说：" << buf << endl;
	}
}

//获取服务器IP  
unsigned long GetServerIP(void)
{
	//把字符串的IP地址转化为u_long  
	char ipStr[20];
	//用第二个参数填充第一个参数所指的内存，填充的长度为第三个参数的大小  
	memset(ipStr, 0, sizeof(ipStr));
	cout << "请输入你要链接的服务器IP：";
	cin >> ipStr;
	unsigned long ip;
	if ((ip = inet_addr(ipStr)) == INADDR_NONE) {
		cout << "不合法的IP地址：";
		Sleep(3000);
		exit(-1);
	}
	return ip;
}

//链接服务器  
void Connect(SOCKET &sock)
{
	unsigned long ip = GetServerIP();
	//把端口号转化成整数  
	short port = 1986;
	cout << "Connecting to " << inet_ntoa(*(in_addr*)&ip) << " : " << port << endl;
	struct sockaddr_in serverAddress;
	memset(&serverAddress, 0, sizeof(sockaddr_in));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.S_un.S_addr = ip;
	serverAddress.sin_port = htons(port);
	//建立和服务器的连接  
	if (connect(sock, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		cout << "建立连接失败:" << WSAGetLastError();
		Sleep(3000);
		exit(-1);
	}
}

//发送数据  
void SendMsg(SOCKET &sock)
{
	char buf[2048];
	while (1) {

		//从控制台读取一行数据  
		gets_s(buf);
		cout << "我说：";
		//发送给服务器  
		if (send(sock, buf, strlen(buf), 0) == SOCKET_ERROR) {
			cout << "发送数据失败！";
			exit(-1);
		}
	}
}


//int main(int argc, char* argv[]) {
//	WSADATA wsa;
//	//初始化套接字DLL  
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
//		cout << "套接字初始化失败!";
//		Sleep(3000);
//		exit(-1);
//	}
//
//	//创建套接字  
//	SOCKET sock;
//	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
//		cout << "创建套接字失败！";
//		exit(-1);
//	}
//
//	Connect(sock);//链接服务器  
//
//	_beginthread(Receive, 0, &sock);//启动接收数据线程  
//	SendMsg(sock);//发送数据  
//
//				  //清理套接字占用的资源  
//	WSACleanup();
//	return 0;
//}

