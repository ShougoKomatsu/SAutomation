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
	m_bReset=FALSE;
}

CSelectDlg::~CSelectDlg()
{
}

void CSelectDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_SELECT_COMBO_KEY_1, (m_combo[0]));
	DDX_Control(pDX, IDC_SELECT_COMBO_KEY_2, (m_combo[1]));
	DDX_Control(pDX, IDC_SELECT_COMBO_KEY_3, (m_combo[2]));
	DDX_Control(pDX, IDC_SELECT_COMBO_KEY_4, (m_combo[3]));
	DDX_Control(pDX, IDC_SELECT_COMBO_KEY_5, (m_combo[4]));
	DDX_Control(pDX, IDC_SELECT_COMBO_KEY_6, (m_combo[5]));
	DDX_Control(pDX, IDC_SELECT_COMBO_KEY_7, (m_combo[6]));
	DDX_Control(pDX, IDC_SELECT_COMBO_KEY_8, (m_combo[7]));

	if(m_bReset==FALSE)
	{
		for(int iSelect=0; iSelect<8; iSelect++)
		{
			m_combo[iSelect].ResetContent();
		}
		m_bReset=TRUE;
	}
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSelectDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SELECT_BUTTON_KEY_1, &CSelectDlg::OnBnClickedButtonSelectKey1)
	ON_BN_CLICKED(IDC_SELECT_BUTTON_KEY_2, &CSelectDlg::OnBnClickedButtonSelectKey2)
	ON_BN_CLICKED(IDC_SELECT_BUTTON_KEY_3, &CSelectDlg::OnBnClickedButtonSelectKey3)
	ON_BN_CLICKED(IDC_SELECT_BUTTON_KEY_4, &CSelectDlg::OnBnClickedButtonSelectKey4)
	ON_BN_CLICKED(IDC_SELECT_BUTTON_KEY_5, &CSelectDlg::OnBnClickedButtonSelectKey5)
	ON_BN_CLICKED(IDC_SELECT_BUTTON_KEY_6, &CSelectDlg::OnBnClickedButtonSelectKey6)
	ON_BN_CLICKED(IDC_SELECT_BUTTON_KEY_7, &CSelectDlg::OnBnClickedButtonSelectKey7)
	ON_BN_CLICKED(IDC_SELECT_BUTTON_KEY_8, &CSelectDlg::OnBnClickedButtonSelectKey8)
	ON_CBN_SELCHANGE(IDC_SELECT_COMBO_KEY_1, &CSelectDlg::OnCbnSelchangeSelectCombo1)
	ON_CBN_SELCHANGE(IDC_SELECT_COMBO_KEY_2, &CSelectDlg::OnCbnSelchangeSelectCombo2)
	ON_CBN_SELCHANGE(IDC_SELECT_COMBO_KEY_3, &CSelectDlg::OnCbnSelchangeSelectCombo3)
	ON_CBN_SELCHANGE(IDC_SELECT_COMBO_KEY_4, &CSelectDlg::OnCbnSelchangeSelectCombo4)
	ON_CBN_SELCHANGE(IDC_SELECT_COMBO_KEY_5, &CSelectDlg::OnCbnSelchangeSelectCombo5)
	ON_CBN_SELCHANGE(IDC_SELECT_COMBO_KEY_6, &CSelectDlg::OnCbnSelchangeSelectCombo6)
	ON_CBN_SELCHANGE(IDC_SELECT_COMBO_KEY_7, &CSelectDlg::OnCbnSelchangeSelectCombo7)
	ON_CBN_SELCHANGE(IDC_SELECT_COMBO_KEY_8, &CSelectDlg::OnCbnSelchangeSelectCombo8)
	ON_BN_CLICKED(IDOK, &CSelectDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_SELECT_BUTTON_SELECTFILE_1, &CSelectDlg::OnBnClickedButtonSelectionFile1)
	ON_BN_CLICKED(IDC_SELECT_BUTTON_SELECTFILE_2, &CSelectDlg::OnBnClickedButtonSelectionFile2)
	ON_BN_CLICKED(IDC_SELECT_BUTTON_SELECTFILE_3, &CSelectDlg::OnBnClickedButtonSelectionFile3)
	ON_BN_CLICKED(IDC_SELECT_BUTTON_SELECTFILE_4, &CSelectDlg::OnBnClickedButtonSelectionFile4)
	ON_BN_CLICKED(IDC_SELECT_BUTTON_SELECTFILE_5, &CSelectDlg::OnBnClickedButtonSelectionFile5)
	ON_BN_CLICKED(IDC_SELECT_BUTTON_SELECTFILE_6, &CSelectDlg::OnBnClickedButtonSelectionFile6)
	ON_BN_CLICKED(IDC_SELECT_BUTTON_SELECTFILE_7, &CSelectDlg::OnBnClickedButtonSelectionFile7)
	ON_BN_CLICKED(IDC_SELECT_BUTTON_SELECTFILE_8, &CSelectDlg::OnBnClickedButtonSelectionFile8)
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
		if(m_iModeOperate==1)
		{
			((CButton*)GetDlgItem(IDC_SELECT_BUTTON_KEY_1+iSelection))->ShowWindow(SW_SHOW);
			((CButton*)GetDlgItem(IDC_SELECT_COMBO_KEY_1+iSelection))->ShowWindow(SW_HIDE);
			((CButton*)GetDlgItem(IDOK))->ShowWindow(SW_HIDE);
			for(int iSelect=0; iSelect<MAX_SELECTION; iSelect++)
			{
				((CButton*)GetDlgItem(IDC_SELECT_BUTTON_SELECTFILE_1 +iSelection))->ShowWindow(SW_HIDE);
			}

		}
		else
		{
			((CButton*)GetDlgItem(IDC_SELECT_BUTTON_KEY_1+iSelection))->ShowWindow(SW_HIDE);
			((CButton*)GetDlgItem(IDC_SELECT_COMBO_KEY_1+iSelection))->ShowWindow(SW_SHOW);

			for(int iSelect=0; iSelect<MAX_SELECTION; iSelect++)
			{
				SetComboItem(&m_combo[iSelect],m_sSelectKeys[iSelect]);
			}

		}

		((CButton*)GetDlgItem(IDC_SELECT_BUTTON_KEY_1+iSelection))->SetWindowText(_T(""));
		((CButton*)GetDlgItem(IDC_SELECT_STATIC_FILENAME_1+iSelection))->SetWindowText(_T(""));

		if(m_sSelectKeys[iSelection].GetLength()<=0){continue;}
		if(m_sSelectFiles[iSelection].GetLength()<=0){continue;}
		
		((CButton*)GetDlgItem(IDC_SELECT_BUTTON_KEY_1+iSelection))->SetWindowText(m_sSelectKeys[iSelection]);
		((CButton*)GetDlgItem(IDC_SELECT_STATIC_FILENAME_1+iSelection))->SetWindowText(m_sSelectFiles[iSelection]);
		CString sTemp;
		sTemp.Format(_T("%s"),m_sSelectKeys[iSelection]);
		sTemp.MakeLower();

		m_dwHotKeys[iSelection] = GetVKeyCode(sTemp);

	}
	SetForegroundWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


BOOL CSelectDlg::PreTranslateMessage(MSG* pMsg)
{

	switch(pMsg->message)
	{
	case WM_KEYDOWN:
		{

			if(m_iModeOperate==1)
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
				return TRUE;
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSelectDlg::OnBnClickedButtonSelectKey1(){m_sResultFileName.Format(_T("%s"), m_sSelectFiles[0]); CDialog::OnOK();}
void CSelectDlg::OnBnClickedButtonSelectKey2(){m_sResultFileName.Format(_T("%s"), m_sSelectFiles[1]); CDialog::OnOK();}
void CSelectDlg::OnBnClickedButtonSelectKey3(){m_sResultFileName.Format(_T("%s"), m_sSelectFiles[2]); CDialog::OnOK();}
void CSelectDlg::OnBnClickedButtonSelectKey4(){m_sResultFileName.Format(_T("%s"), m_sSelectFiles[3]); CDialog::OnOK();}
void CSelectDlg::OnBnClickedButtonSelectKey5(){m_sResultFileName.Format(_T("%s"), m_sSelectFiles[4]); CDialog::OnOK();}
void CSelectDlg::OnBnClickedButtonSelectKey6(){m_sResultFileName.Format(_T("%s"), m_sSelectFiles[5]); CDialog::OnOK();}
void CSelectDlg::OnBnClickedButtonSelectKey7(){m_sResultFileName.Format(_T("%s"), m_sSelectFiles[6]); CDialog::OnOK();}
void CSelectDlg::OnBnClickedButtonSelectKey8(){m_sResultFileName.Format(_T("%s"), m_sSelectFiles[7]); CDialog::OnOK();}

void CSelectDlg::OnCbnSelchangeSelectCombo1(){}
void CSelectDlg::OnCbnSelchangeSelectCombo2(){}
void CSelectDlg::OnCbnSelchangeSelectCombo3(){}
void CSelectDlg::OnCbnSelchangeSelectCombo4(){}
void CSelectDlg::OnCbnSelchangeSelectCombo5(){}
void CSelectDlg::OnCbnSelchangeSelectCombo6(){}
void CSelectDlg::OnCbnSelchangeSelectCombo7(){}
void CSelectDlg::OnCbnSelchangeSelectCombo8(){}


void CSelectDlg::OnBnClickedOk()
{
	if(m_iModeOperate==0)
	{
		UpdateData(TRUE);
		for(int iSelect=0; iSelect<MAX_SELECTION; iSelect++)
		{
			TCHAR tchKey[16];
			TCHAR tchFile[MAX_PATH];

			m_combo[iSelect].GetLBText(m_combo[iSelect].GetCurSel(),tchKey);
			((CButton*)GetDlgItem(IDC_SELECT_STATIC_FILENAME_1+iSelect))->GetWindowText(tchFile,MAX_PATH-1);

			m_sSelectKeys[iSelect].Format(_T("%s"), tchKey);
			m_sSelectFiles[iSelect].Format(_T("%s"), tchFile);
		}
	}
	CDialogEx::OnOK();
}


void CSelectDlg::FileSelect(int iSelect)
{
	CString sMacroFolderPath;
	sMacroFolderPath.Format(_T("%s\\Macro"),m_sDir);

	CFileDialog cf(TRUE);
	cf.m_ofn.lpstrInitialDir = sMacroFolderPath;
	if(cf.DoModal()!=IDOK){ return;}

	CString sFolder;
	CString sFolderPath;
	CString sFilePath;
	CString sFileName;
	sFilePath.Format(_T("%s"), cf.GetPathName());
	GetDirectory(sFilePath,&sFolderPath,&sFileName);

	if(sMacroFolderPath.CompareNoCase(sFolderPath)==0)
	{
		sFolder.Format(_T(""));
	}
	else
	{
		sFolder.Format(_T("%s\\"),sFolderPath.Right( sFolderPath.GetLength()-sMacroFolderPath.GetLength()-1));
	}
	CString sText;
	sText.Format(_T("%s%s"), sFolder, sFileName);
	((CButton*)GetDlgItem(IDC_SELECT_STATIC_FILENAME_1+iSelect))->SetWindowText(sText);

}

void CSelectDlg::OnBnClickedButtonSelectionFile1(){FileSelect(0);}
void CSelectDlg::OnBnClickedButtonSelectionFile2(){FileSelect(1);}
void CSelectDlg::OnBnClickedButtonSelectionFile3(){FileSelect(2);}
void CSelectDlg::OnBnClickedButtonSelectionFile4(){FileSelect(3);}
void CSelectDlg::OnBnClickedButtonSelectionFile5(){FileSelect(4);}
void CSelectDlg::OnBnClickedButtonSelectionFile6(){FileSelect(5);}
void CSelectDlg::OnBnClickedButtonSelectionFile7(){FileSelect(6);}
void CSelectDlg::OnBnClickedButtonSelectionFile8(){FileSelect(7);}
