#include "stdafx.h"
#include "variables.h"



BOOL GetOperandBytesSrc(CString sDataLine, int* iCommandType)
{
	CString sDataTrim;
	sDataTrim.Format(_T("%s"),sDataLine.Trim(_T(" \t")));
	
	if(sDataTrim.SpanIncluding(_T("0123456789ABCDEF")).CompareNoCase(sDataTrim)==0){*iCommandType = VARIABLE_BYTES; return TRUE;}
	
	return FALSE;
}

ByteVector* GetSetBytesValuePointer(CString sDir, int iScene, CString sArg)
{
	
	if(sArg.Left(8).CompareNoCase(_T("VarBytes"))!=0){return NULL;}

	for(int iVarNameB1=1; iVarNameB1<=MAX_VARIABLES; iVarNameB1++)
	{
		CString sVarName;
		sVarName.Format(_T("VarBytes%d"), iVarNameB1);

		if(sArg.CompareNoCase(sVarName)==0){return &(g_bytes[iScene][iVarNameB1-1]);}
	}
	
	return NULL;
}



ReturnValue SetBytesValue(CString sDir, int iScene, BYTE* byDstPointer, CString sDataLocal)
{
	
	return RETURN_FAILED;
}
