#include "stdafx.h"
#include "Thread.h"
#include "Common.h"
#include "Automation.h"
#include "resource.h"
#include "Variables.h"
#include "FlowManager.h"

#define TREAT_TO_EXIT_THREAD if(g_iLogLevel[iScene]>=1){g_utfW[iScene].CloseUTFFile();}g_bHalt = FALSE;\
	ChangeMouseOrigin(0, 0);\
	PostMessage(g_hWnd,WM_DISP_STANDBY,iScene,0);\
//	TerminateThread(hGetKey, 0);TerminateThread(hGetStepKey, 0);

HANDLE g_hThread[MAX_THREAD];

int g_iSceneData[MAX_THREAD];
long g_lLockCommandDisplay=0;

CString g_sCommand[MAX_THREAD];
CString g_sFilePath[MAX_THREAD];

BOOL g_bHalt;
BOOL g_bSuspend = FALSE;
LONGLONG g_llStepIn = 0;
LONGLONG g_llStepOut = 1;


DWORD WINAPI GetKeyThread(LPVOID arg)
{
	short shSpace;
	short shCtrl;
	short shShift;
	while(1)
	{
		shShift = GetKeyState(VK_SHIFT);
		shCtrl = GetKeyState(VK_CONTROL);
		shSpace = GetKeyState(VK_SPACE);

		if((shSpace<0)&&(shShift<0)&&(shCtrl<0)) 
		{
			g_bSuspend = TRUE;  
			Sleep(1);
			continue;
		}

		g_bSuspend = FALSE;
		Sleep(1);
	}

	return 0;
} 

DWORD WINAPI GetStepKeyThread(LPVOID arg)
{
	short shStep;
	short shCtrl;
	short shShift;
	while(1)
	{

		shShift = GetKeyState(VK_SHIFT);
		shCtrl = GetKeyState(VK_CONTROL);
		shStep = GetKeyState(0x53);
		if((shStep<0)&&(shShift<0)&&(shCtrl<0)) 
		{
			if(g_llStepOut==1){g_llStepIn=1;}
		}

		Sleep(1);
	}
	return 0;
} 


DWORD WINAPI CommandThread(LPVOID arg)
{
//	HANDLE hGetKey;
//	HANDLE hGetStepKey;
	DWORD dwThreadID;
	int* iSceneData;

	ChangeMouseOrigin(0, 0);

//	hGetKey = CreateThread(NULL, 0, GetKeyThread, NULL, 0, &dwThreadID);
//	hGetStepKey = CreateThread(NULL, 0, GetStepKeyThread, NULL, 0, &dwThreadID);
	CStringArray saCommands;
	CString sErrorGotoLable;

	int iData[3];
	iData[0] = ((int*)arg)[0];
	iData[1] = ((int*)arg)[1];
	iData[2] = ((int*)arg)[2];
	((int*)arg)[0] = 0;  
	((int*)arg)[1] = 0;  
	((int*)arg)[2] = 0;  
	BOOL bDisableHalt=(BOOL)iData[2];
	int iScene;
	iScene = ((iData[0]-1)>>PARAM_SCENE_SHIFT)&PARAM_SCENE_MASK;
	BOOL bRet;
	
	CString sDir;
	CString sFileName;
	bRet=GetDirectory(g_sFilePath[iScene], &sDir, &sFileName);

	bRet = ReadUTFFile(g_sFilePath[iScene], &saCommands);
	if(bRet != TRUE)
	{
		ChangeMouseOrigin(0, 0);
		PostMessage(g_hWnd,WM_DISP_STANDBY,iScene,0);
//		TerminateThread(hGetKey, 0);
//		TerminateThread(hGetStepKey, 0);
		return 0;
	}

	bRet = CStringArrayTrim(&saCommands);
	if(bRet != TRUE)
	{
		ChangeMouseOrigin(0, 0);
		PostMessage(g_hWnd,WM_DISP_STANDBY,iScene,0);
//		TerminateThread(hGetKey, 0);
//		TerminateThread(hGetStepKey, 0);
		return 0;
	}

	g_iSceneData[iScene]=iScene;
	iSceneData=&g_iSceneData[iScene];

	for(int i=0; i<MAX_VARIABLES; i++)
	{
		g_iVar[iScene][i]=0;
		g_sVar[iScene][i].Format(_T(""));
		g_point[iScene][i].Set(0, 0);
		g_imgRGB[iScene][i].Init();
	}

	g_iLogLevel[iScene] = (iData[1]>>PARAM_LOGLEVEL_SHIFT)&PARAM_LOGLEVEL_MASK;

	ErrTreatValue iErrorTreat;
	iErrorTreat = ERROR_TREAT_END;
	int iListLength;
	ReturnValue iRet;
	CString sLabel;
	BOOL bExit;
	StopWatch sw;
	g_sFilePath[iScene].Format(_T("%s\\Log\\log%d.txt"), g_sDir, iScene);
	if(g_iLogLevel[iScene]>=1)
	{
		BOOL bRet;
		bRet = g_utfW[iScene].OpenUTFFile(g_sFilePath[iScene],_T("w, ccs=UTF-8"));
	}
	ResetProgramCounter(sDir, iScene);
	CString sWrite;
	BOOL* bHalt;

	if(bDisableHalt==FALSE)
	{
		bHalt=&g_bHalt;
	}
	else
	{
		bHalt=NULL;
	}

	iListLength =(int) saCommands.GetCount();
	for(int i=0; i<iListLength; i++)
	{
		if(saCommands.GetAt(i).Left(1).Compare(_T("/"))==0){continue;}
		if(saCommands.GetAt(i).Left(1).Compare(_T("'"))==0){continue;}
		if(saCommands.GetAt(i).GetLength()<=0){continue;}

		sWrite.Format(_T("%d "), i+1);
		if(g_iLogLevel[iScene]>=1){g_utfW[iScene].WriteString(sWrite);}
		bExit = FALSE;
		if(bHalt!=NULL){if(*bHalt == TRUE){TREAT_TO_EXIT_THREAD; return 0;}}

		sWrite.Format(_T("%s "), saCommands.GetAt(i));
		if(g_iLogLevel[iScene]>=1){g_utfW[iScene].WriteString(sWrite);}
		CString sReturnParam;
		try
		{
			if(g_lLockCommandDisplay==0)
			{
				InterlockedExchange(&g_lLockCommandDisplay, 1);
				g_sCommand[iScene].Format(_T("%s"),  saCommands.GetAt(i));
				PostMessage(g_hWnd,WM_DISP_COMMAND,iScene,i);
				InterlockedExchange(&g_lLockCommandDisplay, 0);
			}
		}
		catch(CException* ce)
		{
			AfxMessageBox(saCommands.GetAt(i));
			wchar_t wcMessage[64];
			ce->GetErrorMessage(wcMessage,64);
			AfxMessageBox(wcMessage);
			TREAT_TO_EXIT_THREAD; 
			return 0;
		}
		try
		{
			iRet = OperateCommand(sDir, iSceneData, bHalt, &g_bSuspend, &g_llStepIn, saCommands.GetAt(i), &sReturnParam);
		}
		catch(CException* ce)
		{
			AfxMessageBox(saCommands.GetAt(i));
			wchar_t wcMessage[64];
			ce->GetErrorMessage(wcMessage,64);
			AfxMessageBox(wcMessage);
			TREAT_TO_EXIT_THREAD; 
			return 0;
		}
		sWrite.Format(_T("%d\n"), iRet);

		if(g_iLogLevel[iScene]>=1){g_utfW[iScene].WriteString(sWrite);}
		switch(iRet)
		{
		case RETURN_HALT:{TREAT_TO_EXIT_THREAD; return 0;}
		case RETURN_NORMAL: {break;}
		case RETURN_END:{bExit=TRUE; break;}
		case RETURN_LABEL:{break;}
		case RETURN_ERROR_TREAT:
			{
				int iErrTreatRet = GetErroTreat(saCommands.GetAt(i), &sLabel);
				switch(iErrTreatRet)
				{
				case ERROR_TREAT_END:{iErrorTreat=ERROR_TREAT_END; break;}
				case ERROR_TREAT_GOTO:{iErrorTreat=ERROR_TREAT_GOTO; break;}
				case ERROR_TREAT_RESUME:{iErrorTreat=ERROR_TREAT_RESUME; break;}
				default:{TREAT_TO_EXIT_THREAD; return 0;}
				}
				break;
			}
		case RETURN_FAILED:
			{
				sWrite.Format(_T("iErrorTreat = %d %s\n"), iErrorTreat, sLabel);
				if(g_iLogLevel[iScene]>=1){g_utfW[iScene].WriteString(sWrite);}
				switch(iErrorTreat)
				{
				case ERROR_TREAT_RESUME:{break;}
				case ERROR_TREAT_GOTO:
					{
						PerseLabelFromGotoStatement(saCommands.GetAt(i),&sLabel);
						int iLabel = SearchLable(&saCommands,sLabel, iScene);
						sWrite.Format(_T("iLabel = %d\n"), iLabel);
						if(g_iLogLevel[iScene]>=1){g_utfW[iScene].WriteString(sWrite);}
						if(iLabel < 0){TREAT_TO_EXIT_THREAD; return 0;}

						i=iLabel-1;
						break;
					}
				default:{TREAT_TO_EXIT_THREAD; return 0;}
				}
				break;
			}
		case RETURN_GOTO:
			{
				PerseLabelFromGotoStatement(saCommands.GetAt(i),&sLabel);
				int iLabel = SearchLable(&saCommands,sLabel, iScene);
				if(iLabel < 0){TREAT_TO_EXIT_THREAD; return 0;}

				i=iLabel-1;
				break;
			}
		case RETURN_GOTO_BY_SWITCH:
			{
				int iLabel = SearchLable(&saCommands,sReturnParam, iScene);
				if(iLabel < 0){TREAT_TO_EXIT_THREAD; return 0;}

				i=iLabel-1;
				break;
			}
		case RETURN_CALL_SUB:
			{
				if(g_iNowLevel[iScene]>=MAX_LEVEL){TREAT_TO_EXIT_THREAD; return 0;}

				int iLabel = SearchSubRoutine(&saCommands, sReturnParam, iScene);
				if(iLabel < 0){TREAT_TO_EXIT_THREAD; return 0;}

				g_iProgramCounter[iScene][g_iNowLevel[iScene]]=i;
				(g_iNowLevel[iScene])++;
				i=iLabel-1;
				break;
			}
		case RETURN_END_SUB:
			{
				g_iNowLevel[iScene]--;
				if(g_iNowLevel[iScene]<0){TREAT_TO_EXIT_THREAD; return 0;}

				i=g_iProgramCounter[iScene][g_iNowLevel[iScene]];
				break;
			}
		}
		g_llStepOut=1;
		g_llStepIn=0;
		if(bExit==TRUE){break;}
	}

	TREAT_TO_EXIT_THREAD;
	return 0;
}