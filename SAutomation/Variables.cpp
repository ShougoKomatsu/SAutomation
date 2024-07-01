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

int IntAdd(int iScene, CString sArg1, CString sArg2)
{
	int iInt1;
	int iInt2;
	iInt1 = GetIntValue(iScene, sArg1);
	iInt2 = GetIntValue(iScene, sArg2);
	
	return iInt1+iInt2;
}

int IntSub(int iScene, CString sArg1, CString sArg2)
{
	int iInt1;
	int iInt2;
	iInt1 = GetIntValue(iScene, sArg1);
	iInt2 = GetIntValue(iScene, sArg2);
	
	return iInt1-iInt2;
}
int IntMult(int iScene, CString sArg1, CString sArg2)
{
	int iInt1;
	int iInt2;
	iInt1 = GetIntValue(iScene, sArg1);
	iInt2 = GetIntValue(iScene, sArg2);
	
	return iInt1*iInt2;
}

int IntDiv(int iScene, CString sArg1, CString sArg2)
{
	int iInt1;
	int iInt2;
	iInt1 = GetIntValue(iScene, sArg1);
	iInt2 = GetIntValue(iScene, sArg2);
	
	return iInt1/iInt2;
}

int IntAssign(int iScene, CString sArg, int iValue)
{
	(*GetIntValuePointer(iScene, sArg))=iValue;
}

BOOL IsIntEqual(int iScene, CString sArg1, CString sArg2)
{
	int iInt1;
	int iInt2;
	iInt1 = GetIntValue(iScene, sArg1);
	iInt2 = GetIntValue(iScene, sArg2);
	
	return (iInt1==iInt2);
}

