// SelectDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "SAutomation.h"
#include "SelectDlg.h"
#include "afxdialogex.h"


// CSelectDlg ダイアログ

IMPLEMENT_DYNAMIC(CSelectDlg, CDialogEx)

CSelectDlg::CSelectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSelectDlg::IDD, pParent)
{

}

CSelectDlg::~CSelectDlg()
{
}

void CSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSelectDlg, CDialogEx)
END_MESSAGE_MAP()


// CSelectDlg メッセージ ハンドラー


BOOL CSelectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	CRect rectDlg;
	CRect rectParent;
	GetWindowRect(&rectDlg);
	::GetWindowRect(g_hWnd,&rectParent);
	CRect rectDisp;
	SystemParametersInfo( SPI_GETWORKAREA, NULL, &rectDisp, NULL);

	MoveWindow(rectDisp.Width()-rectDlg.Width(), rectDisp.Height()-rectDlg.Height()-rectParent.Height(),rectDlg.Width(),rectDlg.Height());

	for(int iSelection=0;iSelection<MAX_SELECTION; iSelection++)
	{

		((CButton*)GetDlgItem(IDC_BUTTON_SELECT_KEY_1+iSelection))->SetWindowText(_T(""));
		((CButton*)GetDlgItem(IDC_STATIC_SELECT_FILENAME_1+iSelection))->SetWindowText(_T(""));

		if(m_sSelectKeys[iSelection].GetLength()<=0){continue;}
		if(m_sSelectFiles[iSelection].GetLength()<=0){continue;}
		
		((CButton*)GetDlgItem(IDC_BUTTON_SELECT_KEY_1+iSelection))->SetWindowText(m_sSelectKeys[iSelection]);
		((CButton*)GetDlgItem(IDC_STATIC_SELECT_FILENAME_1+iSelection))->SetWindowText(m_sSelectFiles[iSelection]);
		CString sTemp;
		sTemp.Format(_T("%s"),m_sSelectKeys[iSelection]);
		sTemp.MakeLower();

		if(sTemp.GetLength()>=2)
		{
			if(sTemp.CompareNoCase(_T("F1"))==0){m_dwHotKeys[iSelection] = VK_F1;}
			if(sTemp.CompareNoCase(_T("F2"))==0){m_dwHotKeys[iSelection] = VK_F2;}
			if(sTemp.CompareNoCase(_T("F3"))==0){m_dwHotKeys[iSelection] = VK_F3;}
			if(sTemp.CompareNoCase(_T("F4"))==0){m_dwHotKeys[iSelection] = VK_F4;}
			if(sTemp.CompareNoCase(_T("F5"))==0){m_dwHotKeys[iSelection] = VK_F5;}
			if(sTemp.CompareNoCase(_T("F6"))==0){m_dwHotKeys[iSelection] = VK_F6;}
			if(sTemp.CompareNoCase(_T("F7"))==0){m_dwHotKeys[iSelection] = VK_F7;}
			if(sTemp.CompareNoCase(_T("F8"))==0){m_dwHotKeys[iSelection] = VK_F8;}
			if(sTemp.CompareNoCase(_T("F9"))==0){m_dwHotKeys[iSelection] = VK_F9;}
			if(sTemp.CompareNoCase(_T("F10"))==0){m_dwHotKeys[iSelection] = VK_F10;}
			if(sTemp.CompareNoCase(_T("F11"))==0){m_dwHotKeys[iSelection] = VK_F11;}
			if(sTemp.CompareNoCase(_T("F12"))==0){m_dwHotKeys[iSelection] = VK_F12;}
			if(sTemp.CompareNoCase(_T("Insert"))==0){m_dwHotKeys[iSelection] = VK_INSERT;}

		}
		else
		{
			if((char(sTemp.GetAt(0))>='a') && (char(sTemp.GetAt(0))<='z')){m_dwHotKeys[iSelection] = char(sTemp.GetAt(0))-'a'+0x41;}
			if((char(sTemp.GetAt(0))>='0') && (char(sTemp.GetAt(0))<='9')){m_dwHotKeys[iSelection] = char(sTemp.GetAt(0))-'0'+0x30;}
		}

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


BOOL CSelectDlg::PreTranslateMessage(MSG* pMsg)
{

	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		{
			for(int iSelection=0; iSelection<MAX_SELECTION; iSelection++)
			{
				if(pMsg->wParam==m_dwHotKeys[iSelection] )
				{
					m_sResultFileName.Format(_T("%s"), m_sSelectFiles[iSelection]);
					CDialog::OnOK();
					return TRUE;
				}
			}
					m_sResultFileName.Format(_T(""));
			CDialog::OnCancel();
			break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
