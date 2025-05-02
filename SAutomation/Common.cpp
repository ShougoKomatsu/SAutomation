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

//FILE* g_f[MAX_THREAD];
//CStdioFile* g_cf[MAX_THREAD];
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
	if(combo->GetCount()<=0)
	{
		combo->ResetContent();
		combo->AddString(_T(" "));
		combo->AddString(_T("0"));
		combo->AddString(_T("1"));
		combo->AddString(_T("2"));
		combo->AddString(_T("3"));
		combo->AddString(_T("4"));
		combo->AddString(_T("5"));
		combo->AddString(_T("6"));
		combo->AddString(_T("7"));
		combo->AddString(_T("8"));
		combo->AddString(_T("9"));
		combo->AddString(_T("a"));
		combo->AddString(_T("b"));
		combo->AddString(_T("c"));
		combo->AddString(_T("d"));
		combo->AddString(_T("e"));
		combo->AddString(_T("f"));
		combo->AddString(_T("g"));
		combo->AddString(_T("h"));
		combo->AddString(_T("i"));
		combo->AddString(_T("j"));
		combo->AddString(_T("k"));
		combo->AddString(_T("l"));
		combo->AddString(_T("m"));
		combo->AddString(_T("n"));
		combo->AddString(_T("o"));
		combo->AddString(_T("p"));
		combo->AddString(_T("q"));
		combo->AddString(_T("r"));
		combo->AddString(_T("s"));
		combo->AddString(_T("t"));
		combo->AddString(_T("u"));
		combo->AddString(_T("v"));
		combo->AddString(_T("w"));
		combo->AddString(_T("x"));
		combo->AddString(_T("y"));
		combo->AddString(_T("z"));
		combo->AddString(_T("F1"));
		combo->AddString(_T("F2"));
		combo->AddString(_T("F3"));
		combo->AddString(_T("F4"));
		combo->AddString(_T("F5"));
		combo->AddString(_T("F6"));
		combo->AddString(_T("F7"));
		combo->AddString(_T("F8"));
		combo->AddString(_T("F9"));
		combo->AddString(_T("F10"));
		combo->AddString(_T("F11"));
		combo->AddString(_T("F12"));
		combo->AddString(_T("Insert"));
	}

	BOOL bFound;
	bFound = FALSE;
	for(int i=0; i<combo->GetCount(); i++)
	{
		TCHAR tch[8];
		combo->GetLBText(i, tch);
		if(sHotkey.Compare(tch)==0){combo->SetCurSel(i); bFound = TRUE;break;}
	}
	if(bFound != TRUE){combo->SetCurSel(0);}
}
void AutomationInfo::ReadSettings()
{

	TCHAR szData[MAX_PATH];
	CString sFilePath;

	sFilePath.Format(_T("%s\\SAutomation.ini"), m_sDir); 

	GetPrivateProfileString(_T("Mouse"),_T("ClickDulation"),_T("50"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	g_iClickDulation = _ttoi(szData);

	for(int iScene=0; iScene<MAX_NORMAL_THREAD; iScene++)
	{
		CString sSection;
		sSection.Format(_T("Operation %d"), iScene+1);
		GetPrivateProfileString(sSection,_T("FileName"),_T(""),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		m_OpeInfo[iScene].sFileName.Format(_T("%s"),szData);

		GetPrivateProfileString(sSection,_T("Hotkey"),_T(" "),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		m_OpeInfo[iScene].sHotkey.Format(_T("%s"), szData);

		GetPrivateProfileString(sSection,_T("UseCtrl"),_T("1"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		if(wcscmp(szData,_T("1"))==0){m_OpeInfo[iScene].bUseCtrl=TRUE;}
		else{m_OpeInfo[iScene].bUseCtrl=FALSE;}

		GetPrivateProfileString(sSection,_T("UseShift"),_T("1"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		if(wcscmp(szData,_T("1"))==0){m_OpeInfo[iScene].bUseShift=TRUE;}
		else{m_OpeInfo[iScene].bUseShift=FALSE;}

		GetPrivateProfileString(sSection,_T("UseAlt"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		if(wcscmp(szData,_T("1"))==0){m_OpeInfo[iScene].bUseAlt=TRUE;}
		else{m_OpeInfo[iScene].bUseAlt=FALSE;}

		GetPrivateProfileString(sSection,_T("UseWin"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		if(wcscmp(szData,_T("1"))==0){m_OpeInfo[iScene].bUseWin=TRUE;}
		else{m_OpeInfo[iScene].bUseWin=FALSE;}
	}


	for(int iExScene=0; iExScene<MAX_EX_THREAD; iExScene++)
	{
		int iScene=MAX_NORMAL_THREAD+iExScene;
		CString sSection;
		sSection.Format(_T("ExOperation %d"), iExScene+1);
		GetPrivateProfileString(sSection,_T("FileName"),_T(""),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		m_OpeInfo[iScene].sFileName.Format(_T("%s"),szData);

		GetPrivateProfileString(sSection,_T("Hotkey"),_T(" "),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		m_OpeInfo[iScene].sHotkey.Format(_T("%s"), szData);

		GetPrivateProfileString(sSection,_T("UseCtrl"),_T("1"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		if(wcscmp(szData,_T("1"))==0){m_OpeInfo[iScene].bUseCtrl=TRUE;}
		else{m_OpeInfo[iScene].bUseCtrl=FALSE;}

		GetPrivateProfileString(sSection,_T("UseShift"),_T("1"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		if(wcscmp(szData,_T("1"))==0){m_OpeInfo[iScene].bUseShift=TRUE;}
		else{m_OpeInfo[iScene].bUseShift=FALSE;}

		GetPrivateProfileString(sSection,_T("UseAlt"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		if(wcscmp(szData,_T("1"))==0){m_OpeInfo[iScene].bUseAlt=TRUE;}
		else{m_OpeInfo[iScene].bUseAlt=FALSE;}

		GetPrivateProfileString(sSection,_T("UseWin"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		if(wcscmp(szData,_T("1"))==0){m_OpeInfo[iScene].bUseWin=TRUE;}
		else{m_OpeInfo[iScene].bUseWin=FALSE;}
		for(int iSelect=0; iSelect<MAX_SELECTION; iSelect++)
		{
			CString sKeyKey;
			CString sKeyFile;
			CString sDataKey;
			CString sDataFile;
			sKeyKey.Format(_T("SelectKey%d"),iSelect+1);
			sKeyFile.Format(_T("SelectFile%d"),iSelect+1);
			GetPrivateProfileString(sSection,sKeyKey,_T(""),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
			sDataKey.Format(_T("%s"), szData);
			GetPrivateProfileString(sSection,sKeyFile,_T(""),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
			sDataFile.Format(_T("%s"), szData);
			if((sDataKey.GetLength()>0) && (sDataFile.GetLength()>0))
			{
				this->m_sSelectKeys[iExScene][iSelect].Format(_T("%s"), sDataKey);
				this->m_sSelectFiles[iExScene][iSelect].Format(_T("%s"), sDataFile);
			}
		}
	}


	GetPrivateProfileString(_T("Hotkey"),_T("EnableKey"),_T(" "),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_sHotkeyEnable.Format(_T("%s"), szData);

	GetPrivateProfileString(_T("Hotkey"),_T("Enable"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	if(wcscmp(szData,_T("1"))==0){m_bEnableHotkey=TRUE;}
	else{m_bEnableHotkey=FALSE;}

	GetPrivateProfileString(_T("Common"),_T("AutoMnimize"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	if(wcscmp(szData,_T("1"))==0){m_bAutoMinimize=TRUE;}
	else{m_bAutoMinimize=FALSE;}

	GetPrivateProfileString(_T("Common"),_T("Log"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	if(wcscmp(szData,_T("1"))==0){m_bLog=TRUE;}
	else{m_bLog=FALSE;}

	GetPrivateProfileString(_T("Common"),_T("LogLevel"),_T("1"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	m_iLogLevel=_ttoi(szData);
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

	GetPrivateProfileString(_T("Common"),_T("MinimizeToTasktray"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	if(wcscmp(szData,_T("1"))==0){m_bMinimizeToTaskTray=TRUE;}
	else{m_bMinimizeToTaskTray=FALSE;}
}

void AutomationInfo::SaveSettings()
{

	CString sFilePath;
	sFilePath.Format(_T("%s\\SAutomation.ini"), m_sDir); 

	CString sUseCtrl;
	CString sUseShift;
	CString sUseAlt;
	CString sUseWin;

	for(int iScene = 0; iScene<MAX_NORMAL_THREAD; iScene++)
	{
		CString sSection;
		sSection.Format(_T("Operation %d"), iScene+1);

		WritePrivateProfileString(sSection,_T("FileName"),m_OpeInfo[iScene].sFileName,sFilePath);

		WritePrivateProfileString(sSection,_T("Hotkey"),m_OpeInfo[iScene].sHotkey, sFilePath);

		sUseCtrl.Format(_T("%d"), m_OpeInfo[iScene].bUseCtrl);
		sUseShift.Format(_T("%d"), m_OpeInfo[iScene].bUseShift);
		sUseAlt.Format(_T("%d"), m_OpeInfo[iScene].bUseAlt);
		sUseWin.Format(_T("%d"), m_OpeInfo[iScene].bUseWin);

		WritePrivateProfileString(sSection,_T("UseCtrl"),sUseCtrl,sFilePath);
		WritePrivateProfileString(sSection,_T("UseShift"),sUseShift,sFilePath);
		WritePrivateProfileString(sSection,_T("UseAlt"),sUseAlt,sFilePath);
		WritePrivateProfileString(sSection,_T("UseWin"),sUseWin,sFilePath);

	}



	for(int iExScene=0; iExScene<MAX_EX_THREAD; iExScene++)
	{
		int iScene=MAX_NORMAL_THREAD+iExScene;
		CString sSection;
		sSection.Format(_T("ExOperation %d"), iExScene+1);

		WritePrivateProfileString(sSection,_T("Hotkey"),m_OpeInfo[iScene].sHotkey, sFilePath);

		sUseCtrl.Format(_T("%d"), m_OpeInfo[iScene].bUseCtrl);
		sUseShift.Format(_T("%d"), m_OpeInfo[iScene].bUseShift);
		sUseAlt.Format(_T("%d"), m_OpeInfo[iScene].bUseAlt);
		sUseWin.Format(_T("%d"), m_OpeInfo[iScene].bUseWin);

		WritePrivateProfileString(sSection,_T("UseCtrl"),sUseCtrl,sFilePath);
		WritePrivateProfileString(sSection,_T("UseShift"),sUseShift,sFilePath);
		WritePrivateProfileString(sSection,_T("UseAlt"),sUseAlt,sFilePath);
		WritePrivateProfileString(sSection,_T("UseWin"),sUseWin,sFilePath);


		for(int iSelect=0; iSelect<MAX_SELECTION; iSelect++)
		{
			CString sKeyKey;
			CString sKeyFile;
			CString sDataKey;
			CString sDataFile;
			sKeyKey.Format(_T("SelectKey%d"),iSelect+1);
			sKeyFile.Format(_T("SelectFile%d"),iSelect+1);
			WritePrivateProfileString(sSection,sKeyKey,this->m_sSelectKeys[iExScene][iSelect],sFilePath);
			WritePrivateProfileString(sSection,sKeyFile,this->m_sSelectFiles[iExScene][iSelect],sFilePath);

		}
	}

	WritePrivateProfileString(_T("Hotkey"),_T("EnableKey"),m_sHotkeyEnable,sFilePath);

	if(m_bEnableHotkey==TRUE)
	{
		WritePrivateProfileString(_T("Hotkey"),_T("Enable"),_T("1"),sFilePath);
	}
	else
	{
		WritePrivateProfileString(_T("Hotkey"),_T("Enable"),_T("0"),sFilePath);
	}


	if(m_bAutoMinimize==TRUE)
	{
		WritePrivateProfileString(_T("Common"),_T("AutoMnimize"),_T("1"),sFilePath);
	}
	else
	{
		WritePrivateProfileString(_T("Common"),_T("AutoMnimize"),_T("0"),sFilePath);
	}

	if(m_bLog==1)
	{
		WritePrivateProfileString(_T("Common"),_T("Log"),_T("1"),sFilePath);
	}
	else
	{
		WritePrivateProfileString(_T("Common"),_T("Log"),_T("0"),sFilePath);
	}
	if(m_bMinimizeToTaskTray==1)
	{
		WritePrivateProfileString(_T("Common"),_T("MinimizeToTasktray"),_T("1"),sFilePath);
	}
	else
	{
		WritePrivateProfileString(_T("Common"),_T("MinimizeToTasktray"),_T("0"),sFilePath);
	}

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
	if(m_bEnableHotkey != autoInfoIn->m_bEnableHotkey)
	{
		return FALSE;
	}
	if(m_bAutoMinimize != autoInfoIn->m_bAutoMinimize)
	{
		return FALSE;
	}
	if(m_sHotkeyEnable.Compare(autoInfoIn->m_sHotkeyEnable) != 0)
	{
		return FALSE;
	}
	if(m_iLogLevel != autoInfoIn->m_iLogLevel)
	{
		return FALSE;
	}
	if(m_bLog != autoInfoIn->m_bLog)
	{
		return FALSE;
	}
	if(m_dwHotKeyEnable != autoInfoIn->m_dwHotKeyEnable)
	{
		return FALSE;
	}
	if(m_sDir.Compare(autoInfoIn->m_sDir) != 0)
	{
		return FALSE;
	}

	if(m_bMinimizeToTaskTray != autoInfoIn->m_bMinimizeToTaskTray)
	{
		return FALSE;
	}
	for(int i=0; i<MAX_THREAD; i++)
	{
		if(m_OpeInfo[i].IsSameAs(&(autoInfoIn->m_OpeInfo[i])) == FALSE)
		{
			return FALSE;
		}
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
	int iParam[2];
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

	if(sInput.CompareNoCase(_T("��"))==0){return VK_LEFT;}
	if(sInput.CompareNoCase(_T("<-"))==0){return VK_LEFT;}
	if(sInput.CompareNoCase(_T("Left"))==0){return VK_LEFT;}

	if(sInput.CompareNoCase(_T("��"))==0){return VK_UP;}
	if(sInput.CompareNoCase(_T("Up"))==0){return VK_UP;}

	if(sInput.CompareNoCase(_T("��"))==0){return VK_RIGHT;}
	if(sInput.CompareNoCase(_T("->"))==0){return VK_RIGHT;}
	if(sInput.CompareNoCase(_T("Right"))==0){return VK_RIGHT;}

	if(sInput.CompareNoCase(_T("��"))==0){return VK_DOWN;}
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