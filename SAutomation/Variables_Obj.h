#pragma once

#include "stdafx.h"
#include "common.h"

BOOL GetOperandObjSrc(CString sDataLine, int* iCommandType);
Object* GetObjValuePointer(CString sDir, int iScene, CString sArg);
ReturnValue SetObjValue(CString sDir, int iScene, Object* objectDst, CString sData);