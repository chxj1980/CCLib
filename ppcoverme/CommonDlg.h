#pragma once


// CommonDlg dialog
//�̳���dlg
//below is must function
class CommonDlg : public CDialogEx
{
	//�������������Ϊ���ڶ�̬����
	DECLARE_DYNAMIC(CommonDlg)

public:
	//constructor
	CommonDlg(CWnd* pParent = NULL);   // standard constructor
	//destructor
	virtual ~CommonDlg();

	CListBox m_listBox;

	void CommonDlg::OnDraw(CDC* /*pDC*/);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_COM };
#endif

protected:
	//ddx/ddvsupport
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	//msg
	DECLARE_MESSAGE_MAP()

private:
	CTreeCtrl m_treeItem;
};
