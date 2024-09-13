#include "stdafx.h"
#include "FlowManager.h"

int g_iNowLevel[MAX_THREAD];
int g_iProgramCounter[MAX_THREAD][MAX_LEVEL];


void ResetProgramCounter(int iScene)
{
	g_iNowLevel[iScene]=0;
	for(int i=0; i<MAX_LEVEL; i++)
	{
		g_iProgramCounter[iScene][i]=0;
	}
}


int SearchLable(CStringArray* saData, CString sLabel, int iScene)
{
	for(int i=0; i<saData->GetCount(); i++)
	{
		CString sTemp;
		sTemp.Format(_T("%s"), saData->GetAt(i));
		sTemp.Trim(_T(" \t"));
		CString sTrim;
		sTrim.Format(_T("%s"), sTemp.Left(sTemp.GetLength()-1));
		sTrim.Trim(_T(" \t"));

		if(g_iLogLevel[iScene]>=5)
		{
			CString sWrite;
			sWrite.Format(_T("\"%s\", \"%s\"\n"), sTrim, sLabel);
			if(g_cf[iScene].m_hFile != INVALID_HANDLE_VALUE){ g_cf[iScene].WriteString(sWrite);}
		}
		if(sTrim.CompareNoCase(sLabel)==0){return i;}
	}
	return -1;
}


int SearchSubRoutine(CStringArray* saData, CString sLabel, int iScene)
{
	for(int i=0; i<saData->GetCount(); i++)
	{
		CString sTemp;
		sTemp.Format(_T("%s"), saData->GetAt(i));
		sTemp.Trim(_T(" \t"));
		if(sTemp.Left(3).CompareNoCase(_T("sub"))!=0){continue;}

		CString sTrim;
		sTrim.Format(_T("%s"), sTemp.Right(sTemp.GetLength()-4));
		sTrim.Trim(_T(" \t"));

		sTrim.Trim(_T(" \t"));

		if(g_iLogLevel[iScene]>=5)
		{
			CString sWrite;
			sWrite.Format(_T("\"%s\", \"%s\"\n"), sTrim, sLabel);
			if(g_cf[iScene].m_hFile != INVALID_HANDLE_VALUE){ g_cf[iScene].WriteString(sWrite);}
		}
		if(sTrim.CompareNoCase(sLabel)==0){return i;}
	}
	return -1;
}