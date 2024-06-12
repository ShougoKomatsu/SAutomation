#pragma once
#include "stdafx.h"
#include "resource.h"
// CInputDialog2 ダイアログ

class CInputDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CInputDialog)

public:
		CStringArray m_saParam;
	
	CString m_sMessage;
	int m_iTimeOutMilliSec;
	BYTE* m_byKey;
	int m_iKeyNum;
	CString* m_sLabel;
	CString m_sResultLabel;

	BOOL PerseParameter();
	CInputDialog(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CInputDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_INPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
};

