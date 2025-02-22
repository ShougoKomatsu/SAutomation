#include "stdafx.h"
#include "Common.h"
CString g_sDir;
AutomationInfo g_Automation;

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

BOOL ReadUTFFile(CString sFilePath, CString* sData)
{
	CFileFind cFind;
	if(cFind.FindFile(sFilePath)==FALSE){return FALSE;}

	FILE* f;
	CString sBuf;
	CString sDocBuf;

	_tfopen_s(&f, sFilePath,_T("r, ccs=UTF-8"));
	CStdioFile cstdioF(f);
	while(cstdioF.ReadString(sBuf)!= NULL){sDocBuf = sDocBuf + sBuf+_T("\x0d\x0a");}
	cstdioF.Close();
	fclose(f);

	sData->Format(_T("%s"), sDocBuf);
	return TRUE;
}


BOOL ReadTextFile(CString sFilePath, CStringArray* saCommands)
{
	CFileFind cfind;
	BOOL bRet;
	bRet = cfind.FindFile(sFilePath);
	cfind.Close();
	if(bRet != TRUE){return FALSE;}
	

	saCommands->RemoveAll();
	CString sFileDataRaw;
	bRet = ReadUTFFile(sFilePath, &sFileDataRaw);
	if(bRet != TRUE){return FALSE;}

	unsigned long ulFileDataLength;
	long lCR1;
	long lCR2;

	lCR1 = 0;
	ulFileDataLength = sFileDataRaw.GetLength();
	for(unsigned long ulPointer = 0; ulPointer<=ulFileDataLength; ulPointer++)
	{
		lCR2 = sFileDataRaw.Find(_T("\r"),lCR1);
		if(lCR2<=0)
		{
			lCR2 = sFileDataRaw.Find(_T("\n"),lCR1);
			if(lCR2<=0)
			{
				CString sBufTemp;
				sBufTemp.Trim(_T("\r"));
				sBufTemp.Trim(_T("\n"));
				sBufTemp.Format(_T("%s"), sFileDataRaw.Mid(lCR1, sFileDataRaw.GetLength()-lCR1));
				if(sBufTemp.GetLength()>0)
				{
					if(sBufTemp.GetLength()>0){saCommands->Add(sBufTemp);}
				}
				return TRUE;
			}
		}

		CString sLineData;
		sLineData.Format(_T("%s"), sFileDataRaw.Mid(lCR1, lCR2-lCR1));
		sLineData.Trim(_T("\r"));
		sLineData.Trim(_T("\n"));
		if(sLineData.GetLength()>0)
		{
			if(sLineData.GetLength()>0){saCommands->Add(sLineData);}
		}
		lCR1=lCR2+1;
	}

	//‚±‚±‚É‚Í—ˆ‚È‚¢
	return FALSE;
}

void SetComboItem(CComboBox* combo, CString sHotkey)
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

	sFilePath.Format(_T("%s\\SAutomation.ini"), g_Automation.m_sDir); 

	GetPrivateProfileString(_T("Mouse"),_T("ClickDulation"),_T("50"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	g_iClickDulation = _ttoi(szData);

	for(int iScene=0; iScene<MAX_THREAD; iScene++)
	{
		CString sSection;
		sSection.Format(_T("Operation %d"), iScene+1);
		GetPrivateProfileString(sSection,_T("FileName"),_T(""),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		g_Automation.m_OpeInfo[iScene].sFileName.Format(_T("%s"),szData);

		GetPrivateProfileString(sSection,_T("Hotkey"),_T(" "),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		g_Automation.m_OpeInfo[iScene].sHotkey.Format(_T("%s"), szData);

		GetPrivateProfileString(sSection,_T("UseCtrl"),_T("1"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		if(wcscmp(szData,_T("1"))==0){g_Automation.m_OpeInfo[iScene].bUseCtrl=TRUE;}
		else{g_Automation.m_OpeInfo[iScene].bUseCtrl=FALSE;}

		GetPrivateProfileString(sSection,_T("UseShift"),_T("1"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		if(wcscmp(szData,_T("1"))==0){g_Automation.m_OpeInfo[iScene].bUseShift=TRUE;}
		else{g_Automation.m_OpeInfo[iScene].bUseShift=FALSE;}

		GetPrivateProfileString(sSection,_T("UseAlt"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		if(wcscmp(szData,_T("1"))==0){g_Automation.m_OpeInfo[iScene].bUseAlt=TRUE;}
		else{g_Automation.m_OpeInfo[iScene].bUseAlt=FALSE;}

		GetPrivateProfileString(sSection,_T("UseWin"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
		if(wcscmp(szData,_T("1"))==0){g_Automation.m_OpeInfo[iScene].bUseWin=TRUE;}
		else{g_Automation.m_OpeInfo[iScene].bUseWin=FALSE;}
	}

	GetPrivateProfileString(_T("Hotkey"),_T("EnableKey"),_T(" "),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	g_Automation.m_sHotkeyEnable.Format(_T("%s"), szData);

	GetPrivateProfileString(_T("Hotkey"),_T("Enable"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	if(wcscmp(szData,_T("1"))==0){g_Automation.m_bEnableHotkey=TRUE;}
	else{g_Automation.m_bEnableHotkey=FALSE;}

	GetPrivateProfileString(_T("Common"),_T("AutoMnimize"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	if(wcscmp(szData,_T("1"))==0){g_Automation.m_bAutoMinimize=TRUE;}
	else{g_Automation.m_bAutoMinimize=FALSE;}

	GetPrivateProfileString(_T("Common"),_T("Log"),_T("0"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	if(wcscmp(szData,_T("1"))==0){g_Automation.m_bLog=TRUE;}
	else{g_Automation.m_bLog=FALSE;}

	GetPrivateProfileString(_T("Common"),_T("LogLevel"),_T("1"),szData,sizeof(szData)/sizeof(TCHAR),sFilePath);
	g_Automation.m_iLogLevel=_ttoi(szData);
	if(g_Automation.m_iLogLevel<1){g_Automation.m_iLogLevel=1;}
	if(g_Automation.m_iLogLevel>5){g_Automation.m_iLogLevel=5;}
	
	for(int iScene= 0; iScene<MAX_THREAD; iScene++)
	{
		g_hThread[iScene] = NULL;
		if(g_Automation.m_OpeInfo[iScene].sHotkey.GetLength()>=2)
		{
			if(g_Automation.m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F1"))==0){g_Automation.m_OpeInfo[iScene].dwHotKey = VK_F1;}
			if(g_Automation.m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F2"))==0){g_Automation.m_OpeInfo[iScene].dwHotKey = VK_F2;}
			if(g_Automation.m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F3"))==0){g_Automation.m_OpeInfo[iScene].dwHotKey = VK_F3;}
			if(g_Automation.m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F4"))==0){g_Automation.m_OpeInfo[iScene].dwHotKey = VK_F4;}
			if(g_Automation.m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F5"))==0){g_Automation.m_OpeInfo[iScene].dwHotKey = VK_F5;}
			if(g_Automation.m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F6"))==0){g_Automation.m_OpeInfo[iScene].dwHotKey = VK_F6;}
			if(g_Automation.m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F7"))==0){g_Automation.m_OpeInfo[iScene].dwHotKey = VK_F7;}
			if(g_Automation.m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F8"))==0){g_Automation.m_OpeInfo[iScene].dwHotKey = VK_F8;}
			if(g_Automation.m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F9"))==0){g_Automation.m_OpeInfo[iScene].dwHotKey = VK_F9;}
			if(g_Automation.m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F10"))==0){g_Automation.m_OpeInfo[iScene].dwHotKey = VK_F10;}
			if(g_Automation.m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F11"))==0){g_Automation.m_OpeInfo[iScene].dwHotKey = VK_F11;}
			if(g_Automation.m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("F12"))==0){g_Automation.m_OpeInfo[iScene].dwHotKey = VK_F12;}
			if(g_Automation.m_OpeInfo[iScene].sHotkey.CompareNoCase(_T("Insert"))==0){g_Automation.m_OpeInfo[iScene].dwHotKey = VK_INSERT;}

		}
		else
		{
			if((char(g_Automation.m_OpeInfo[iScene].sHotkey.GetAt(0))>='a') && (char(g_Automation.m_OpeInfo[iScene].sHotkey.GetAt(0))<='z')){g_Automation.m_OpeInfo[iScene].dwHotKey = char(g_Automation.m_OpeInfo[iScene].sHotkey.GetAt(0))-'a'+0x41;}
			if((char(g_Automation.m_OpeInfo[iScene].sHotkey.GetAt(0))>='0') && (char(g_Automation.m_OpeInfo[iScene].sHotkey.GetAt(0))<='9')){g_Automation.m_OpeInfo[iScene].dwHotKey = char(g_Automation.m_OpeInfo[iScene].sHotkey.GetAt(0))-'0'+0x30;}
		}

	}
	if(g_Automation.m_sHotkeyEnable.GetLength()==1)
	{
		if((char(g_Automation.m_sHotkeyEnable.GetAt(0))>='a') && (char(g_Automation.m_sHotkeyEnable.GetAt(0))<='z')){g_Automation.m_dwHotKeyEnable = char(g_Automation.m_sHotkeyEnable.GetAt(0))-'a'+0x41;}
		if((char(g_Automation.m_sHotkeyEnable.GetAt(0))>='0') && (char(g_Automation.m_sHotkeyEnable.GetAt(0))<='9')){g_Automation.m_dwHotKeyEnable = char(g_Automation.m_sHotkeyEnable.GetAt(0))-'0'+0x30;}
	}
	if(g_Automation.m_iLogLevel<1){g_Automation.m_iLogLevel=1;}
	if(g_Automation.m_iLogLevel>5){g_Automation.m_iLogLevel=5;}

}

void AutomationInfo::SaveSettings()
{
	
	CString sFilePath;
	sFilePath.Format(_T("%s\\SAutomation.ini"), g_Automation.m_sDir); 

	CString sUseCtrl;
	CString sUseShift;
	CString sUseAlt;
	CString sUseWin;

	for(int iScene = 0; iScene<MAX_THREAD; iScene++)
	{
		CString sSection;
		sSection.Format(_T("Operation %d"), iScene+1);

		WritePrivateProfileString(sSection,_T("FileName"),g_Automation.m_OpeInfo[iScene].sFileName,sFilePath);

		WritePrivateProfileString(sSection,_T("Hotkey"),g_Automation.m_OpeInfo[iScene].sHotkey, sFilePath);

		sUseCtrl.Format(_T("%d"), g_Automation.m_OpeInfo[iScene].bUseCtrl);
		sUseShift.Format(_T("%d"), g_Automation.m_OpeInfo[iScene].bUseShift);
		sUseAlt.Format(_T("%d"), g_Automation.m_OpeInfo[iScene].bUseAlt);
		sUseWin.Format(_T("%d"), g_Automation.m_OpeInfo[iScene].bUseWin);

		WritePrivateProfileString(sSection,_T("UseCtrl"),sUseCtrl,sFilePath);
		WritePrivateProfileString(sSection,_T("UseShift"),sUseShift,sFilePath);
		WritePrivateProfileString(sSection,_T("UseAlt"),sUseAlt,sFilePath);
		WritePrivateProfileString(sSection,_T("UseWin"),sUseWin,sFilePath);

	}


	WritePrivateProfileString(_T("Hotkey"),_T("EnableKey"),g_Automation.m_sHotkeyEnable,sFilePath);

	if(g_Automation.m_bEnableHotkey==TRUE)
	{
		WritePrivateProfileString(_T("Hotkey"),_T("Enable"),_T("1"),sFilePath);
	}
	else
	{
		WritePrivateProfileString(_T("Hotkey"),_T("Enable"),_T("0"),sFilePath);
	}


	if(g_Automation.m_bAutoMinimize==TRUE)
	{
		WritePrivateProfileString(_T("Common"),_T("AutoMnimize"),_T("1"),sFilePath);
	}
	else
	{
		WritePrivateProfileString(_T("Common"),_T("AutoMnimize"),_T("0"),sFilePath);
	}

	if(g_Automation.m_bLog==1)
	{
		WritePrivateProfileString(_T("Common"),_T("Log"),_T("1"),sFilePath);
	}
	else
	{
		WritePrivateProfileString(_T("Common"),_T("Log"),_T("0"),sFilePath);
	}

	CString sData;
	sData.Format(_T("%d"),g_Automation.m_iLogLevel);
	WritePrivateProfileString(_T("Common"),_T("LogLevel"),sData,sFilePath);
	
}