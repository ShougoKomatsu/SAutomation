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

ReturnValue KillExe(CString sDir, int iScene, CStringArray* saData)
{
	int iHandle=GetIntValue(sDir, iScene, saData->GetAt(0));
	DWORD dwProcessID;
	GetProcessIDByWindowHandle((HWND)iHandle, &dwProcessID);

	HANDLE hProcess= OpenProcess(PROCESS_TERMINATE,FALSE, dwProcessID);

	TerminateProcess(hProcess, 0);
	CloseHandle(hProcess);


	return RETURN_FAILED;
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
	SAFE_DELETE(szTmp);
	return RETURN_NORMAL;
}

ReturnValue RunExe2(CString sExePath, HWND* hWnd)
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
	SHELLEXECUTEINFO sei={0};
	sei.cbSize=sizeof(SHELLEXECUTEINFO);
	sei.fMask=SEE_MASK_NOCLOSEPROCESS;
	sei.hwnd=NULL;
	sei.lpVerb=NULL;
	sei.lpFile=szTmp;
	sei.lpParameters=NULL;
	sei.lpDirectory=NULL;
	sei.nShow=SW_NORMAL;
	sei.hInstApp=NULL;
	ShellExecuteEx(&sei);
	SAFE_DELETE(szTmp);

	DWORD dwProcessID=GetProcessId(sei.hProcess);
	
	GetWindowHandleByProcessID(dwProcessID,hWnd);
	CloseHandle(sei.hProcess);

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

#include <dwmapi.h>

#pragma comment(lib, "dwmapi.lib")
ReturnValue SetWindowAttribute(CString sDir, int iScene, CStringArray* saData)
{


	HWND hwnd=(HWND)GetIntValue(sDir, iScene, saData->GetAt(0));
	if(hwnd==0){hwnd = GetForegroundWindow();}
	
	int iAttribute = GetIntValue(sDir, iScene, saData->GetAt(1));
	DWORD dwParameter = GetIntValue(sDir, iScene, saData->GetAt(2));

	HRESULT hr = DwmSetWindowAttribute(hwnd, iAttribute, &dwParameter, sizeof(dwParameter));
	if (SUCCEEDED(hr) != TRUE) {return RETURN_FAILED;}
	return RETURN_NORMAL;
}
BOOL CALLBACK EnumWindowsFunc(HWND hWnd, LPARAM lParam)
{
	g_hWnds[g_iWnd]=hWnd;
	g_iWnd++;
	if(g_iWnd>=MAX_WINDOW_HANDLE){return FALSE;}

	return TRUE;
}


BOOL GetWindowHandleByName(CString sTargetName, HWND* hwnd, BOOL bPartialMatch)
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

BOOL GetProcessIDByWindowHandle(HWND hwnd,DWORD* dwProcessID)
{
	WCHAR wszWindowName[MAX_PATH];
	CString sWindowName;

	g_iWnd=0;
	EnumWindows(EnumWindowsFunc, 0) ;

	for(int i=0; i<g_iWnd; i++)
	{
		if(g_hWnds[i] == hwnd)
		{
			GetWindowThreadProcessId(g_hWnds[i],dwProcessID);

			return TRUE;
		}
	}
	return FALSE;
}

BOOL GetWindowHandleByProcessID(DWORD dwTargetID, HWND* hwnd)
{
	*hwnd=NULL;
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
		DWORD dwProcessID;
		GetWindowThreadProcessId(g_hWnds[i],&dwProcessID);
		if(dwProcessID==dwTargetID)
		{
			*hwnd=g_hWnds[i];
			return TRUE;
		}
	}
	return FALSE;
}

BOOL GetWindowRectByName(CString sTargetName, RECT* rect, BOOL bPartialMatch)
{
	BOOL bRet;
	HWND hwnd;
	bRet = GetWindowHandleByName(sTargetName, &hwnd, bPartialMatch);
	if(bRet != TRUE){return FALSE;}

	WINDOWINFO wi;
	GetWindowInfo(hwnd,&wi);
	*rect=wi.rcWindow;
	return TRUE;
}

ReturnValue SendMessage_My(CString sDir, int iScene, CStringArray* saData)
{
	HWND hwnd;
	UINT msg;
	WPARAM wParam;
	LPARAM lParam;

	hwnd=(HWND)GetIntValue(sDir, iScene, saData->GetAt(0));
	if(hwnd==0){hwnd = GetForegroundWindow();}

	msg=(UINT)GetIntValue(sDir, iScene, saData->GetAt(1));
	SendMessage(hwnd, msg, NULL, NULL);
	
	return RETURN_NORMAL;
}
ReturnValue SetWindowForward(CString sDir, int iScene, CStringArray* saData)
{
	BOOL bRet;
	HWND hwnd;

	CString sTargetName;

	int iType = GetOperandType(saData->GetAt(0));

	switch(iType)
	{
	case VARIABLE_INT:
		{
			hwnd = (HWND)GetIntValue(sDir, iScene, saData->GetAt(0));
			break;
		}
	case VARIABLE_STR:
		{
			sTargetName.Format(_T("%s"), GetStrValue(sDir, iScene, saData->GetAt(0)));
			bRet = GetWindowHandleByName(sTargetName, &hwnd);
			if(bRet != TRUE){return RETURN_FAILED;}
			break;
		}
	default:
		{
			return RETURN_FAILED;
		}
	}

	bRet = ShowWindow(hwnd, SW_SHOW);
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

ReturnValue WindowSize(CString sDir, int iScene, CStringArray* saData)
{
	HWND hwnd = GetForegroundWindow();
	CRect	rect ;
	GetWindowRect(hwnd,&rect) ;
	int iLeft;
	int iTop;
	int iWidth;
	int iHeight;

	if(saData->GetCount()!=2){return RETURN_FAILED;}

	iWidth = GetIntValue(sDir, iScene, saData->GetAt(0));
	iHeight = GetIntValue(sDir, iScene, saData->GetAt(1));

	iLeft = rect.left;
	iTop = rect.top;
	SetWindowPos(hwnd, HWND_TOP,iLeft, iTop, iWidth, iHeight,SWP_NOMOVE) ;
	return RETURN_NORMAL;
}
ReturnValue WindowPos(CString sDir, int iScene, CStringArray* saData)
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


	iLeft = GetIntValue(sDir, iScene, saData->GetAt(0));
	iTop = GetIntValue(sDir, iScene, saData->GetAt(1));

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

BOOL GetWindowRect_My(UINT iID, CRect* rect)
{
	
	HWND hwnd = GetForegroundWindow();
	if(hwnd == NULL){return FALSE;}
	HWND hwnd_item;
	hwnd_item=GetDlgItem(hwnd, iID);
	if(hwnd_item == NULL){return FALSE;}
	

	return GetWindowRect(hwnd_item, rect);;
}


BOOL CALLBACK EnumChildProc(HWND hwnd, LPARAM lParam);

#define MAX_CTRL_NUM (1024)
HWND g_hCtrlHandles[MAX_CTRL_NUM];

BOOL CALLBACK EnumChildProc( HWND hWnd, LPARAM lParam )
{
	wchar_t   tch[ 1024 ];
	int  iCount = *(int*)lParam;

	if(iCount>=MAX_CTRL_NUM){return FALSE;}

	GetWindowText( hWnd, tch, sizeof(tch) ); 
	if(_tcslen(tch)<=0){return TRUE;}

	g_hCtrlHandles[iCount]=hWnd;
	*(int*)lParam = iCount+1;
	return TRUE;
}


ReturnValue ListDlgItems()
{
	CString sMes;
	HWND hwnd;
	wchar_t tch[MAX_PATH];
	hwnd=GetForegroundWindow();
	int iListLength;
	iListLength=0;
	sMes.Format(_T(""));

	int iCount = 0;
	BOOL bRet = EnumChildWindows( hwnd, EnumChildProc, (LPARAM)&iCount );
	if(bRet != TRUE){return RETURN_FAILED;}

	for(int i=0; i<iCount; i++)
	{
		UINT uiRet = GetWindowText(g_hCtrlHandles[i], tch, MAX_PATH);
		int iID = GetDlgCtrlID(g_hCtrlHandles[i]);
		if(uiRet<=0){continue;}
		if(_tcslen(tch)<=0){continue;}

		if(sMes.GetLength()>0)
		{
			sMes.Format(_T("%s\n%d: %s"),sMes, iID, tch);
		}
		else
		{
			sMes.Format(_T("%d: %s"), iID, tch);
		}
		iListLength++;
		if(iListLength>=10)
		{
			AfxMessageBox(sMes);
			iListLength=0;
			sMes.Format(_T(""));
		}
	}
	if(iListLength>0)
	{
		AfxMessageBox(sMes);
	}

	return RETURN_NORMAL;
}
int GetDlgItem_My(CString sText, int iRank)
{
	HWND hwnd = GetForegroundWindow();
	if(hwnd==NULL){return 0;}
	
	wchar_t tch[MAX_PATH];
	int iRankLocal=0;
	int iRankNow=0;

	if(iRank<=0){iRankLocal=0;}
	else{iRankLocal=iRank;}
	
	int iCount = 0;
	EnumChildWindows( hwnd, EnumChildProc, (LPARAM)&iCount );

	for(int i=0; i<iCount; i++)
	{
		UINT uiRet = GetWindowText(g_hCtrlHandles[i], tch, MAX_PATH);
		if(uiRet<=0){continue;}
		if(_tcslen(tch)<=0){continue;}
		CString sTemp;
		sTemp.Format(_T("%s"), tch);

		if(sTemp.Compare(sText)==0)
		{
			if(iRankNow==iRankLocal){return GetDlgCtrlID(g_hCtrlHandles[i]);}
			iRankNow++;
		}
	}
	return 0;
}
