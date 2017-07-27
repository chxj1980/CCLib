// CommonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfcCommonClass.h"
#include "CommonDlg.h"
#include "afxdialogex.h"
#include "resource.h"


// CommonDlg dialog

IMPLEMENT_DYNAMIC(CommonDlg, CDialogEx)

CommonDlg::CommonDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_COM, pParent)
{

}

CommonDlg::~CommonDlg()
{
}

void CommonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listBox);
	DDX_Control(pDX, IDC_TREE_COM, m_treeItem);
}


BEGIN_MESSAGE_MAP(CommonDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CommonDlg message handlers

void CommonDlg::OnDraw(CDC* /*pDC*/)
{
	//CmfcCommonClassDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	//m_listBox.AddString(_T("123"));
	//m_listBox.AddString(_T("English"));

	// TODO: add draw code for native data here
}


BOOL CommonDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	////初始化dlg
	m_listBox.AddString(_T("123"));
	m_listBox.AddString(_T("English"));

	//动态读取文本文件中的数据写入到listbox
	FILE *fp = fopen("ListBox.txt","rt");
	if (fp == NULL)
	{
		MessageBox(_T("cant open file"), _T("error"), MB_OK);
		return FALSE;
	}

	//字符串处理函数

	//insert in ListBox
	int length = 10;
	for (int i = 0; i < length; i++)
	{
		m_listBox.AddString(_T("吃那"));
	}

	//

	//close file pointer
	fclose(fp);
	return TRUE;
}
