#pragma once


// CSelectDlg ダイアログ

class CSelectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSelectDlg)

public:
	CSelectDlg(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CSelectDlg();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_SELECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};
