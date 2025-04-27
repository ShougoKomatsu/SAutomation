#pragma once

#include "stdafx.h"
#include "common.h"

BOOL GetOperandObjSrc(CString sDataLine, int* iCommandType);
Object* GetObjValuePointer(int iScene, CString sArg);
ReturnValue SetObjValue(Object* objectDst, int iScene, CString sData);