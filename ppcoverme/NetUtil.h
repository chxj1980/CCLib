#pragma once
#include <windows.h>
#include <iostream>
#include "FileLog.h"
#include <string>
#include <time.h>
#include <process.h>

#pragma comment(lib,"ws2_32.lib") 

using namespace std;

//多线程调用的方法只有一个指针型的参数，有时候需要多个参数，所以定义一个结构，参数作为结构的字段
typedef struct _StruReceive 
{
	SOCKET *m_Socket;
	FileLog *m_FileLog;
	_StruReceive(SOCKET * _socket, FileLog* _fileLog) :m_Socket(_socket), m_FileLog(_fileLog) {}
}StruReceive;


std::string GetDate(const char* format);//获取今天的日期

void Receive(PVOID param);//接受数据线程

in_addr GetHostName(void);//获取本机IP  

SOCKET StartServer(void);//启动服务器  

SOCKET ReceiveConnect(SOCKET &serverSocket);//接收客户端连接  
 
void SendMsg(SOCKET &clientSocket, FileLog &fileLog);//发送数据 



//client
void ClientReceive(PVOID param);//接收数据  
 
unsigned long GetServerIP(void);//获取服务器IP 

void Connect(SOCKET &sock);//链接服务器  

void SendMsg(SOCKET &sock);//发送数据