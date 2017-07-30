#include "stdafx.h"
#include "NetUtil.h"

//��ȡ���������
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

//���������߳�
void Receive(PVOID param)
{
	StruReceive* receiveStru = (StruReceive*)param;
	char buf[2048];

	int bytes;
	while (1)
	{
		//��������
		if ((bytes = recv(*receiveStru->m_Socket, buf, sizeof(buf), 0)) == SOCKET_ERROR)
		{
			cout << "��������ʧ�ܣ�" << endl;
			_endthread();//��ֹ��ǰ�߳�
		}
		buf[bytes] = '\0';
		cout << "�ͻ���˵��" << buf << endl;
		receiveStru->m_FileLog->Write("�ͻ���    ").WriteLine(GetDate("%Y-%m-%d %H:%M:%S").c_str()).WriteLine(buf);//��¼�������� 
	}
}

//��ȡ����IP  
in_addr GetHostName(void)
{
	char host_name[255];
	//��ȡ������������  
	if (gethostname(host_name, sizeof(host_name)) == SOCKET_ERROR) {
		cout << "Error %d when getting local host name." << WSAGetLastError();
		Sleep(3000);
		exit(-1);
	}

	//�����������ݿ��еõ���Ӧ�ġ�IP��   
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

//����������  
SOCKET StartServer(void)
{
	//�����׽���  
	SOCKET serverSocket;
	if ((serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
		cout << "�����׽���ʧ�ܣ�";
		Sleep(3000);
		exit(-1);
	}
	short port = 1986;
	struct sockaddr_in serverAddress;
	//��ʼ��ָ�����ڴ�����  
	memset(&serverAddress, 0, sizeof(sockaddr_in));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(port);

	//��  
	if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		cout << "�׽��ְ󶨵��˿�ʧ�ܣ��˿�:" << port;
		Sleep(3000);
		exit(-1);
	}

	//��������״̬  
	if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
		cout << "����ʧ�ܣ�";
		Sleep(3000);
		exit(-1);
	}

	//��ȡ������IP  
	struct in_addr addr = GetHostName();
	cout << "Server " << inet_ntoa(addr) << " : " << port << " is listening......" << endl;
	return serverSocket;
}


//���տͻ�������  
SOCKET ReceiveConnect(SOCKET &serverSocket)
{
	SOCKET clientSocket;//�����Ϳͻ���ͨ�ŵ��׽���  
	struct sockaddr_in clientAddress;//�����Ϳͻ���ͨ�ŵ��׽��ֵ�ַ  
	memset(&clientAddress, 0, sizeof(clientAddress));//��ʼ����ſͻ�����Ϣ���ڴ�  
	int addrlen = sizeof(clientAddress);

	//��������  
	if ((clientSocket = accept(serverSocket, (sockaddr*)&clientAddress, &addrlen)) == INVALID_SOCKET) {
		cout << "���ܿͻ�������ʧ�ܣ�";
		Sleep(3000);
		exit(-1);
	}
	cout << "Accept connection from " << inet_ntoa(clientAddress.sin_addr) << endl;
	return clientSocket;
}


//��������  
void SendMsg(SOCKET &clientSocket, FileLog &fileLog)
{
	char buf[2048];
	while (1) {
		cout << "������˵��";
		gets_s(buf);
		if (send(clientSocket, buf, strlen(buf), 0) == SOCKET_ERROR) {
			cout << "��������ʧ�ܣ�" << endl;
			Sleep(3000);
			exit(-1);
		}
		fileLog.Write("������   ").WriteLine(GetDate("%Y-%m-%d %H:%M:%S").c_str()).WriteLine(buf);//��¼��������  
	}
}

//server
//int main(int argc, char* argv[]) {
//	WSADATA wsa;//WSADATA�ṹ���������溯��WSAStartup���ص�Windows Sockets��ʼ����Ϣ  
//
//				//MAKEWORD(a,b)�ǽ�����byte�ͺϲ���һ��word�ͣ�һ���ڸ�8λ(b)��һ���ڵ�8λ(a)   
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
//		cout << "�׽��ֳ�ʼ��ʧ��!";
//		Sleep(3000);
//		exit(-1);
//	}
//
//	SOCKET serverSocket = StartServer();//����������  
//	SOCKET clientSocket = ReceiveConnect(serverSocket);//���տͷ��˵�����  
//
//	FileLog fileLog;
//	fileLog.Open(GetDate("%Y%m%d").append(".log").c_str());//�򿪼�¼���������ļ�  
//
//	ReceiveStruct receiveStruct(&clientSocket, &fileLog);
//	_beginthread(receive, 0, &receiveStruct);//����һ���������ݵ��߳�  
//
//	SendMsg(clientSocket, fileLog);//��������  
//
//	fileLog.Close();//�ر��ļ�  
//	closesocket(clientSocket);//�رտͻ����׽��֣����Ϸ���FIN�źţ�����û�н��յ����Ƿ�����ɵ����ݶ��ᶪʧ��  
//	closesocket(serverSocket);//�رշ������׽���  
//
//							  //�����׽���ռ�õ���Դ  
//	WSACleanup();
//	return 0;
//}


//�ͻ���
//��������  
void ClientReceive(PVOID param)
{
	char buf[2096];
	while (1)
	{
		SOCKET* sock = (SOCKET*)param;
		int bytes;
		if ((bytes = recv(*sock, buf, sizeof(buf), 0)) == SOCKET_ERROR) {
			printf("��������ʧ��!\n");
			exit(-1);
		}
		buf[bytes] = '\0';
		cout << "������˵��" << buf << endl;
	}
}

//��ȡ������IP  
unsigned long GetServerIP(void)
{
	//���ַ�����IP��ַת��Ϊu_long  
	char ipStr[20];
	//�õڶ�����������һ��������ָ���ڴ棬���ĳ���Ϊ�����������Ĵ�С  
	memset(ipStr, 0, sizeof(ipStr));
	cout << "��������Ҫ���ӵķ�����IP��";
	cin >> ipStr;
	unsigned long ip;
	if ((ip = inet_addr(ipStr)) == INADDR_NONE) {
		cout << "���Ϸ���IP��ַ��";
		Sleep(3000);
		exit(-1);
	}
	return ip;
}

//���ӷ�����  
void Connect(SOCKET &sock)
{
	unsigned long ip = GetServerIP();
	//�Ѷ˿ں�ת��������  
	short port = 1986;
	cout << "Connecting to " << inet_ntoa(*(in_addr*)&ip) << " : " << port << endl;
	struct sockaddr_in serverAddress;
	memset(&serverAddress, 0, sizeof(sockaddr_in));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.S_un.S_addr = ip;
	serverAddress.sin_port = htons(port);
	//�����ͷ�����������  
	if (connect(sock, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
		cout << "��������ʧ��:" << WSAGetLastError();
		Sleep(3000);
		exit(-1);
	}
}

//��������  
void SendMsg(SOCKET &sock)
{
	char buf[2048];
	while (1) {

		//�ӿ���̨��ȡһ������  
		gets_s(buf);
		cout << "��˵��";
		//���͸�������  
		if (send(sock, buf, strlen(buf), 0) == SOCKET_ERROR) {
			cout << "��������ʧ�ܣ�";
			exit(-1);
		}
	}
}


//int main(int argc, char* argv[]) {
//	WSADATA wsa;
//	//��ʼ���׽���DLL  
//	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
//		cout << "�׽��ֳ�ʼ��ʧ��!";
//		Sleep(3000);
//		exit(-1);
//	}
//
//	//�����׽���  
//	SOCKET sock;
//	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
//		cout << "�����׽���ʧ�ܣ�";
//		exit(-1);
//	}
//
//	Connect(sock);//���ӷ�����  
//
//	_beginthread(Receive, 0, &sock);//�������������߳�  
//	SendMsg(sock);//��������  
//
//				  //�����׽���ռ�õ���Դ  
//	WSACleanup();
//	return 0;
//}

