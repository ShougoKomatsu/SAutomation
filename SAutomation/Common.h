#pragma once

#define SAFE_DELETE(v) if(v != NULL){delete [] v; v=NULL;}

enum ReturnValue
{
	RETURN_NORMAL=0,
	RETURN_FAILED=-1,
	RETURN_END=10,
	RETURN_HALT=-2,
	RETURN_ERROR_TREAT=11,
	RETURN_IF=100,
	RETURN_LABEL=101,
	RETURN_GOTO=102,
	RETURN_GOTO_BY_SWITCH=103,
	RETURN_CALL_SUB=104,
	RETURN_END_SUB=105,
	RETURN_SUB=106

};

struct StopWatch
{
	ULONGLONG ullStartMilliSec;
	ULONGLONG ullStopMilliSec;
	StopWatch(){Init();return;}
	~StopWatch(){Init();return;}
	void Start(){ullStartMilliSec = GetTickCount64();}
	void Stop(){ullStopMilliSec = GetTickCount64();}

	int GetTime(){return (int)(ullStopMilliSec-ullStartMilliSec);}
	const CString GetTimeStr(){CString sss; sss.Format(_T("%d"), GetTime()); return sss;}

	void Init(){ullStartMilliSec=0;ullStopMilliSec=0;}

};


enum ErrTreatValue
{
	ERROR_TREAT_UNDEFINED=(-1),
	ERROR_TREAT_END=(0),
	ERROR_TREAT_RESUME=(1),
	ERROR_TREAT_GOTO=(2)
};

struct OperationInfo
{	
	CString sHotkey;
	BOOL bUseCtrl;
	BOOL bUseShift;
	BOOL bUseAlt;
	BOOL bUseWin;
	DWORD dwHotKey;
	BOOL m_bRunning;
	CString sFileName;
	OperationInfo(){m_bRunning=FALSE;}
	void Copy(OperationInfo* opeInfoIn)
	{
		sHotkey.Format(_T("%s"),opeInfoIn->sHotkey);
		sFileName.Format(_T("%s"),opeInfoIn->sFileName);
		bUseCtrl = opeInfoIn->bUseCtrl;
		bUseShift = opeInfoIn->bUseShift;
		bUseAlt = opeInfoIn->bUseAlt;
		bUseWin = opeInfoIn->bUseWin;
		dwHotKey = opeInfoIn->dwHotKey;
		m_bRunning = opeInfoIn->m_bRunning;
	}

	BOOL IsSameAs(OperationInfo* opeInfoIn)
	{
		if(sHotkey.Compare(opeInfoIn->sHotkey) != 0){return FALSE;}
		if(sFileName.Compare(opeInfoIn->sFileName) != 0){return FALSE;}
		if(bUseCtrl != opeInfoIn->bUseCtrl){return FALSE;}
		if(bUseShift != opeInfoIn->bUseShift){return FALSE;}
		if(bUseAlt != opeInfoIn->bUseAlt){return FALSE;}
		if(bUseWin != opeInfoIn->bUseWin){return FALSE;}
		if(dwHotKey != opeInfoIn->dwHotKey){return FALSE;}
		if(m_bRunning != opeInfoIn->m_bRunning){return FALSE;}
		return TRUE;
	}
};

void SetComboItem(CComboBox* combo, CString sHotkey);

#include "thread.h"
#define MAX_SELECTION (8)
class AutomationInfo
{
public:
	void Operate(int iScene);
	AutomationInfo()
	{
		for(int iExSecene=0; iExSecene<MAX_EX_THREAD; iExSecene++)
		{
			for(int iSelection=0;iSelection<MAX_SELECTION; iSelection++)
			{
				m_sSelectKeys[iExSecene][iSelection].Format(_T(""));
				m_sSelectFiles[iExSecene][iSelection].Format(_T(""));
			}
		}
	}
	BOOL Copy(AutomationInfo* autoInfoIn);

	BOOL m_bEnableHotkey;
	BOOL m_bAutoMinimize;
	BOOL m_bMinimizeToTaskTray;
	CString m_sHotkeyEnable;
	CString m_sTargetWindowName;
	int m_iLogLevel;
	BOOL m_bLog;
	DWORD m_dwHotKeyEnable;
	void ReadSettings();
	void SaveSettings();
	CString m_sDir;
	CString m_sSelectKeys[MAX_EX_THREAD][MAX_SELECTION];
	CString m_sSelectFiles[MAX_EX_THREAD][MAX_SELECTION];
	OperationInfo m_OpeInfo[MAX_THREAD];
	BOOL IsSameAs(AutomationInfo* autoInfoIn);
};	




#include "stdafx.h"
#include "InputDialog.h"


#include "MouseAutomation.h"



extern HHOOK g_hhook;

extern int g_iR;
extern int g_iC;
extern int g_iOriginR;
extern int g_iOriginC;
extern HWND g_hWnd;
extern double g_dSpeedMult;

extern int g_iWatching;

extern CStdioFile* g_cf[MAX_THREAD];
extern CString g_sLogFilePath[MAX_THREAD];

extern int g_iClickDulation;
extern CString g_sDir;
#define LOG_OUTPUT_INT(iScene, sArg, iData) if(g_iLogLevel[iScene]>=5){if(g_cf[iScene]->m_hFile != INVALID_HANDLE_VALUE){ CString sWrite; sWrite.Format(_T("<%s = %d> "),sArg, iData); g_cf[iScene]->WriteString(sWrite);}}
#define LOG_OUTPUT_STR(iScene, sArg, sData) if(g_iLogLevel[iScene]>=5){if(g_cf[iScene]->m_hFile != INVALID_HANDLE_VALUE){ CString sWrite; sWrite.Format(_T("<%s = %s> "),sArg, sData); g_cf[iScene]->WriteString(sWrite);}}	
#define LOG_OUTPUT_POINT(iScene, sArg, pPoint) if(g_iLogLevel[iScene]>=5){if(g_cf[iScene]->m_hFile != INVALID_HANDLE_VALUE){ CString sWrite; sWrite.Format(_T("<%s = (%d, %d)> "),sArg.Left(8), (pPoint==NULL ? 0 : pPoint->r), (pPoint == NULL ? 0 : pPoint->c)); g_cf[iScene]->WriteString(sWrite);}}



LRESULT CALLBACK MouseHookProc(int code, WPARAM wParam, LPARAM lParam);
BOOL GetFileName(CString sFilePath, CString* sFileName);


BOOL ReadUTFFile(CString sFilePath, CString* sData);
BOOL ReadTextFile(CString sFilePath, CStringArray* saCommands);

extern AutomationInfo g_Automation;
extern CInputDialog g_cInput;


void SetComboItemCtrl(CComboBox* combo, OperationInfo* op);

void SetComboItemShift(CComboBox* combo,OperationInfo* op);

void SetComboItem(CComboBox* combo, CString m_sHotkey);

BOOL GetFileProperty(const CString sFilePath, CTime* ctCreationTime, CTime* ctLastAccessTime, CTime* ctLastWriteTime);
const CString ConvertTimeToString(const SYSTEMTIME st, const CString sArg);


DWORD GetVKeyCode(const CString sIn);