#include "stdafx.h"
#include "FileLog.h"
#include "strutil.h"

//���ļ�
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

//�ر��ļ�
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

//��ȡ�ļ�
BOOL FileLog::Read(char* buf, int size)
{
	BOOL isOK = FALSE;
	Lock();
	if(fileHandle != INVALID_HANDLE_VALUE)
	{
		DWORD dwSize = 0;
		isOK = ReadFile(fileHandle, buf, size, &dwSize, NULL);//д
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
	//�����ͷţ�һ���߳�ռ��֮��,���������߳�һֱ�ȴ�
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
