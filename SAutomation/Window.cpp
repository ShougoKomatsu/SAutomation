#include "stdafx.h"
#include <TlHelp32.h>

#include "Window.h"
#include "Common.h"
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

int RunExe(CString sExePath)
{
	BOOL bAlreadyExist = FALSE;
	bAlreadyExist = isProcessExist(sExePath);
	if(bAlreadyExist==TRUE){return 0;}

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
	return 0;
}

int Maximize()
{
	HWND hwnd = GetForegroundWindow();
	ShowWindow( hwnd, SW_MAXIMIZE );
	return 0;
}

int Minimize()
{
	HWND hwnd = GetForegroundWindow();
	ShowWindow( hwnd, SW_MINIMIZE );
	return 0;
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

int SetWindowForward(CString sTargetName)
{
	BOOL bRet;
	HWND hwnd;
	bRet = GetHandleByName(sTargetName, &hwnd);
	if(bRet != TRUE){return -1;}

//	bRet = ShowWindow(g_hWnds[iTargetHandle], SW_SHOW);
//	if(bRet != TRUE){return -1;}
	bRet = SetForegroundWindow(hwnd);
//	if(bRet != TRUE){return -1;}

	return 0;
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
//	WINDOWINFO wi;
//	GetWindowInfo(g_hWnds[i],&wi);
	
	sWindowName.Format(_T("%s"), wszWindowName);
	

		if(wcslen(wszWindowName)>0)
			{
				csNames->Add(wszWindowName);
		}
	}
	return TRUE;
}

int WindowSize(CStringArray* saData)
{
	HWND hwnd = GetForegroundWindow();
	CRect	rect ;
	GetWindowRect(hwnd,&rect) ;
	int iLeft;
	int iTop;
	int iWidth;
	int iHeight;

	if(saData->GetCount()!=2){return -1;}

	iWidth = _ttoi(saData->GetAt(0));
	iHeight = _ttoi(saData->GetAt(1));
	iLeft = rect.left;
	iTop = rect.top;
	SetWindowPos(hwnd, HWND_TOP,iLeft, iTop, iWidth, iHeight,SWP_NOMOVE) ;
	return 0;
}
int WindowPos(CStringArray* saData)
{
	HWND hwnd = GetForegroundWindow();
	CRect	rect ;
	GetWindowRect(hwnd,&rect) ;
	int iLeft;
	int iTop;
	int iWidth;
	int iHeight;

	if(saData->GetCount()!=2){return -1;}
	
	iWidth = rect.Width();
	iHeight = rect.Height();
	iLeft = _ttoi(saData->GetAt(0));
	iTop = _ttoi(saData->GetAt(1));

	SetWindowPos(hwnd, HWND_TOP,iLeft, iTop, iWidth, iHeight,SWP_NOSIZE) ;
	return 0;
}
