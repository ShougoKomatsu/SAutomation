#include "stdafx.h"
#include "Logger.h"
#include "Common.h"
BOOL g_bClearFile[MAX_THREAD];
struct Message 
{
	int iScene;
	CString sLogText;
	void Copy(const Message* mesIn)
	{
		this->iScene=mesIn->iScene;
		this->sLogText.Format(_T("%s"),(LPCTSTR)mesIn->sLogText);
	}
};

#define MAX_QUE_SET (10)
#define MAX_QUE (1024)

CRITICAL_SECTION csQue[MAX_QUE_SET];
Message g_MainQue[MAX_QUE_SET*MAX_QUE];
int g_iQuePos[MAX_QUE_SET] = {0};

BOOL g_bEndLogThread=FALSE;
int g_iWriteLogPeriodMilliSec=10000;
int g_iCheckLogPeriodMilliSec=1000;

BOOL PushQue(int iSet, const Message* mes) 
{
	if(TryEnterCriticalSection(&(csQue[iSet])) != TRUE)
	{
		if(iSet>=MAX_QUE_SET-1){return FALSE;}
		return PushQue(iSet+1, mes);
	}

	if (g_iQuePos[iSet] >= MAX_QUE) 
	{
		BOOL bRet = PushQue(iSet+1, mes);
		LeaveCriticalSection(&(csQue[iSet]));
		return bRet;
	}

	g_MainQue[iSet*MAX_QUE + g_iQuePos[iSet]].Copy(mes);
	g_iQuePos[iSet]++;
	LeaveCriticalSection(&(csQue[iSet]));
	return TRUE;
}


BOOL PopAllMain(int iSet, Message* mes, int* iNum) 
{
	EnterCriticalSection(&(csQue[iSet]));
	int iQuePos=0;
	for(int iQuePos=0; iQuePos<g_iQuePos[iSet]; iQuePos++)
	{
		mes[iQuePos].Copy(&(g_MainQue[iSet*MAX_QUE + iQuePos]));
	}
	*iNum=g_iQuePos[iSet];
	g_iQuePos[iSet]=0;
	LeaveCriticalSection(&(csQue[iSet]));
	return TRUE;
}


BOOL SetLogQue(int iScene, CString sData)
{
	if(g_iLogLevel[iScene]<=0){return FALSE;}
	BOOL bRet;
	Message mes;
	mes.iScene=iScene;
	mes.sLogText.Format(_T("%s"), sData);
	bRet = PushQue(0, &mes);
	return bRet;
}


DWORD WINAPI LoggerThread(LPVOID) 
{
	for(int iSet=0; iSet<MAX_QUE_SET; iSet++)
	{
		InitializeCriticalSection(&(csQue[iSet]));
	}

	CStringArray saToWrite[MAX_THREAD];
	Message mesToWrite[MAX_QUE_SET*MAX_QUE];
	UTFReaderWriter utfW[MAX_THREAD];

	for(int iScene=0; iScene<MAX_THREAD; iScene++)
	{
		saToWrite[iScene].RemoveAll();
	}

	DWORD timeLastWrote = GetTickCount();
	DWORD timeLastCheck = GetTickCount();
	while (1) 
	{
		int iNum[MAX_QUE_SET];
		for(int iSet=0; iSet<MAX_QUE_SET; iSet++)
		{
			if(PopAllMain(iSet, &(mesToWrite[iSet*MAX_QUE_SET]), &(iNum[iSet])) != TRUE){break;}
		}



		for(int iSet=0; iSet<MAX_QUE_SET; iSet++)
		{
			for(int iQuePos=0; iQuePos<iNum[iSet]; iQuePos++)
			{
				saToWrite[mesToWrite[iSet*MAX_QUE_SET + iQuePos].iScene].Add(mesToWrite[iSet*MAX_QUE_SET + iQuePos].sLogText);
			}
		}


		DWORD now = GetTickCount();
		if ((g_bEndLogThread==TRUE) || (now - timeLastWrote >= g_iWriteLogPeriodMilliSec))
		{
			for(int iScene=0; iScene<MAX_THREAD; iScene++)
			{
				if(g_iLogLevel[iScene]<=0){continue;}
				if(saToWrite[iScene].GetCount()<=0){continue;}

				if(g_bClearFile[iScene] == TRUE)
				{
					g_bClearFile[iScene]=FALSE;
					utfW[iScene].OpenUTFFile(g_sLogFilePath[iScene],_T("w, ccs=UTF-8"));
				}
				else
				{
					utfW[iScene].OpenUTFFile(g_sLogFilePath[iScene],_T("a, ccs=UTF-8"));
				}

				for(int iQuePos=0; iQuePos<saToWrite[iScene].GetCount(); iQuePos++)
				{
					utfW[iScene].WriteString(saToWrite[iScene].GetAt(iQuePos));
				}
				utfW[iScene].CloseUTFFile();
				saToWrite[iScene].RemoveAll();
			}

			if(g_bEndLogThread==TRUE)
			{
				break;
			}

			timeLastWrote = now;
		}

		while(1)
		{
			if(g_bEndLogThread==TRUE)
			{
				break;
			}

			DWORD now = GetTickCount();
			if (now - timeLastCheck >= g_iCheckLogPeriodMilliSec) 
			{
				timeLastCheck = now;
				break;
			}
			Sleep(10);
		}
	}

	for(int iSet=0; iSet<MAX_QUE_SET; iSet++)
	{
		DeleteCriticalSection(&(csQue[iSet]));
	}
	return 0;
}

