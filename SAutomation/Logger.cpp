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

enum QueStatus
{
	QUE_LOCKED = -1,
	QUE_NO_QUE =0,
	QUE_POP_NORMAL = 1,
};

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


QueStatus PopAllMain(int iSet, Message* mes, int* iNum) 
{
	EnterCriticalSection(&(csQue[iSet]));
	int i=0;
	for(int i=0; i<g_iQuePos[iSet]; i++)
	{
		mes[i].Copy(&(g_MainQue[iSet*MAX_QUE + i]));
	}
	*iNum=g_iQuePos[iSet];
	g_iQuePos[iSet]=0;
	LeaveCriticalSection(&(csQue[iSet]));
	return QUE_POP_NORMAL;
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
	for(int i=0; i<MAX_QUE_SET; i++)
	{
		InitializeCriticalSection(&(csQue[i]));
	}

	BOOL bNeedToWrite[MAX_THREAD]={FALSE};
	Message mesToWrite[MAX_QUE_SET*MAX_QUE];
	UTFReaderWriter utfW[MAX_THREAD];

	DWORD timeLastWrote = GetTickCount();
	while (1) 
	{
		int iNum[MAX_QUE_SET];
		for(int iSet=0; iSet<MAX_QUE_SET; iSet++)
		{
			if(PopAllMain(iSet, &(mesToWrite[iSet*MAX_QUE_SET]), &(iNum[iSet])) != QUE_POP_NORMAL){break;}
		}

		for(int iScene=0; iScene<MAX_THREAD; iScene++)
		{
			bNeedToWrite[iScene]=FALSE;
		}

		for(int iSet=0; iSet<MAX_QUE_SET; iSet++)
		{
			for(int i=0; i<iNum[iSet]; i++)
			{
				bNeedToWrite[mesToWrite[iSet*MAX_QUE_SET + i].iScene]=TRUE;
			}

		}



		for(int iScene=0; iScene<MAX_THREAD; iScene++)
		{
			if(g_iLogLevel[iScene]<=0){continue;}
			if(bNeedToWrite[iScene] != TRUE){continue;}
			if(g_bClearFile[iScene]==TRUE)
			{
				utfW[iScene].OpenUTFFile(g_sLogFilePath[iScene],_T("w, ccs=UTF-8"));
				g_bClearFile[iScene]=FALSE;
			}
			else
			{
				utfW[iScene].OpenUTFFile(g_sLogFilePath[iScene],_T("a, ccs=UTF-8"));
			}
		}
		
		for(int iSet=0; iSet<MAX_QUE_SET; iSet++)
		{
			for(int i=0; i<iNum[iSet]; i++)
			{
			utfW[mesToWrite[iSet*MAX_QUE_SET + i].iScene].WriteString(mesToWrite[iSet*MAX_QUE_SET + i].sLogText);
		}
		}


		for(int iScene=0; iScene<MAX_THREAD; iScene++)
		{
			if(g_iLogLevel[iScene]<=0){continue;}
			if(bNeedToWrite[iScene] != TRUE){continue;}
			utfW[iScene].CloseUTFFile();
		}

		while(1)
		{
			if(g_bEndLogThread==TRUE){break;}
			DWORD now = GetTickCount();
			if (now - timeLastWrote >= 1000) 
			{
				timeLastWrote = now;
				break;
			}
			Sleep(10);
		}
	}
	for(int i=0; i<MAX_QUE_SET; i++)
	{
		DeleteCriticalSection(&(csQue[i]));
	}
	return 0;
}

