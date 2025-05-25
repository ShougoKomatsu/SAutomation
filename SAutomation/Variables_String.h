#pragma once

#include "stdafx.h"
#include "common.h"

BOOL GetOperandStrSrc(CString sDataLine, int* iCommandType);
const CString GetStrValue(CString sDir, int iScene, CString sDataLocal);
CString* GetStrValuePointer(CString sDir, int iScene, CString sArg);


ReturnValue SetStrValue(CString sDir, int iScene, CString* sDstPointer, CString sDataLocal);

const CString StrCombine(CString sDir, int iScene, CString sArg1, CString sArg2);
const CString StrLeft(CString sDir, int iScene, CString sArg1, CString sArg2);
const CString StrRight(CString sDir, int iScene, CString sArg1, CString sArg2);
const CString StrMid(CString sDir, int iScene, CString sArg1, CString sArg2, CString sArg3);
const CString NowDateTime(CString sArg);
