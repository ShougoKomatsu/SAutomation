#include "stdafx.h"
#include "Common.h"
#include "MouseAutomation.h"
CString g_sDir;
AutomationInfo g_Automation;
HHOOK g_hhook=NULL;
int g_iR=0;
int g_iC=0;
int g_iOriginR=0;
int g_iOriginC=0;
HWND g_hWnd;
int g_iWatching=0;


HANDLE g_hHotkey[MAX_THREAD];
UTFReaderWriter g_utfW[MAX_THREAD];
CString g_sLogFilePath[MAX_THREAD];
int g_iLogLevel[MAX_THREAD];
double g_dSpeedMult=1.0;


int g_iClickDulation = 50;
CInputDialog g_cInput;

BOOL GetFileName(CString sFilePath, CString* sFileName)
{
	int iFoundPosLast;
	int iFoundPos;

	iFoundPos = 0;
	while(iFoundPos>=0)
	{
		iFoundPosLast = iFoundPos;
		iFoundPos = sFilePath.Find(_T("\\"), iFoundPosLast+1);
	}
	CString sExeName;
	if(iFoundPosLast==0){return FALSE;}
	sFileName->Format(_T("%s"), sFilePath.Right(sFilePath.GetLength()-iFoundPosLast-1));
	return TRUE;
}

void SetComboItem(CComboBox* combo, CString sHotkey)
{
	CString sTemp;
	if(combo->GetCount()<=0)
	{
		combo->ResetContent();

		combo->AddString(_T(" "));
		for(int i=0; i<=9; i++){sTemp.Format(_T("%d"),i); combo->AddString(sTemp);}
		for(char c='a'; c<='z'; c++){sTemp.Format(_T("%c"),c); combo->AddString(sTemp);}
		for(int i=1; i<=12; i++){sTemp.Format(_T("F%d"),i); combo->AddString(sTemp);}
		combo->AddString(_T("Insert"));
	}

	BOOL bFound;
	bFound = FALSE;
	for(int i=0; i<combo->GetCount(); i++)
	{
		wchar_t tch[8];
		combo->GetLBText(i, tch);
		if(sHotkey.Compare(tch)==0){combo->SetCurSel(i); bFound = TRUE;break;}
	}
	if(bFound != TRUE){combo->SetCurSel(0);}
}
void AutomationInfo::ReadSettings()
{

	wchar_t szData[MAX_PATH];
	CString sFilePath;

	sFilePath.Format(_T("%s\\SAutomation.ini"), m_sDir); 

	GetPrivateProfileString(_T("Mouse"),_T("ClickDulation"),_T("50"),szData,sizeof(szData)/sizeof(wchar_t),sFilePath);
	g_iClickDulation = _wtoi(szData);

	for(int iScene=0; iScene<MAX_NORMAL_THREAD; iScene++)
	{
		CString sSection;
		sSection.Format(_T("Operation %d"), iScene+1);
		GetPrivateProfileString(sSection,_T("FileName"),_T(""),szData,sizeof(szData)/sizeof(wchar_t),sFilePath);
		m_OpeInfo[iScene].sFileName.Format(_T("%s"),szData);

		GetPrivateProfileString(sSection,_T("Hotkey"),_T(" "),szData,sizeof(szData)/sizeof(wchar_t),sFilePath);
		m_OpeInfo[iScene].sHotkey.Format(_T("%s"), szData);

		GetPrivateProfileStringAsBool(sSection, _T("UseCtrl"), TRUE, &(m_OpeInfo[iScene].bUseCtrl), sFilePath);
		GetPrivateProfileStringAsBool(sSection, _T("UseShift"), TRUE, &(m_OpeInfo[iScene].bUseShift), sFilePath);
		GetPrivateProfileStringAsBool(sSection, _T("UseAlt"), FALSE, &(m_OpeInfo[iScene].bUseAlt), sFilePath);
		GetPrivateProfileStringAsBool(sSection, _T("UseWin"), FALSE, &(m_OpeInfo[iScene].bUseWin), sFilePath);
		
		GetPrivateProfileStringAsBool(sSection, _T("DisableHalt"), FALSE, &(m_OpeInfo[iScene].m_bDisableHalt), sFilePath);
		GetPrivateProfileString(sSection,_T("OperationMode"),_T(" "),szData,sizeof(szData)/sizeof(wchar_t),sFilePath);
		m_OpeInfo[iScene].m_iOperationMode=_wtoi(szData);
	}


	for(int iExScene=0; iExScene<MAX_EX_THREAD; iExScene++)
	{
		int iScene=MAX_NORMAL_THREAD+iExScene;
		CString sSection;
		sSection.Format(_T("ExOperation %d"), iExScene+1);
		GetPrivateProfileString(sSection,_T("FileName"),_T(""),szData,sizeof(szData)/sizeof(wchar_t),sFilePath);
		m_OpeInfo[iScene].sFileName.Format(_T("%s"),szData);

		GetPrivateProfileString(sSection,_T("Hotkey"),_T(" "),szData,sizeof(szData)/sizeof(wchar_t),sFilePath);
		m_OpeInfo[iScene].sHotkey.Format(_T("%s"), szData);
		
		GetPrivateProfileStringAsBool(sSection, _T("UseCtrl"), TRUE, &(m_OpeInfo[iScene].bUseCtrl), sFilePath);
		GetPrivateProfileStringAsBool(sSection, _T("UseShift"), TRUE, &(m_OpeInfo[iScene].bUseShift), sFilePath);
		GetPrivateProfileStringAsBool(sSection, _T("UseAlt"), FALSE, &(m_OpeInfo[iScene].bUseAlt), sFilePath);
		GetPrivateProfileStringAsBool(sSection, _T("UseWin"), FALSE, &(m_OpeInfo[iScene].bUseWin), sFilePath);
		
		GetPrivateProfileStringAsBool(sSection, _T("DisableHalt"), FALSE, &(m_OpeInfo[iScene].m_bDisableHalt), sFilePath);
		GetPrivateProfileString(sSection,_T("OperationMode"),_T(" "),szData,sizeof(szData)/sizeof(wchar_t),sFilePath);
		m_OpeInfo[iScene].m_iOperationMode=_wtoi(szData);

		for(int iSelect=0; iSelect<MAX_SELECTION; iSelect++)
		{
			CString sKeyKey;
			CString sKeyFile;
			CString sDataKey;
			CString sDataFile;
			sKeyKey.Format(_T("SelectKey%d"),iSelect+1);
			sKeyFile.Format(_T("SelectFile%d"),iSelect+1);
			GetPrivateProfileString(sSection,sKeyKey,_T(""),szData,sizeof(szData)/sizeof(wchar_t),sFilePath);
			sDataKey.Format(_T("%s"), szData);
			GetPrivateProfileString(sSection,sKeyFile,_T(""),szData,sizeof(szData)/sizeof(wchar_t),sFilePath);
			sDataFile.Format(_T("%s"), szData);
			if((sDataKey.GetLength()>0) && (sDataFile.GetLength()>0))
			{
				this->m_sSelectKeys[iExScene][iSelect].Format(_T("%s"), sDataKey);
				this->m_sSelectFiles[iExScene][iSelect].Format(_T("%s"), sDataFile);
			}
		}
	}


	GetPrivateProfileString(_T("Hotkey"),_T("EnableKey"),_T(" "),szData,sizeof(szData)/sizeof(wchar_t),sFilePath);
	m_sHotkeyEnable.Format(_T("%s"), szData);

	GetPrivateProfileStringAsBool(_T("Hotkey"), _T("Enable"), FALSE, &(m_bEnableHotkey), sFilePath);
	GetPrivateProfileStringAsBool(_T("Common"), _T("AutoMnimize"), FALSE, &(m_bAutoMinimize), sFilePath);
	GetPrivateProfileStringAsBool(_T("Common"), _T("MinimizeToTasktray"), FALSE, &(m_bMinimizeToTaskTray), sFilePath);
	GetPrivateProfileStringAsBool(_T("Common"), _T("Log"), FALSE, &(m_bLog), sFilePath);


	GetPrivateProfileString(_T("Common"),_T("LogLevel"),_T("1"),szData,sizeof(szData)/sizeof(wchar_t),sFilePath);
	m_iLogLevel=_wtoi(szData);
	if(m_iLogLevel<1){m_iLogLevel=1;}
	if(m_iLogLevel>5){m_iLogLevel=5;}

	for(int iScene= 0; iScene<MAX_NORMAL_THREAD; iScene++)
	{
		g_hThread[iScene] = NULL;
		m_OpeInfo[iScene].dwHotKey = GetVKeyCode(m_OpeInfo[iScene].sHotkey);
	}

	for(int iExScene= 0; iExScene<MAX_EX_THREAD; iExScene++)
	{
		int iScene=MAX_NORMAL_THREAD+iExScene;
		g_hThread[iScene] = NULL;
		m_OpeInfo[iScene].dwHotKey = GetVKeyCode(m_OpeInfo[iScene].sHotkey);
	}

	if(m_sHotkeyEnable.GetLength()==1)
	{
		m_dwHotKeyEnable = GetVKeyCode(m_sHotkeyEnable);
	}
	if(m_iLogLevel<1){m_iLogLevel=1;}
	if(m_iLogLevel>5){m_iLogLevel=5;}
	
}



void AutomationInfo::SaveSettings()
{

	CString sFilePath;
	sFilePath.Format(_T("%s\\SAutomation.ini"), m_sDir); 

	for(int iScene = 0; iScene<MAX_NORMAL_THREAD; iScene++)
	{
		CString sSection;
		sSection.Format(_T("Operation %d"), iScene+1);

		WritePrivateProfileString(sSection,_T("FileName"),m_OpeInfo[iScene].sFileName,sFilePath);
		WritePrivateProfileString(sSection,_T("Hotkey"),m_OpeInfo[iScene].sHotkey, sFilePath);
		
		WritePrivateProfileStringAsBool(sSection, _T("UseCtrl"), m_OpeInfo[iScene].bUseCtrl, sFilePath);
		WritePrivateProfileStringAsBool(sSection, _T("UseShift"), m_OpeInfo[iScene].bUseShift, sFilePath);
		WritePrivateProfileStringAsBool(sSection, _T("UseAlt"), m_OpeInfo[iScene].bUseAlt, sFilePath);
		WritePrivateProfileStringAsBool(sSection, _T("UseWin"), m_OpeInfo[iScene].bUseWin, sFilePath);

		WritePrivateProfileStringAsBool(sSection, _T("DisableHalt"), m_OpeInfo[iScene].m_bDisableHalt, sFilePath);

		CString sData;
		sData.Format(_T("%d"),m_OpeInfo[iScene].m_iOperationMode);
		WritePrivateProfileString(sSection,_T("OperationMode"),sData,sFilePath);
	}



	for(int iExScene=0; iExScene<MAX_EX_THREAD; iExScene++)
	{
		int iScene=MAX_NORMAL_THREAD+iExScene;
		CString sSection;
		sSection.Format(_T("ExOperation %d"), iExScene+1);

		WritePrivateProfileString(sSection,_T("Hotkey"),m_OpeInfo[iScene].sHotkey, sFilePath);

		WritePrivateProfileStringAsBool(sSection, _T("UseCtrl"), m_OpeInfo[iScene].bUseCtrl, sFilePath);
		WritePrivateProfileStringAsBool(sSection, _T("UseShift"), m_OpeInfo[iScene].bUseShift, sFilePath);
		WritePrivateProfileStringAsBool(sSection, _T("UseAlt"), m_OpeInfo[iScene].bUseAlt, sFilePath);
		WritePrivateProfileStringAsBool(sSection, _T("UseWin"), m_OpeInfo[iScene].bUseWin, sFilePath);
		
		WritePrivateProfileStringAsBool(sSection, _T("DisableHalt"), m_OpeInfo[iScene].m_bDisableHalt, sFilePath);

		CString sData;
		sData.Format(_T("%d"),m_OpeInfo[iScene].m_iOperationMode);
		WritePrivateProfileString(sSection,_T("OperationMode"),sData,sFilePath);

		for(int iSelect=0; iSelect<MAX_SELECTION; iSelect++)
		{
			CString sKeyKey;
			CString sKeyFile;
			sKeyKey.Format(_T("SelectKey%d"),iSelect+1);
			sKeyFile.Format(_T("SelectFile%d"),iSelect+1);
			WritePrivateProfileString(sSection,sKeyKey,this->m_sSelectKeys[iExScene][iSelect],sFilePath);
			WritePrivateProfileString(sSection,sKeyFile,this->m_sSelectFiles[iExScene][iSelect],sFilePath);
		}
	}

	WritePrivateProfileString(_T("Hotkey"),_T("EnableKey"), m_sHotkeyEnable, sFilePath);
	
	WritePrivateProfileStringAsBool(_T("Hotkey"),_T("Enable"),m_bEnableHotkey,sFilePath);
	WritePrivateProfileStringAsBool(_T("Common"),_T("AutoMnimize"),m_bAutoMinimize,sFilePath);
	WritePrivateProfileStringAsBool(_T("Common"),_T("Log"),m_bLog,sFilePath);
	WritePrivateProfileStringAsBool(_T("Common"),_T("MinimizeToTasktray"),m_bMinimizeToTaskTray,sFilePath);

	CString sData;
	sData.Format(_T("%d"),m_iLogLevel);
	WritePrivateProfileString(_T("Common"),_T("LogLevel"),sData,sFilePath);

}
BOOL AutomationInfo::Copy(AutomationInfo* autoInfoIn)
{
	m_bEnableHotkey=autoInfoIn->m_bEnableHotkey;
	m_bAutoMinimize=autoInfoIn->m_bAutoMinimize;
	m_sHotkeyEnable.Format(_T("%s"),autoInfoIn->m_sHotkeyEnable);
	m_iLogLevel=autoInfoIn->m_iLogLevel;
	m_bLog=autoInfoIn->m_bLog;
	m_dwHotKeyEnable=autoInfoIn->m_dwHotKeyEnable;
	m_bMinimizeToTaskTray=autoInfoIn->m_bMinimizeToTaskTray;
	m_sDir.Format(_T("%s"),autoInfoIn->m_sDir);

	for(int i=0; i<MAX_THREAD; i++)
	{
		m_OpeInfo[i].Copy(&(autoInfoIn->m_OpeInfo[i]));
	}

	for(int iExSecene=0; iExSecene<MAX_EX_THREAD; iExSecene++)
	{
		for(int iSelection=0;iSelection<MAX_SELECTION; iSelection++)
		{
			m_sSelectKeys[iExSecene][iSelection].Format(_T("%s"),autoInfoIn->m_sSelectKeys[iExSecene][iSelection]);
			m_sSelectFiles[iExSecene][iSelection].Format(_T("%s"),autoInfoIn->m_sSelectFiles[iExSecene][iSelection]);
		}
	}

	return TRUE;
}

BOOL AutomationInfo::IsSameAs(AutomationInfo* autoInfoIn)
{
	if(m_bEnableHotkey != autoInfoIn->m_bEnableHotkey){return FALSE;}
	if(m_bAutoMinimize != autoInfoIn->m_bAutoMinimize){return FALSE;}
	if(m_sHotkeyEnable.Compare(autoInfoIn->m_sHotkeyEnable) != 0){return FALSE;}
	if(m_iLogLevel != autoInfoIn->m_iLogLevel){return FALSE;}
	if(m_bLog != autoInfoIn->m_bLog){return FALSE;}
	if(m_dwHotKeyEnable != autoInfoIn->m_dwHotKeyEnable){return FALSE;}
	if(m_sDir.Compare(autoInfoIn->m_sDir) != 0){return FALSE;}
	if(m_bMinimizeToTaskTray != autoInfoIn->m_bMinimizeToTaskTray){return FALSE;}

	for(int i=0; i<MAX_THREAD; i++)
	{
		if(m_OpeInfo[i].IsSameAs(&(autoInfoIn->m_OpeInfo[i])) == FALSE){return FALSE;}
	}

	for(int iExSecene=0; iExSecene<MAX_EX_THREAD; iExSecene++)
	{
		for(int iSelection=0;iSelection<MAX_SELECTION; iSelection++)
		{
			if(m_sSelectKeys[iExSecene][iSelection].Compare(autoInfoIn->m_sSelectKeys[iExSecene][iSelection]) != 0){return FALSE;};
			if(m_sSelectFiles[iExSecene][iSelection].Compare(autoInfoIn->m_sSelectFiles[iExSecene][iSelection]) != 0){return FALSE;};
		}
	}

	return TRUE;
}
void AutomationInfo::Operate(int iScene)
{
	ChangeMouseOrigin(0, 0);

	DWORD dwThreadID;
	if(g_hThread[iScene] != NULL)
	{
		DWORD dwResult;
		dwResult = WaitForSingleObject(g_hThread[iScene], 0);
		if(dwResult != STATUS_WAIT_0){return;}
	}
	g_sFilePath[iScene].Format(_T("%s\\Macro\\%s"),g_Automation.m_sDir, g_Automation.m_OpeInfo[iScene].sFileName);
	int iParam[3];
	iParam[2] = g_Automation.m_OpeInfo[iScene].m_bDisableHalt;
	iParam[1] = m_iLogLevel<<PARAM_LOGLEVEL_SHIFT;
	iParam[0] = iScene+1;
	g_Automation.m_OpeInfo[iScene].m_bRunning=TRUE;

	g_hThread[iScene] = CreateThread(NULL, 0, CommandThread, (LPVOID)(iParam), 0, &dwThreadID);

	while(iParam[0]!=0){Sleep(10);}

}

void SetComboItemCtrl(CComboBox* combo, OperationInfo* op)
{
	if(combo->GetCount()<=0)
	{
		combo->ResetContent();
		combo->AddString(_T(" "));
		combo->AddString(_T("Ctrl"));
		combo->AddString(_T("Shift"));
		combo->AddString(_T("Alt"));
		combo->AddString(_T("Win"));
	}

	const int NOTHING = 0;
	const int CTRL = 1;
	const int SHIFT = 2;
	const int ALT = 4;
	const int WIN = 8;

	int iCombi = NOTHING;
	int iKeyCount = 0;
	if(op->bUseCtrl==TRUE){iKeyCount++; iCombi |= CTRL;}
	if(op->bUseShift==TRUE){iKeyCount++;iCombi |= SHIFT;}
	if(op->bUseAlt==TRUE){iKeyCount++;iCombi |= ALT;}
	if(op->bUseWin==TRUE){iKeyCount++;iCombi |= WIN;}

	if(iKeyCount >= 3){combo->SetCurSel(0); return;}

	if((iCombi&WIN) == WIN)		{if(iCombi != WIN){iCombi -= WIN;}}
	if((iCombi&ALT) == ALT)		{if(iCombi != ALT){iCombi -= ALT;}}
	if((iCombi&SHIFT) == SHIFT) {if(iCombi != SHIFT){iCombi -= SHIFT;}}

	switch(iCombi)
	{
	case NOTHING:{combo->SetCurSel(0); return;}
	case CTRL:{combo->SetCurSel(1); return;}
	case SHIFT:{combo->SetCurSel(2); return;}
	case ALT:{combo->SetCurSel(3); return;}
	case WIN:{combo->SetCurSel(4); return;}

	default:{combo->SetCurSel(0); return;}
	}
	combo->SetCurSel(0); 
	return;

}

void SetComboItemShift(CComboBox* combo,OperationInfo* op)
{
	if(combo->GetCount()<=0)
	{
		combo->ResetContent();
		combo->AddString(_T(" "));
		combo->AddString(_T("Shift"));
		combo->AddString(_T("Alt"));
		combo->AddString(_T("Win"));
	}

	const int NOTHING = 0;
	const int CTRL = 1;
	const int SHIFT = 2;
	const int ALT = 4;
	const int WIN = 8;

	int iCombi = NOTHING;
	int iKeyCount = 0;
	if(op->bUseCtrl==TRUE){iKeyCount++;iCombi |= CTRL;}
	if(op->bUseShift==TRUE){iKeyCount++;iCombi |= SHIFT;}
	if(op->bUseAlt==TRUE){iKeyCount++;iCombi |= ALT;}
	if(op->bUseWin==TRUE){iKeyCount++;iCombi |= WIN;}

	if(iKeyCount != 2){combo->SetCurSel(0); return;}

	if((iCombi&CTRL) == CTRL)	{iCombi -= CTRL;}
	if((iCombi&SHIFT) == SHIFT) {if(iCombi != SHIFT){iCombi -= SHIFT;}}
	if((iCombi&ALT) == ALT)		{if(iCombi != ALT){iCombi -= ALT;}}
	if((iCombi&WIN) == WIN)		{if(iCombi != WIN){iCombi -= WIN;}}

	switch(iCombi)
	{
	case NOTHING:{combo->SetCurSel(0); return;}
	case CTRL:{combo->SetCurSel(0); return;}
	case SHIFT:{combo->SetCurSel(1); return;}
	case ALT:{combo->SetCurSel(2); return;}
	case WIN:{combo->SetCurSel(3); return;}

	default:{combo->SetCurSel(0); return;}
	}
	combo->SetCurSel(0); 
	return;
}

LRESULT CALLBACK MouseHookProc(int code, WPARAM wParam, LPARAM lParam)
{
	switch(wParam)
	{
	case WM_MOUSEMOVE:
		{
			g_iR = ((LPMSLLHOOKSTRUCT)lParam)->pt.y-g_iOriginR;
			g_iC = ((LPMSLLHOOKSTRUCT)lParam)->pt.x-g_iOriginC;
			break;
		}
	default: break;
	}
	return CallNextHookEx(g_hhook, code, wParam, lParam);
}


BOOL GetFileProperty(CString sFilePath, CTime* ctCreationTime, CTime* ctLastAccessTime, CTime* ctLastWriteTime)
{
	WIN32_FIND_DATAW FileData;

	HANDLE hFile=FindFirstFile(sFilePath, &FileData);
	if(hFile == INVALID_HANDLE_VALUE){return FALSE;}

	if(ctCreationTime != NULL)
	{
		*ctCreationTime = FileData.ftCreationTime;
	}

	if(ctLastAccessTime != NULL)
	{
		*ctLastAccessTime = FileData.ftLastAccessTime;
	}

	if(ctLastWriteTime != NULL)
	{
		*ctLastWriteTime = FileData.ftLastWriteTime;
	}

	FindClose(hFile);

	return TRUE;
}


const CString ConvertTimeToString(const SYSTEMTIME st, const CString sArg)
{
	CString sOut;

	int iPlace=0;
	sOut.Format(_T(""));
	while(iPlace<=sArg.GetLength())
	{
		if(sArg.Mid(iPlace,1).CompareNoCase(_T("Y"))==0)
		{
			if(sArg.Mid(iPlace,4).CompareNoCase(_T("YYYY"))==0){CString sTemp; sTemp.Format(_T("%d"),st.wYear); sOut+=sTemp; iPlace+=4;}
			else if(sArg.Mid(iPlace,2).CompareNoCase(_T("YY"))==0){CString sTemp; sTemp.Format(_T("%d"),(st.wYear%100)); sOut+=sTemp;iPlace+=2;}
			else{return _T("");}
			continue;
		}
		if(sArg.Mid(iPlace,1).Compare(_T("M"))==0)
		{
			if(sArg.Mid(iPlace,2).Compare(_T("MM"))==0){CString sTemp; sTemp.Format(_T("%02d"),st.wMonth); sOut+=sTemp; iPlace+=2;}
			else{CString sTemp; sTemp.Format(_T("%d"),st.wMonth); sOut+=sTemp;iPlace+=1;}
			continue;
		}
		if(sArg.Mid(iPlace,1).CompareNoCase(_T("D"))==0)
		{
			if(sArg.Mid(iPlace,2).CompareNoCase(_T("dd"))==0){CString sTemp; sTemp.Format(_T("%02d"),st.wDay); sOut+=sTemp;iPlace+=2;}
			else{CString sTemp; sTemp.Format(_T("%d"),st.wDay); sOut+=sTemp;iPlace+=1;}
			continue;
		}
		if(sArg.Mid(iPlace,1).CompareNoCase(_T("h"))==0)
		{
			if(sArg.Mid(iPlace,2).CompareNoCase(_T("hh"))==0){CString sTemp; sTemp.Format(_T("%02d"),st.wHour); sOut+=sTemp;iPlace+=2;}
			else{CString sTemp; sTemp.Format(_T("%d"),st.wHour); sOut+=sTemp;iPlace+=1;}
			continue;
		}
		if(sArg.Mid(iPlace,1).Compare(_T("m"))==0)
		{
			if(sArg.Mid(iPlace,2).Compare(_T("mm"))==0){CString sTemp; sTemp.Format(_T("%02d"),st.wMinute); sOut+=sTemp;iPlace+=2;}
			else{CString sTemp; sTemp.Format(_T("%d"),st.wMinute); sOut+=sTemp;iPlace+=1;}
			continue;
		}
		if(sArg.Mid(iPlace,1).CompareNoCase(_T("s"))==0)
		{
			if(sArg.Mid(iPlace,2).CompareNoCase(_T("ss"))==0){CString sTemp; sTemp.Format(_T("%02d"),st.wSecond); sOut+=sTemp;iPlace+=2;}
			else{CString sTemp; sTemp.Format(_T("%d"),st.wSecond); sOut+=sTemp;iPlace+=1;}
			continue;
		}
		sOut+=sArg.Mid(iPlace,1);
		iPlace++;
	}
	return sOut;
}

DWORD GetVKeyCode(const CString sIn)
{
	CString sInput;
	sInput.Format(_T("%s"),sIn);
	sInput.MakeLower();

	if(sInput.CompareNoCase(_T("Ctrl"))==0){return VK_CONTROL;}
	if(sInput.CompareNoCase(_T("Shift"))==0){return VK_SHIFT;}
	if(sInput.CompareNoCase(_T("Alt"))==0){return VK_MENU;}

	if(sInput.CompareNoCase(_T("©"))==0){return VK_LEFT;}
	if(sInput.CompareNoCase(_T("<-"))==0){return VK_LEFT;}
	if(sInput.CompareNoCase(_T("Left"))==0){return VK_LEFT;}

	if(sInput.CompareNoCase(_T("ª"))==0){return VK_UP;}
	if(sInput.CompareNoCase(_T("Up"))==0){return VK_UP;}

	if(sInput.CompareNoCase(_T("¨"))==0){return VK_RIGHT;}
	if(sInput.CompareNoCase(_T("->"))==0){return VK_RIGHT;}
	if(sInput.CompareNoCase(_T("Right"))==0){return VK_RIGHT;}

	if(sInput.CompareNoCase(_T("«"))==0){return VK_DOWN;}
	if(sInput.CompareNoCase(_T("Down"))==0){return VK_DOWN;}

	if(sInput.GetLength()>=2)
	{
		if(sInput.CompareNoCase(_T("F1"))==0){return VK_F1;}
		if(sInput.CompareNoCase(_T("F2"))==0){return VK_F2;}
		if(sInput.CompareNoCase(_T("F3"))==0){return VK_F3;}
		if(sInput.CompareNoCase(_T("F4"))==0){return VK_F4;}
		if(sInput.CompareNoCase(_T("F5"))==0){return VK_F5;}
		if(sInput.CompareNoCase(_T("F6"))==0){return VK_F6;}
		if(sInput.CompareNoCase(_T("F7"))==0){return VK_F7;}
		if(sInput.CompareNoCase(_T("F8"))==0){return VK_F8;}
		if(sInput.CompareNoCase(_T("F9"))==0){return VK_F9;}
		if(sInput.CompareNoCase(_T("F10"))==0){return VK_F10;}
		if(sInput.CompareNoCase(_T("F11"))==0){return VK_F11;}
		if(sInput.CompareNoCase(_T("F12"))==0){return VK_F12;}
		if(sInput.CompareNoCase(_T("f13"))==0){return VK_F13;}
		if(sInput.CompareNoCase(_T("f14"))==0){return VK_F14;}
		if(sInput.CompareNoCase(_T("f15"))==0){return VK_F15;}
		if(sInput.CompareNoCase(_T("f16"))==0){return VK_F16;}
		if(sInput.CompareNoCase(_T("f17"))==0){return VK_F17;}
		if(sInput.CompareNoCase(_T("f18"))==0){return VK_F18;}
		if(sInput.CompareNoCase(_T("f19"))==0){return VK_F19;}
		if(sInput.CompareNoCase(_T("f20"))==0){return VK_F20;}
		if(sInput.CompareNoCase(_T("f21"))==0){return VK_F21;}
		if(sInput.CompareNoCase(_T("f22"))==0){return VK_F22;}
		if(sInput.CompareNoCase(_T("f23"))==0){return VK_F23;}
		if(sInput.CompareNoCase(_T("f24"))==0){return VK_F24;}

		if(sInput.CompareNoCase(_T("LShift"))==0){return VK_SHIFT;}
		if(sInput.CompareNoCase(_T("RShift"))==0){return VK_SHIFT;}
		if(sInput.CompareNoCase(_T("LCtrl"))==0){return VK_CONTROL;}
		if(sInput.CompareNoCase(_T("RCtrl"))==0){return VK_CONTROL;}
		if(sInput.CompareNoCase(_T("LAlt"))==0){return VK_MENU;}
		if(sInput.CompareNoCase(_T("RAlt"))==0){return VK_MENU;}

		if(sInput.CompareNoCase(_T("Tab"))==0){return VK_TAB;}
		if(sInput.CompareNoCase(_T("Enter"))==0){return VK_RETURN;}
		if(sInput.CompareNoCase(_T("Return"))==0){return VK_RETURN;}
		if(sInput.CompareNoCase(_T("Space"))==0){return VK_SPACE;}
		if(sInput.CompareNoCase(_T("BackSpace"))==0){return VK_BACK;}
		if(sInput.CompareNoCase(_T("Jp"))==0){return 0xf3;}

		if(sInput.CompareNoCase(_T("PrintScreen"))==0){return VK_SNAPSHOT;}
		if(sInput.CompareNoCase(_T("ScrollLock"))==0){return VK_SCROLL;}
		if(sInput.CompareNoCase(_T("Pause"))==0){return VK_PAUSE;}
		if(sInput.CompareNoCase(_T("NumLock"))==0){return VK_NUMLOCK;}

		if(sInput.CompareNoCase(_T("Insert"))==0){return VK_INSERT;}
		if(sInput.CompareNoCase(_T("Delete"))==0){return VK_DELETE;}

		if(sInput.CompareNoCase(_T("Home"))==0){return VK_HOME;}
		if(sInput.CompareNoCase(_T("End"))==0){return VK_END;}

		if(sInput.CompareNoCase(_T("PageUp"))==0){return VK_PRIOR;}
		if(sInput.CompareNoCase(_T("PageDown"))==0){return VK_NEXT;}

	}
	else
	{
		if((char(sInput.GetAt(0))>='a') && (char(sInput.GetAt(0))<='z')){return char(sInput.GetAt(0))-'a'+0x41;}
		if((char(sInput.GetAt(0))>='0') && (char(sInput.GetAt(0))<='9')){return char(sInput.GetAt(0))-'0'+0x30;}
	}
	return -1;
}

UTFReaderWriter::UTFReaderWriter()
{
	m_f=NULL;
	m_cstdioF=NULL;
}
UTFReaderWriter::~UTFReaderWriter()
{
	Init();
}
BOOL UTFReaderWriter::Init()
{
	if(m_cstdioF != NULL){m_cstdioF->Close(); delete m_cstdioF; m_cstdioF=NULL;}
	if(m_f != NULL){fclose(m_f);m_f=NULL;}
	return TRUE;
}
BOOL UTFReaderWriter::OpenUTFFile(CString sFilePath, CString sAttribute)
{
	Init();
	try
	{
		errno_t err = _tfopen_s(&m_f, sFilePath ,sAttribute);
		if(err != 0)
		{
			return FALSE;
		}
		m_cstdioF = new CStdioFile(m_f);
	}
	catch(CExpansionVector* e)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL UTFReaderWriter::CloseUTFFile()
{
	Init();
	return TRUE;
}

BOOL UTFReaderWriter::WriteString(CString sLine)
{
	if(m_cstdioF==NULL){return FALSE;}

	if((m_cstdioF)->m_hFile == INVALID_HANDLE_VALUE){return FALSE;}

	(m_cstdioF)->WriteString(sLine);
	return TRUE;
}
BOOL UTFReaderWriter::ReadString(CString* sLine)
{
	if(m_cstdioF==NULL){return FALSE;}

	if((m_cstdioF)->m_hFile == INVALID_HANDLE_VALUE){return FALSE;}
	CString sBuf=_T("");
	sLine->Format(_T(""));
	BOOL bRet = m_cstdioF->ReadString(sBuf);
	if(bRet != TRUE){return FALSE;}

	sLine->Format(_T("%s"), sBuf);

	return TRUE;
}

BOOL ReadUTFFile(CString sFilePath, CStringArray* saData)
{
	CFileFind cFind;
	if(cFind.FindFile(sFilePath)==FALSE){return FALSE;}

	CString sBuf=_T("");
	saData->RemoveAll();

	UTFReaderWriter utfR;
	BOOL bRet = utfR.OpenUTFFile(sFilePath, _T("r, ccs=UTF-8"));
	if(bRet != TRUE){return FALSE;}

	while(utfR.ReadString(&sBuf)== TRUE)
	{
		if(sBuf.GetLength()>0){saData->Add(sBuf);}
	}
	utfR.CloseUTFFile();

	return TRUE;
}

BOOL CStringArrayTrim(CStringArray* saData)
{
	CStringArray saDataLocal;
	CString sDataLine;
	saDataLocal.Copy(*saData);

	saData->RemoveAll();
	for(int i=0; i<saDataLocal.GetCount(); i++)
	{
		sDataLine.Format(_T("%s"), saDataLocal.GetAt(i));
		sDataLine.Trim();
		if(sDataLine.GetLength()>0)
		{
			saData->Add(sDataLine);
		}
	}
	return TRUE;
}

BOOL WritePrivateProfileStringAsBool(CString sSection, CString sKey, BOOL bValue, CString sFilePath)
{
	if(bValue == TRUE)
	{
		return WritePrivateProfileString(sSection,sKey,_T("TRUE"),sFilePath);
	}
	else
	{
		return WritePrivateProfileString(sSection,sKey,_T("FALSE"),sFilePath);
	}
	return FALSE;
}

BOOL GetPrivateProfileStringAsBool(CString sSection, CString sKey, BOOL bDefault, BOOL* bValue, CString sFilePath)
{

	wchar_t szData[MAX_PATH];

	if(bDefault==TRUE)
	{
		GetPrivateProfileString(sSection, sKey, _T("TRUE"),szData,sizeof(szData)/sizeof(wchar_t),sFilePath);
	}
	else
	{
		GetPrivateProfileString(sSection, sKey, _T("FALSE"),szData,sizeof(szData)/sizeof(wchar_t),sFilePath);
	}

	
	CString sTemp;
	sTemp.Format(_T("%s"), szData);
	if(sTemp.CompareNoCase(_T("TRUE"))==0){*bValue=TRUE; return TRUE;}
	if(sTemp.CompareNoCase(_T("1"))==0){*bValue=TRUE; return TRUE;}

	if(sTemp.CompareNoCase(_T("FALSE"))==0){*bValue=FALSE; return TRUE;}
	if(sTemp.CompareNoCase(_T("0"))==0){*bValue=FALSE; return TRUE;}

	*bValue=bDefault;
	return FALSE;
}


BOOL GetDirectory(CString sFilePath, CString* sDir, CString* sFileName)
{
	int iPlace1;
	int iPlace2;

	iPlace2=0;
	while(1)
	{
		iPlace1 = sFilePath.Find(_T("\\"), iPlace2);
		if(iPlace1<0)
		{
			break;
		}
		iPlace2=iPlace1+1;
	}

	if(iPlace2<=0)
	{
		sDir->Format(_T(""));
		sFileName->Format(_T(""));
		return FALSE;
	}
	iPlace2--;

	if(sFilePath.GetLength()-iPlace2-1 <= 0)
	{
		sDir->Format(_T(""));
		sFileName->Format(_T(""));
		return FALSE;
	}

	sDir->Format(_T("%s"), sFilePath.Left(iPlace2));
	sFileName->Format(_T("%s"), sFilePath.Right(sFilePath.GetLength()-iPlace2-1));
	return TRUE;
}