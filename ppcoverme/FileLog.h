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
		EnterCriticalSection(&cs);	//�����ٽ���
	}
	void UnLock()
	{
		LeaveCriticalSection(&cs);	       //�뿪�ٽ���
	}

public:
	FileLog()
	{
		InitializeCriticalSection(&cs);    //��ʼ���ٽ���
		fileHandle = INVALID_HANDLE_VALUE; //��ʼ��Ϊ��Ч���
	}

	~FileLog()
	{
		if (fileHandle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(fileHandle);
		}

		DeleteCriticalSection(&cs);		//ɾ���ٽ���
	}

	BOOL Open(const char* filename);	//���ļ�
	BOOL Close();						//�ر��ļ�
	BOOL Read(char* buf, int size);		//��ȡ����
	FileLog& Write(const char* content);//���ļ���д������
	FileLog& WriteLine(const char* content);//���ļ���д��һ������
};//����ṹ���ӷֺ�


#endif
