#if!defined(AFX_LOGFILE_H__EF4BC4B2_3BB6_46E8_B936_0F3A61E20BF0__INCLUDE_)
#define AFX_LOGFILE_H__EF4BC4B2_3BB6_46E8_B936_0F3A61E20BF0__INCLUDE_
#pragma once
#include "OpenSource.h"
//#include <logfile.h>
#include <iostream>
UNSING_STD

//debug版本宏
#if _DEBUG
#ifndef _FLAG_OUTLOG_ENABLE
#define _FLAG_OUTLOG_ENABLE TURE
#endif //_FLAG_OUTLOG_ENABLE
#endif //_DEBUG

//设置控制台
#define _DEBUGCONSOLE

//设置文件名宏
//#define _SETFILENAME
#ifdef _SETFILENAME
#define FILENAME "log.txt"
#endif // _SETFILENAME

//设置等级宏
#define _LOGLEVEL
#ifdef _LOGLEVEL
#define MIN_LEVEL 1
#define MAX_LEVEL 5
#endif // _LOGLEVEL


//控制台打印日志
void ConsoleLog();

//文本打印日志
void FileLog();

//日志输出类
struct CLog
{
	//取得进程执行文件名称
	static void GetProcessFileName(char* lpName)
	{
		if (::GetModuleFileName(NULL, lpName, MAX_PATH) > 0)
		{
			char* pBegin = lpName;
			char* pTemp = lpName;
			while (*pTemp != 0)
			{
				if (*pTemp == '\\')
				{
					pBegin = pTemp + 1;
				}
				pTemp++;
			}
			memcpy(lpName, pBegin, strlen(pBegin) + 1);
		}
	}
	//输出到文件
	//lpFile :源文件名
	//nLine : 源文件行号
	static void logout(LPCTSTR lpFile, int nLine, LPCTSTR lpFormat, ...)
	{
		static CRITICAL_SECTION m_crit;
		if (m_crit.DebugInfo == NULL)
			::InitializeCriticalSection(&m_crit);

		//进入临界区（输出信息）
		::EnterCriticalSection(&m_crit);

		if (NULL == lpFormat)
			return;

		//当前时间
		SYSTEMTIME st;
		::GetLocalTime(&st);

		//设置消息头
		const DWORD BufSize = 2048;
		char szMsg[BufSize];

		if (nLine == 0)
		{
			//当nLine == 0 时。即Logout("xxx")只打印信息
			sprintf(szMsg, "[%02d:%02d:%02d.%03d]:", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		}
		else
		{
			//当nLine!=0时， 即Logout(AT"xxx")打印文件名行号及信息
			sprintf(szMsg, "[%02d:%02d:%02d.%03d]文件%s第%04d行：", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, lpFile, nLine);
		}

		//格式化消息，并输出整条信息
		char* pTemp = szMsg;
		pTemp += strlen(szMsg);
		va_list args;
		va_start(args, lpFormat);
		wvsprintfA(pTemp, lpFormat, args); //vsprintf_s BufSize - strlen(szMsg);
		va_end(args);

		DWORD dwMsgLen = (DWORD)strlen(szMsg);

		//获取日志文件名
		char szFileName[MAX_PATH];
		char szExeName[MAX_PATH];
		GetProcessFileName(szExeName);
		sprintf(szFileName, "Log(%s)%d-%d-%d.txt", szExeName, st.wYear, st.wMonth, st.wDay);

		//判断文件名是否相同，句柄是否有效
		//判断不同或者无效， 则关闭当前文件， 创建新文件
		static char s_szFileName[MAX_PATH] = { 0 };
		static HANDLE s_hFile = INVALID_HANDLE_VALUE;

		//设置自定义日志文件名
#ifdef _SETFILENAME
		strcpy(szFileName, FILENAME);
#endif//_SETFILENAME

		BOOL bNew = ((strcmp(s_szFileName, szFileName) != 0) ||(s_hFile == INVALID_HANDLE_VALUE));

#ifdef  _DEBUGCONSOLE //控制台输出
		static BOOL bOpenConsole = FALSE;
		if (!bOpenConsole)
		{
			bOpenConsole = ::AllocConsole();
			if(bOpenConsole)
			{
				freopen("CONOUT$", "w+t", stdout);
				freopen("CONIN$", "r+t", stdin);
				freopen("CONERR", "w", stderr);

				HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTitle("DebugConsole");
				SetConsoleTextAttribute((HANDLE)handle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				
			}
		}
#endif //  _DEBUGCONSOLE //控制台输出

	}

};




char* GetProPath();

#endif