#pragma once
#include <windef.h>
#include <ShlObj.h>
#include <iostream>
#include <afxstr.h>
#include <windows.h>
#include <iostream>
#include <tchar.h>

struct CaptureData
{
	BOOL    bCaptureFullScreen;
	char	szCapturePath[MAX_PATH]; // no unicode path support
	char	szCaptureFilename[MAX_PATH];
};

/*
	����Ŀ��
	��ȡ��Ļ�ϣ�Ȼ����ʾ�ڶԻ����ϣ�����ǰ����ʾ�����Ϳ������޼ɵ��ĳ�������


	��ȡ��ĻͼƬ�ķ���
	�и�������˵��������
	һ���ǻ���GDI��һ���ǻ���DX����һ������Windows Media APIץ��

	������������GDI��������ȡ��Ļ
	�����ľ��巽�������϶��У�����ֱ�������ϳ���
	��һ��������CreateDC�������豸�����Ļ����������豸����������Ϊdisplay��
	�ڶ�����CreateCompatibleDC��������display�豸���ݵ��ڴ��豸�����Ļ�����DC�����������ݵ��ڴ��豸��������
	�����������Ļ�ֱ��ʺ�Ҫ��ͼ���������ꡣGetDeviceCaps��ȡ��Ļ�ֱ��ʡ�
	���ġ���CreateCompatibleBitmap����������display�豸���ݵ�λͼ������һ������Ļ�豸��������ݵ�λͼ����
	���塢SelectObject��������λͼѡ���ڴ��豸�������С�
	������BitBlt��������Ļ�豸�����������ڴ��豸�������С�
	���ߡ����SelectObject�õ���Ļλͼ�ľ����
	�ڰˡ���ʾλͼ��

	//Ϊ��ʵ�ִ����ͨ�����������ǰѺ�����װ��Common����������

*/

/*һ��GDI����*/
//1.1
HBITMAP Copybitmap(LPRECT lprect);

void logs(std::string strMes);

//ͼƬ���浽����
/*virtual */BOOL CaptureLolToDesktop(HWND hWnd);

//��Ļ��ͼ����ʵ��  
/*virtual */HBITMAP ScreenCapture(LPSTR filename, WORD bitCount, LPRECT lpRect);

//��������
void CaptureScreen(CaptureData* lpData);

//��ʾ����
BOOL ConfigureCapture(HWND hWndParent, CaptureData* lpData);

//��ͼƬ��ʾ��������




