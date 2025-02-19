#include "stdafx.h"

#pragma once
extern CString g_sDir;
#define LOG_OUTPUT_INT(iScene, sArg, iData) if(g_iLogLevel[iScene]>=5){if(g_cf[iScene].m_hFile != INVALID_HANDLE_VALUE){ CString sWrite; sWrite.Format(_T("<%s = %d> "),sArg, iData); g_cf[iScene].WriteString(sWrite);}}
#define LOG_OUTPUT_STR(iScene, sArg, sData) if(g_iLogLevel[iScene]>=5){if(g_cf[iScene].m_hFile != INVALID_HANDLE_VALUE){ CString sWrite; sWrite.Format(_T("<%s = %s> "),sArg, sData); g_cf[iScene].WriteString(sWrite);}}	
#define LOG_OUTPUT_POINT(iScene, sArg, pPoint) if(g_iLogLevel[iScene]>=5){if(g_cf[iScene].m_hFile != INVALID_HANDLE_VALUE){ CString sWrite; sWrite.Format(_T("<%s = (%d, %d)> "),sArg.Left(8), (pPoint==NULL ? 0 : pPoint->r), (pPoint == NULL ? 0 : pPoint->c)); g_cf[iScene].WriteString(sWrite);}}


BOOL GetFileName(CString sFilePath, CString* sFileName);


BOOL ReadUTFFile(CString sFilePath, CString* sData);
BOOL ReadTextFile(CString sFilePath, CStringArray* saCommands);

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

enum ErrTreatValue
{
	ERROR_TREAT_UNDEFINED=(-1),
	ERROR_TREAT_END=(0),
	ERROR_TREAT_RESUME=(1),
	ERROR_TREAT_GOTO=(2)
};

void SetComboItem(CComboBox* combo, CString sHotkey);