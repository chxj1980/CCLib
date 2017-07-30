#ifndef _FILE_LOG_H_
#define _FILE_LOG_H_

#include <string.h>
#include <iostream>
#include <windows.h>
using namespace std;

class FileLog
{
private:
	CRITICAL_SECTION cs;
	HANDLE fileHandle;
	void Lock()
	{
		EnterCriticalSection(&cs);	//进入临界区
	}
	void UnLock()
	{
		LeaveCriticalSection(&cs);	       //离开临界区
	}

public:
	FileLog()
	{
		InitializeCriticalSection(&cs);    //初始化临界区
		fileHandle = INVALID_HANDLE_VALUE; //初始化为无效句柄
	}

	~FileLog()
	{
		if (fileHandle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(fileHandle);
		}

		DeleteCriticalSection(&cs);		//删除临界区
	}

	BOOL Open(const char* filename);	//打开文件
	BOOL Close();						//关闭文件
	BOOL Read(char* buf, int size);		//读取内容
	FileLog& Write(const char* content);//向文件中写入内容
	FileLog& WriteLine(const char* content);//向文件中写入一行数据
};//类与结构体后加分号


#endif
