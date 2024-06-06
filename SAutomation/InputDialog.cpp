// InputDialog2.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "SAutomation.h"
#include "InputDialog.h"
#include "afxdialogex.h"


// CInputDialog �_�C�A���O

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


// CInputDialog ���b�Z�[�W �n���h���[br


BOOL CInputDialog::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYUP)
	{
		OnOK();
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
