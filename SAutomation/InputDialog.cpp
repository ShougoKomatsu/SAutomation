// InputDialog2.cpp : 実装ファイル
//

#include "stdafx.h"
#include "SAutomation.h"
#include "InputDialog.h"
#include "afxdialogex.h"


// CInputDialog ダイアログ

IMPLEMENT_DYNAMIC(CInputDialog, CDialogEx)

CInputDialog::CInputDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInputDialog::IDD, pParent)
{

}

CInputDialog::~CInputDialog()
{
}

void CInputDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInputDialog, CDialogEx)
END_MESSAGE_MAP()


// CInputDialog メッセージ ハンドラーbr


BOOL CInputDialog::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYUP)
	{
		OnOK();
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
