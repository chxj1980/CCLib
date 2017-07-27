#if!defined(AFX_LOGFILE_H__EF4BC4B2_3BB6_46E8_B936_0F3A61E20BF0__INCLUDE_)
#define AFX_LOGFILE_H__EF4BC4B2_3BB6_46E8_B936_0F3A61E20BF0__INCLUDE_
#pragma once
#include "OpenSource.h"
//#include <logfile.h>
#include <iostream>
UNSING_STD

//debug�汾��
#if _DEBUG
#ifndef _FLAG_OUTLOG_ENABLE
#define _FLAG_OUTLOG_ENABLE TURE
#endif //_FLAG_OUTLOG_ENABLE
#endif //_DEBUG

//���ÿ���̨
#define _DEBUGCONSOLE

//�����ļ�����
//#define _SETFILENAME
#ifdef _SETFILENAME
#define FILENAME "log.txt"
#endif // _SETFILENAME

//���õȼ���
#define _LOGLEVEL
#ifdef _LOGLEVEL
#define MIN_LEVEL 1
#define MAX_LEVEL 5
#endif // _LOGLEVEL


//����̨��ӡ��־
void ConsoleLog();

//�ı���ӡ��־
void FileLog();

//��־�����
struct CLog
{
	//ȡ�ý���ִ���ļ�����
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
	//������ļ�
	//lpFile :Դ�ļ���
	//nLine : Դ�ļ��к�
	static void logout(LPCTSTR lpFile, int nLine, LPCTSTR lpFormat, ...)
	{
		static CRITICAL_SECTION m_crit;
		if (m_crit.DebugInfo == NULL)
			::InitializeCriticalSection(&m_crit);

		//�����ٽ����������Ϣ��
		::EnterCriticalSection(&m_crit);

		if (NULL == lpFormat)
			return;

		//��ǰʱ��
		SYSTEMTIME st;
		::GetLocalTime(&st);

		//������Ϣͷ
		const DWORD BufSize = 2048;
		char szMsg[BufSize];

		if (nLine == 0)
		{
			//��nLine == 0 ʱ����Logout("xxx")ֻ��ӡ��Ϣ
			sprintf(szMsg, "[%02d:%02d:%02d.%03d]:", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
		}
		else
		{
			//��nLine!=0ʱ�� ��Logout(AT"xxx")��ӡ�ļ����кż���Ϣ
			sprintf(szMsg, "[%02d:%02d:%02d.%03d]�ļ�%s��%04d�У�", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, lpFile, nLine);
		}

		//��ʽ����Ϣ�������������Ϣ
		char* pTemp = szMsg;
		pTemp += strlen(szMsg);
		va_list args;
		va_start(args, lpFormat);
		wvsprintfA(pTemp, lpFormat, args); //vsprintf_s BufSize - strlen(szMsg);
		va_end(args);

		DWORD dwMsgLen = (DWORD)strlen(szMsg);

		//��ȡ��־�ļ���
		char szFileName[MAX_PATH];
		char szExeName[MAX_PATH];
		GetProcessFileName(szExeName);
		sprintf(szFileName, "Log(%s)%d-%d-%d.txt", szExeName, st.wYear, st.wMonth, st.wDay);

		//�ж��ļ����Ƿ���ͬ������Ƿ���Ч
		//�жϲ�ͬ������Ч�� ��رյ�ǰ�ļ��� �������ļ�
		static char s_szFileName[MAX_PATH] = { 0 };
		static HANDLE s_hFile = INVALID_HANDLE_VALUE;

		//�����Զ�����־�ļ���
#ifdef _SETFILENAME
		strcpy(szFileName, FILENAME);
#endif//_SETFILENAME

		BOOL bNew = ((strcmp(s_szFileName, szFileName) != 0) ||(s_hFile == INVALID_HANDLE_VALUE));

#ifdef  _DEBUGCONSOLE //����̨���
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
#endif //  _DEBUGCONSOLE //����̨���

	}

};




char* GetProPath();

#endif