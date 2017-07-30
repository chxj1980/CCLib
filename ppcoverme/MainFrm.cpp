
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ppcoverme.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_FILE_PROCESSTEST, &CMainFrame::OnFileProcesstest)
	ON_COMMAND(ID_FILE_PROCESSSYSCODE, &CMainFrame::OnFileProcesssyscode)
	ON_COMMAND(ID_FILE_MAP, &CMainFrame::OnFileMap)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}



//Windows进程间通讯的方法有很多：管道、邮件槽、剪切板、共享内存、消息、套接字、RPC、DDE等。

#define WM_MY_MSG (WM_USER + 1000)     //响应进程收不到，只能收到注册的消息，或者是系统消息
const UINT WM_CONTROLPRINT = RegisterWindowMessage(L"reg_data");

//向另一个进程发送消息
//发送自定义消息
void CMainFrame::OnFileProcesstest()
{
	// TODO: Add your command handler code here
	CString  strBuffer;
	//m_Edit.GetWindowText(strBuffer);
	strBuffer = "CNN";

	if (strBuffer.GetLength() == 0)
	{
		return;
	}

	COPYDATASTRUCT  Temp;

	Temp.dwData = 0;
	Temp.cbData = strBuffer.GetLength() * sizeof(WCHAR);      //  sizeof    没有算  '\0'
	Temp.lpData = strBuffer.GetBuffer();


	HWND hFindWindow = ::FindWindow(NULL, L"ScreenCapAndCV");

	if (hFindWindow == NULL)
	{
		return;
	}
	//::SendMessage(hFindWindow, WM_COPYDATA, NULL, (LPARAM)&Temp);
	::SendMessage(hFindWindow, WM_CONTROLPRINT, NULL, (LPARAM)&Temp);
}


//发送系统消息
void CMainFrame::OnFileProcesssyscode()
{
	// TODO: Add your command handler code here
	CString  strBuffer;
	//m_Edit.GetWindowText(strBuffer);
	strBuffer = "CNN";

	if (strBuffer.GetLength() == 0)
	{
		return;
	}

	COPYDATASTRUCT  Temp;

	Temp.dwData = 0;
	Temp.cbData = strBuffer.GetLength() * sizeof(WCHAR);      //  sizeof    没有算  '\0'
	Temp.lpData = strBuffer.GetBuffer();


	HWND hFindWindow = ::FindWindow(NULL, L"ScreenCapAndCV");

	if (hFindWindow == NULL)
	{
		return;
	}
	//::SendMessage(hFindWindow, WM_COPYDATA, NULL, (LPARAM)&Temp);
	::SendMessage(hFindWindow, WM_COPYDATA, NULL, (LPARAM)&Temp);
}


//文件映射进程消息
/*
	如何将一个文件映射到自己的缓冲区中。

	打开文件-->计算文件大小-->创建内存映射对象Mapping-->mapofviewfile映射到自己的缓冲区中

	通过文件映射来进行读写文件操作较为方便。
*/


void CMainFrame::OnFileMap()
{
	// TODO: Add your command handler code here
	int nRetCode = 0;

	//打开文件
	HANDLE hFile = CreateFile(L"D:\\Demo.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//获取文件大小
	DWORD dwHigh = 0;
	DWORD dwLow = 0;
	dwLow = GetFileSize(hFile, &dwHigh);
	dwLow = ((dwLow + 4095) / 4096) * 4096;
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return;
	}

	//创建内存对象
	HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, dwHigh, dwLow, NULL);
	if (hMapping == NULL)
	{
		CloseHandle(hFile);
	}

	//映射到缓冲区
	char* szBuffer = NULL;
	szBuffer = (char*)MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (szBuffer != NULL)
	{
		/*cout << szBuffer << endl;*/
	}
	*(szBuffer + 1) = 'w';
	//*szBuffer + 1 = 's';

	UnmapViewOfFile(szBuffer);
	CloseHandle(hMapping);
	CloseHandle(hFile);
}


//管道通讯
#define READ_PIPE   L"\\\\.\\pipe\\ReadPipe"
#define WRITE_PIPE  L"\\\\.\\pipe\\WritePipe"      //   管道命名

typedef struct _USER_CONTEXT_
{
	HANDLE hPipe;
	HANDLE hEvent;
}USER_CONTEXT, *PUSER_CONTEXT;


USER_CONTEXT  Context[2] = { 0 };

HANDLE hThread[2] = { 0 };

BOOL  WritePipe();
BOOL  ReadPipe();

BOOL  bOk = FALSE;

DWORD WINAPI WritePipeThread(LPVOID LPParam);
DWORD WINAPI ReadPipeThread(LPVOID LPParam);
//int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
//{
//	int nRetCode = 0;
//	HANDLE hPipe = NULL;
//	if (WritePipe() == FALSE)
//	{
//		return -1;
//	}
//	if (ReadPipe() == FALSE)
//	{
//		return -1;
//	}
//	int iIndex = 0;
//	while (TRUE)
//	{
//		if (bOk == TRUE)
//		{
//			SetEvent(Context[0].hEvent);
//			SetEvent(Context[1].hEvent);
//
//			Sleep(1);
//		}
//		iIndex = WaitForMultipleObjects(2, hThread, TRUE, 5000);
//
//		if (iIndex == WAIT_TIMEOUT)
//		{
//			continue;
//		}
//		else
//		{
//			break;
//		}
//	}
//	int i = 0;
//	for (i = 0; i < 2; i++)
//	{
//		CloseHandle(Context[i].hEvent);
//		CloseHandle(Context[i].hPipe);
//	}
//	CloseHandle(hThread[0]);
//	CloseHandle(hThread[1]);
//	//cout << "Exit" << endl;
//	return nRetCode;
//}


BOOL  WritePipe()
{
	HANDLE hWritePipe = NULL;

	hWritePipe = CreateNamedPipe(
		WRITE_PIPE,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE |
		PIPE_READMODE_MESSAGE |
		PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		MAX_PATH,
		MAX_PATH,
		0,
		NULL);


	if (hWritePipe == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	Context[0].hEvent = hEvent;
	Context[0].hPipe = hWritePipe;
	hThread[0] = CreateThread(NULL, 0, WritePipeThread, NULL, 0, NULL);

	return TRUE;
}

BOOL  ReadPipe()
{
	HANDLE hReadPipe = NULL;

	hReadPipe = CreateNamedPipe(
		READ_PIPE,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_MESSAGE |
		PIPE_READMODE_MESSAGE |
		PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		MAX_PATH,
		MAX_PATH,
		0,
		NULL);

	if (hReadPipe == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	Context[1].hEvent = hEvent;
	Context[1].hPipe = hReadPipe;
	hThread[1] = CreateThread(NULL, 0, ReadPipeThread, NULL, 0, NULL);

	return TRUE;

}

DWORD WINAPI ReadPipeThread(LPVOID LPParam)
{
	HANDLE hEvent = Context[1].hEvent;
	HANDLE hReadPipe = Context[1].hPipe;
	DWORD  dwReturn = 0;
	char szBuffer[MAX_PATH] = { 0 };
	int  iIndex = 0;
	while (TRUE)
	{
		iIndex = WaitForSingleObject(hEvent, 30);
		iIndex = iIndex - WAIT_OBJECT_0;
		if (iIndex == WAIT_FAILED || iIndex == 0)
		{
			break;
		}
		if (ReadFile(hReadPipe, szBuffer, MAX_PATH, &dwReturn, NULL))
		{
			szBuffer[dwReturn] = '\0';
			//cout << szBuffer << endl;
		}
		else
		{
			if (GetLastError() == ERROR_INVALID_HANDLE)
			{
				break;
			}
		}
	}
	return 0;
}

DWORD WINAPI WritePipeThread(LPVOID LPParam)
{
	HANDLE hEvent = Context[0].hEvent;
	HANDLE hWritePipe = Context[0].hPipe;
	DWORD  dwReturn = 0;
	char szBuffer[MAX_PATH] = { 0 };
	int  iIndex = 0;
	while (TRUE)
	{
		iIndex = WaitForSingleObject(hEvent, 30);
		iIndex = iIndex - WAIT_OBJECT_0;
		if (iIndex == WAIT_FAILED || iIndex == 0)
		{
			break;
		}
		//cin >> szBuffer;
		if (WriteFile(hWritePipe, szBuffer, strlen(szBuffer), &dwReturn, NULL))
		{
		}
		else
		{
			if (GetLastError() == ERROR_INVALID_HANDLE)
			{
				break;
			}
		}
	}
	return 0;
}


//共享内存
//using namespace std;
//int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
//{
//	int nRetCode = 0;
//	char szBuffer[] = "Shine";
//	HANDLE hMapping = CreateFileMapping(NULL, NULL, PAGE_READWRITE, 0, 4096, L"ShareMemory");
//	LPVOID lpBase = MapViewOfFile(hMapping, FILE_MAP_WRITE | FILE_MAP_READ, 0, 0, 0);
//	strcpy((char*)lpBase, szBuffer);
//	Sleep(20000);
//	UnmapViewOfFile(lpBase);
//	CloseHandle(hMapping);
//	return nRetCode;
//}


//邮件槽
#define  MAIL_SLOT_NAME  L"\\\\.\\mailslot\\Name" 
HANDLE  hReadMailSlot = INVALID_HANDLE_VALUE;
DWORD WINAPI ReadMail();
//int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
//{
//	int nRetCode = 0;
//	HANDLE hReadThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReadMail, NULL, 0, NULL);
//	Sleep(INFINITE);
//	if (hReadMailSlot != INVALID_HANDLE_VALUE)
//	{
//		CloseHandle(hReadMailSlot);
//	}
//	Sleep(10);
//	return nRetCode;
//}

DWORD WINAPI ReadMail()
{
	hReadMailSlot = CreateMailslot(MAIL_SLOT_NAME, 0, 0, NULL);
	if (hReadMailSlot == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	//查看油槽的信息
	DWORD cbMessage = 0;
	DWORD cMessage = 0;
	BOOL bOk = FALSE;
	char*  szBuffer = NULL;
	DWORD  dwReturn = 0;
	while (TRUE)
	{
		bOk = GetMailslotInfo(hReadMailSlot, NULL, &cbMessage, &cMessage, NULL);
		if (bOk == FALSE)
		{
			break;
		}
		if (cMessage == 0)
		{
			continue;
		}
		else
		{
			if (szBuffer != NULL)
			{
				free(szBuffer);
				szBuffer = NULL;
			}
			szBuffer = (char*)malloc(sizeof(char)*cbMessage + 1);
			if (ReadFile(hReadMailSlot,
				szBuffer,
				cbMessage,
				&dwReturn,
				NULL) == TRUE)
			{
				szBuffer[dwReturn] = '\0';
				if (strcmp(szBuffer, "Exit") == 0)
				{
					break;
				}
				//cout << szBuffer << endl;
			}

		}
	}
	//cout << "ReadThread Exit" << endl;
}