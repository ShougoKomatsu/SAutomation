#include "stdafx.h"
#include <TlHelp32.h>

#include "Window.h"
#include "Common.h"
#include "Variables.h"
HWND g_hWnds[MAX_WINDOW_HANDLE];
int g_iWnd=0;

BOOL isProcessExist(CString sExePath)
{
	CString sExeName;
	BOOL bRet;
	bRet = GetFileName(sExePath,&sExeName);
	if(bRet != TRUE){return FALSE;}


	PROCESSENTRY32 entry;
	entry.dwSize=sizeof(PROCESSENTRY32);

	HANDLE snapshot = NULL;
	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	if(snapshot == NULL){return FALSE;}

	bRet = Process32First(snapshot,&entry);
	if(bRet !=TRUE){CloseHandle(snapshot);return FALSE;}

	while(Process32Next(snapshot, &entry)==TRUE)
	{
		if(sExeName.Compare( entry.szExeFile)==0)
		{
			CloseHandle(snapshot);
			return TRUE;
		}
	}
	CloseHandle(snapshot);
	return FALSE;
}

ReturnValue RunExe(CString sExePath)
{
	BOOL bAlreadyExist = FALSE;
	bAlreadyExist = isProcessExist(sExePath);
	if(bAlreadyExist==TRUE){return RETURN_NORMAL;}

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	memset(&si, NULL, sizeof(si));
	si.cb=sizeof(si);
	memset(&pi, NULL, sizeof(pi));

	wchar_t* szTmp;
	szTmp = new wchar_t[wcslen(sExePath) + 1];
	memset(szTmp, NULL, sizeof(szTmp)/sizeof(wchar_t));
	wcscpy_s(szTmp, wcslen(sExePath) + 1, sExePath);

	CreateProcess(NULL,  szTmp, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	delete [] szTmp;
	return RETURN_NORMAL;
}

ReturnValue Maximize()
{
	HWND hwnd = GetForegroundWindow();
	ShowWindow( hwnd, SW_MAXIMIZE );
	return RETURN_NORMAL;
}

ReturnValue Minimize()
{
	HWND hwnd = GetForegroundWindow();
	ShowWindow( hwnd, SW_MINIMIZE );
	return RETURN_NORMAL;
}
BOOL CALLBACK EnumWindowsFunc(HWND hWnd, LPARAM lParam)
{
	g_hWnds[g_iWnd]=hWnd;
	g_iWnd++;
	if(g_iWnd>=MAX_WINDOW_HANDLE){return FALSE;}

	return TRUE;
}


BOOL GetHandleByName(CString sTargetName, HWND* hwnd, BOOL bPartialMatch)
{
	WCHAR wszWindowName[MAX_PATH];
	CString sWindowName;

	g_iWnd=0;
	EnumWindows(EnumWindowsFunc, 0) ;

	int iTargetHandle;
	BOOL bFound;
	bFound = FALSE;
	iTargetHandle=0;
	for(int i=0; i<g_iWnd; i++)
	{
		GetWindowText(g_hWnds[i],wszWindowName,MAX_PATH);
		sWindowName.Format(_T("%s"), wszWindowName);
		if(bPartialMatch==TRUE)
		{
			if(sWindowName.Find(sTargetName)>=0){*hwnd = (g_hWnds[i]); return TRUE;}
		}
		else
		{
			if(sWindowName.Compare(sTargetName)==0){*hwnd = (g_hWnds[i]); return TRUE;}
		}
	}
	return FALSE;
}

BOOL GetWindowRectByName(CString sTargetName, RECT* rect, BOOL bPartialMatch)
{
	BOOL bRet;
	HWND hwnd;
	bRet = GetHandleByName(sTargetName, &hwnd, bPartialMatch);
	if(bRet != TRUE){return FALSE;}

	WINDOWINFO wi;
	GetWindowInfo(hwnd,&wi);
	*rect=wi.rcWindow;
	return TRUE;
}


ReturnValue SetWindowForward(CString sTargetName)
{
	BOOL bRet;
	HWND hwnd;
	bRet = GetHandleByName(sTargetName, &hwnd);
	if(bRet != TRUE){return RETURN_FAILED;}

//	bRet = ShowWindow(g_hWnds[iTargetHandle], SW_SHOW);
//	if(bRet != TRUE){return -1;}
	bRet = SetForegroundWindow(hwnd);
//	if(bRet != TRUE){return -1;}

	return RETURN_NORMAL;
}


BOOL GetWindowNameList(CStringArray* csNames)
{
	csNames->RemoveAll();

	WCHAR wszWindowName[MAX_PATH];
	CString sWindowName;

	g_iWnd=0;
	EnumWindows(EnumWindowsFunc, 0) ;

	int iTargetHandle;
	BOOL bFound;
	bFound = FALSE;
	iTargetHandle=0;
	for(int i=0; i<g_iWnd; i++)
	{
		GetWindowText(g_hWnds[i],wszWindowName,MAX_PATH);
		CRect	rect ;
		GetWindowRect(g_hWnds[i],&rect) ;
		if(rect.Width()<=1){continue;}

		sWindowName.Format(_T("%s"), wszWindowName);


		if(wcslen(wszWindowName)>0)
		{
			csNames->Add(wszWindowName);
		}
	}
	return TRUE;
}

ReturnValue WindowSize(int iScene, CStringArray* saData)
{
	HWND hwnd = GetForegroundWindow();
	CRect	rect ;
	GetWindowRect(hwnd,&rect) ;
	int iLeft;
	int iTop;
	int iWidth;
	int iHeight;

	if(saData->GetCount()!=2){return RETURN_FAILED;}

	iWidth = GetIntValue(iScene, saData->GetAt(0));
	iHeight = GetIntValue(iScene, saData->GetAt(1));

	iLeft = rect.left;
	iTop = rect.top;
	SetWindowPos(hwnd, HWND_TOP,iLeft, iTop, iWidth, iHeight,SWP_NOMOVE) ;
	return RETURN_NORMAL;
}
ReturnValue WindowPos(int iScene, CStringArray* saData)
{
	HWND hwnd = GetForegroundWindow();
	CRect	rect ;
	GetWindowRect(hwnd,&rect) ;
	int iLeft;
	int iTop;
	int iWidth;
	int iHeight;

	if(saData->GetCount()!=2){return RETURN_FAILED;}
	
	iWidth = rect.Width();
	iHeight = rect.Height();


	iLeft = GetIntValue(iScene, saData->GetAt(0));
	iTop = GetIntValue(iScene, saData->GetAt(1));

	SetWindowPos(hwnd, HWND_TOP,iLeft, iTop, iWidth, iHeight,SWP_NOSIZE) ;
	return RETURN_NORMAL;
}

BOOL GetForegroundWindowPos(int* iLeft, int* iTop, int* iWidth, int* iHeight)
{
	HWND hwnd = GetForegroundWindow();
	if(hwnd==NULL){return FALSE;}
	
	CRect rect;
	GetWindowRect(hwnd, &rect);
	*iLeft=rect.left;
	*iTop=rect.top;
	*iWidth=rect.Width();
	*iHeight=rect.Height();
	return TRUE;
}
const CString GetForegroundWindowName()
{
	HWND hwnd = GetForegroundWindow();
	if(hwnd==NULL){return _T("");}

	WCHAR wszWindowName[MAX_PATH];
	GetWindowText(hwnd,wszWindowName,MAX_PATH);
	
	CString sWindowName;
	sWindowName.Format(_T("%s"), wszWindowName);
	return sWindowName;
}

const CString GetForegroundWindowClassName()
{
	HWND hwnd = GetForegroundWindow();
	if(hwnd==NULL){return _T("");}

	WCHAR wszWindowName[MAX_PATH];
	GetClassName(hwnd,wszWindowName,MAX_PATH);
	
	CString sWindowName;
	sWindowName.Format(_T("%s"), wszWindowName);
	return sWindowName;
}

UINT GetDlgItem_My(CString sText, int iRank)
{
	HWND hwnd = GetForegroundWindow();
	if(hwnd==NULL){return 0;}
	
	TCHAR tch[MAX_PATH];
	int iRankLocal=0;
	int iRankNow=0;

	if(iRank<=0){iRankLocal=0;}
	else{iRankLocal=iRank;}

	for(UINT i=0; i<65535; i++)
	{
		UINT uiRet = GetDlgItemText(hwnd,i,tch,MAX_PATH);
		if(uiRet<=0){continue;}
		if(_tcslen(tch)<=0){continue;}
		CString sTemp;
		sTemp.Format(_T("%s"), tch);

		if(sTemp.Compare(sText)==0)
		{
			if(iRankNow==iRankLocal){return i;}
			iRankNow++;
		}
	}
	return 0;
}

BOOL GetWindowRect_My(UINT iID, CRect* rect)
{
	HWND hwnd = GetForegroundWindow();
	if(hwnd == NULL){return FALSE;}
	HWND hwnd_item;
	hwnd_item=GetDlgItem(hwnd, iID);
	if(hwnd_item == NULL){return FALSE;}
	
	return GetWindowRect(hwnd_item, rect);;
}
ReturnValue ListDlgItems()
{
	CString sMes;
	BOOL bRet;
	int iCommandType;
	HWND hwnd;
	TCHAR tch[MAX_PATH];
	hwnd=GetForegroundWindow();
	for(int i=0; i<65535; i++)
	{
		UINT uiRet = GetDlgItemText(hwnd,i,tch,MAX_PATH);
		if(uiRet<=0){continue;}
		if(_tcslen(tch)<=0){continue;}

		CString sMes;
		sMes.Format(_T("%d\n%s"), i, tch);
		AfxMessageBox(sMes);
	}

	return RETURN_NORMAL;
}