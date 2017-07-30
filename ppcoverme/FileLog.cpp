#include "stdafx.h"
#include "FileLog.h"
#include "strutil.h"

//打开文件
BOOL FileLog::Open(const char* filename)
{
	if (fileHandle == INVALID_HANDLE_VALUE)
	{
		fileHandle = CreateFile(CharToLpcwStr(filename), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (fileHandle != INVALID_HANDLE_VALUE)
		{
			SetFilePointer(fileHandle, 0, NULL, FILE_END);
			return TRUE;
		}
	}
	return FALSE;
}

//关闭文件
BOOL FileLog::Close()
{
	BOOL isOK = FALSE;
	Lock();
	if (fileHandle != INVALID_HANDLE_VALUE)
	{
		isOK = CloseHandle(fileHandle);
		fileHandle = INVALID_HANDLE_VALUE;
	}
	UnLock();
	return isOK;
}

//读取文件
BOOL FileLog::Read(char* buf, int size)
{
	BOOL isOK = FALSE;
	Lock();
	if(fileHandle != INVALID_HANDLE_VALUE)
	{
		DWORD dwSize = 0;
		isOK = ReadFile(fileHandle, buf, size, &dwSize, NULL);//写
	}
	return isOK;
}

FileLog& FileLog::Write(const char* content)
{
	Lock();
	if (fileHandle != INVALID_HANDLE_VALUE)
	{
		DWORD dwSize = 0;
		WriteFile(fileHandle, content, strlen(content), &dwSize, NULL);
	}
	//锁不释放，一个线程占用之后,导致其他线程一直等待
	UnLock();
	return *this;
}

FileLog& FileLog::WriteLine(const char* content)
{
	Lock();
	if (fileHandle != INVALID_HANDLE_VALUE)
	{
		DWORD dwSize = 0;
		WriteFile(fileHandle, content, strlen(content), &dwSize, NULL);
	}
	UnLock();
	return FileLog::Write("\r\n");
}
