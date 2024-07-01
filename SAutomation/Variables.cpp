#include "stdafx.h"
#include "variables.h"
#include "perser.h"

int g_iVar[MAX_THREAD][MAX_VARIABLES];

int GetIntValue(int iScene, CString sArg)
{
	if(sArg.Left(6).CompareNoCase(_T("VarInt"))==0)
	{
		for(int iVarNameB1=1; iVarNameB1<=MAX_VARIABLES; iVarNameB1++)
		{
			CString sVarName;
			sVarName.Format(_T("VarInt%d"));
			if(sArg.CompareNoCase(sVarName)==0){return g_iVar[iScene][iVarNameB1-1];}
		}
	}
	
	return _ttoi(sArg);
}

int* GetIntValuePointer(int iScene, CString sArg)
{
	if(sArg.Left(6).CompareNoCase(_T("VarInt"))==0)
	{
		for(int iVarNameB1=1; iVarNameB1<=MAX_VARIABLES; iVarNameB1++)
		{
			CString sVarName;
			sVarName.Format(_T("VarInt%d"));
			if(sArg.CompareNoCase(sVarName)==0){return &(g_iVar[iScene][iVarNameB1-1]);}
		}
	}
	
	return NULL;
}