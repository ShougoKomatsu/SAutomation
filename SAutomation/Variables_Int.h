#pragma once

#include "stdafx.h"
#include "common.h"


BOOL GetOperandIntSrc(CString sDataLine, int* iCommandType);
int GetIntValue(int iScene, CString sDataLocal);
int* GetIntValuePointer(int iScene, CString sArg);
int IntAdd(int iScene, CString sArg1, CString sArg2);
int IntSub(int iScene, CString sArg1, CString sArg2);
int IntMult(int iScene, CString sArg1, CString sArg2);
int IntDiv(int iScene, CString sArg1, CString sArg2);
void AssignInt(int iScene, CString sArg, int iInput);
ReturnValue SetIntValue(int* iDstPointer, int iScene, CString sDataLocal, int iSelfSrc);

BOOL GetOperandPointSrc(CString sDataLine, int* iCommandType);

Point* GetPointValuePointer(int iScene, CString sArg);

ReturnValue SetPointValue(Point* pPoint, int iScene, CString sDataLocal);
CRect* GetRectValuePointer(int iScene, CString sArg);
ReturnValue SetRectValue(CRect* pRect, int iScene, CString sDataLocal)
;