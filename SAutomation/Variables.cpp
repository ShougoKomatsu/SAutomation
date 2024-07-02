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
			sVarName.Format(_T("VarInt%d"), iVarNameB1);
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
			sVarName.Format(_T("VarInt%d"), iVarNameB1);
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

	return 0;
}

BOOL IsIntEqual(int iScene, CString sArg1, CString sArg2)
{
	int iInt1;
	int iInt2;
	iInt1 = GetIntValue(iScene, sArg1);
	iInt2 = GetIntValue(iScene, sArg2);
	
	return (iInt1==iInt2);
}

int Flow_IsIntEqual(int iScene, CStringArray* saData, CString* sReturnParam)
{
	if(IsIntEqual(iScene, saData->GetAt(0), saData->GetAt(1)))
	{
		sReturnParam->Format(_T("%s"), saData->GetAt(2));
		return RETURN_GOTO_BY_SWITCH;

	}

	return RETURN_NORMAL;
}

int Flow_AddInt(int iScene, CStringArray* saData)
{
	int iTemp=IntAdd(iScene, saData->GetAt(0), saData->GetAt(1));
	(*GetIntValuePointer(iScene, saData->GetAt(0)))=iTemp;
	return RETURN_NORMAL;
}
int Flow_SubInt(int iScene, CStringArray* saData)
{
	int iTemp=IntSub(iScene, saData->GetAt(0), saData->GetAt(1));
	(*GetIntValuePointer(iScene, saData->GetAt(0)))=iTemp;
	return RETURN_NORMAL;
}
int Flow_MultInt(int iScene, CStringArray* saData)
{
	int iTemp=IntMult(iScene, saData->GetAt(0), saData->GetAt(1));
	(*GetIntValuePointer(iScene, saData->GetAt(0)))=iTemp;
	return RETURN_NORMAL;
}
int Flow_DivInt(int iScene, CStringArray* saData)
{
	if(_ttoi(saData->GetAt(1))==0){return RETURN_FAILED;}
	int iTemp=IntDiv(iScene, saData->GetAt(0), saData->GetAt(1));
	(*GetIntValuePointer(iScene, saData->GetAt(0)))=iTemp;
	return RETURN_NORMAL;
}

int GetValue(int iScene, CString sArg)
{
	if(sArg.GetLength()<0){return 0;}
	if(sArg.Left(1).CompareNoCase(_T("v"))==0) {return GetIntValue(iScene, sArg);}
	return _ttoi(sArg);
}
