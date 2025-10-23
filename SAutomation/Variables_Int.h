#pragma once

#include "stdafx.h"
#include "common.h"


BOOL GetOperandIntSrc(CString sDataLine, int* iCommandType);
BOOL GetOperandPointSrc(CString sDataLine, int* iCommandType);
BOOL GetOperandRectSrc(CString sDataLine, int* iCommandType);


int GetIntValue(CString sDir, int iScene, CString sDataLocal);
BOOL GetRectValue(CString sDir, int iScene, CString sArg, CRect* rectOutput);
BOOL GetPointValue(CString sDir, int iScene, CString sDataLocal, Point* pPoint);

int* GetIntValuePointer(CString sDir, int iScene, CString sArg);
Point* GetPointValuePointer(CString sDir, int iScene, CString sArg);
CRect* GetRectValuePointer(CString sDir, int iScene, CString sArg);



ReturnValue SetIntValue(CString sDir, int iScene, int* iDstPointer, CString sDataLocal, int iSelfSrc);
ReturnValue SetPointValue(CString sDir, int iScene, Point* pPoint, CString sDataLocal);
ReturnValue SetRectValue(CString sDir, int iScene, CRect* pRect, CString sDataLocal);


int IntAdd(CString sDir, int iScene, CString sArg1, CString sArg2);
int IntSub(CString sDir, int iScene, CString sArg1, CString sArg2);
int IntMult(CString sDir, int iScene, CString sArg1, CString sArg2);
int IntDiv(CString sDir, int iScene, CString sArg1, CString sArg2);

int ConvertStr2Int(CString sSrc);