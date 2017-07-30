#pragma once
#include <windows.h>
#include <iostream>
#include "FileLog.h"
#include <string>
#include <time.h>
#include <process.h>

#pragma comment(lib,"ws2_32.lib") 

using namespace std;

//���̵߳��õķ���ֻ��һ��ָ���͵Ĳ�������ʱ����Ҫ������������Զ���һ���ṹ��������Ϊ�ṹ���ֶ�
typedef struct _StruReceive 
{
	SOCKET *m_Socket;
	FileLog *m_FileLog;
	_StruReceive(SOCKET * _socket, FileLog* _fileLog) :m_Socket(_socket), m_FileLog(_fileLog) {}
}StruReceive;


std::string GetDate(const char* format);//��ȡ���������

void Receive(PVOID param);//���������߳�

in_addr GetHostName(void);//��ȡ����IP  

SOCKET StartServer(void);//����������  

SOCKET ReceiveConnect(SOCKET &serverSocket);//���տͻ�������  
 
void SendMsg(SOCKET &clientSocket, FileLog &fileLog);//�������� 



//client
void ClientReceive(PVOID param);//��������  
 
unsigned long GetServerIP(void);//��ȡ������IP 

void Connect(SOCKET &sock);//���ӷ�����  

void SendMsg(SOCKET &sock);//��������