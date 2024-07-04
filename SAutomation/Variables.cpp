#include "stdafx.h"
#include "variables.h"
#include "perser.h"

int g_iVar[MAX_THREAD][MAX_VARIABLES];

BOOL GetCommandVariable(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));
	if(sDataTrim.Left(6).CompareNoCase(_T("VarInt"))==0){*iCommandType=]VARIABLE_INT; return TRUE;}

	if(sDataTrim.Left(6).CompareNoCase(_T("AddInt"))==0){*iCommandType=VARIABLE_ADD_INT; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("SubInt"))==0){*iCommandType=VARIABLE_SUB_INT; return TRUE;}
	if(sDataTrim.Left(7).CompareNoCase(_T("MultInt"))==0){*iCommandType=VARIABLE_MULT_INT; return TRUE;}
	if(sDataTrim.Left(6).CompareNoCase(_T("DivInt"))==0){*iCommandType=VARIABLE_DIV_INT; return TRUE;}

return FALSE;
}


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


int GetValueInt(int iScene, CString sArg)
{
	if(sArg.GetLength()<0){return 0;}
	if(sArg.Left(1).CompareNoCase(_T("v"))==0) {return GetIntValue(iScene, sArg);}
	return _ttoi(sArg);
}

void AssignInt(int iScene, CString sArg, int iInput)
{
	(*GetIntValuePointer(iScene, sArg))=iInput;
}


int Flow_Assign(int iScene, CStringArray* saData)
{
	int iCommandType;

	BOOL bRet;
	CString sArg;
	CString sDataLocal;
	sDataLocal.Format(_T("%s"), saData->GetAt(1));
	GetCommandVariable(sDataLocal, &iCommandType);
	switch(iCommandType)
	{
	case VARIABLE_ADD_INT:
		{
			CString sArg1;
			CString sArg2;
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg1.Format(_T("%s"), sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg2.Format(_T("%s"), sArg);}

			int iTemp=IntAdd(iScene, sArg1, sArg2);
			(*GetIntValuePointer(iScene, saData->GetAt(0)))=iTemp;
			return RETURN_NORMAL;
		}
	case VARIABLE_SUB_INT:
		{
			CString sArg1;
			CString sArg2;
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg1.Format(_T("%s"), sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg2.Format(_T("%s"), sArg);}

			int iTemp=IntSub(iScene, sArg1, sArg2);
			(*GetIntValuePointer(iScene, saData->GetAt(0)))=iTemp;
			return RETURN_NORMAL;
		}
	case VARIABLE_MULT_INT:
		{
			CString sArg1;
			CString sArg2;
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg1.Format(_T("%s"), sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg2.Format(_T("%s"), sArg);}

			int iTemp=IntMult(iScene, sArg1, sArg2);
			(*GetIntValuePointer(iScene, saData->GetAt(0)))=iTemp;
			return RETURN_NORMAL;
		}
	case VARIABLE_DIV_INT:
		{
			CString sArg1;
			CString sArg2;
			ExtractData(sDataLocal, _T("("), &sArg, &sDataLocal);
			ExtractData(sDataLocal, _T(","), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg1.Format(_T("%s"), sArg);}
			ExtractData(sDataLocal, _T(")"), &sArg, &sDataLocal);
			if(sArg.GetLength()>0){sArg2.Format(_T("%s"), sArg);}

			int iTemp=IntDiv(iScene, sArg1, sArg2);
			(*GetIntValuePointer(iScene, saData->GetAt(0)))=iTemp;
			return RETURN_NORMAL;
		}
	case VARIABLE_INT:
		{
			int iTemp=GetIntValue(iScene, sDataLocal);
			(*GetIntValuePointer(iScene, saData->GetAt(0)))=iTemp;
			return RETURN_NORMAL;
		}
	default:
		{
			if(sDataLocal.SpanIncluding(_T("0123456789")).CompareNoCase(sDataLocal)==0)
			{
				(*GetIntValuePointer(iScene, saData->GetAt(0)))=_ttoi(sDataLocal);
				return RETURN_NORMAL;
			}
			return RETURN_FAILED;
		}

	}
			return RETURN_FAILED;
}