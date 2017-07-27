#pragma once


// CommonDlg dialog
//继承于dlg
//below is must function
class CommonDlg : public CDialogEx
{
	//这里用这个是因为利于动态创建
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
