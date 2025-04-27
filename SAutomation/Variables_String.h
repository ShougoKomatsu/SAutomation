#pragma once

#include "stdafx.h"
#include "common.h"


#define FORMATO (_T("%d"))
#define FORMAT_FLAG_MASK			(0x0000F000)
#define FORMAT_FLAG_NOTHING			(0x00000000)
#define FORMAT_FLAG_SPACE			(0x00001000)
#define FORMAT_FLAG_PLUS			(0x00002000)
#define FORMAT_FLAG_ZERO			(0x00003000)

#define FORMAT_MIN_FIELD_MASK		(0x000F0000)
#define FORMAT_MIN_FIELD_SHIFT		(16)

#define FORMAT_ACCURACY_MASK		(0x00F00000)
#define FORMAT_ACCURACY_SHIFT		(20)


#define FORMAT_QUALIFIER_MASK		(0x03000000)
#define FORMAT_QUALIFIER_NOTHING	(0x00000000)
#define FORMAT_QUALIFIER_HALF		(0x01000000)
#define FORMAT_QUALIFIER_LONG		(0x02000000)

#define FORMAT_FLAG_UNSIGNED		(0x04000000)

#define FORMAT_SPECIFIER_MASK		 (0xF0000000)
#define FORMAT_SPECIFIER_DECIMAL	 (0x10000000)
#define FORMAT_SPECIFIER_SMALL_HEX	 (0x20000000)
#define FORMAT_SPECIFIER_CAPITAL_HEX (0x30000000)


BOOL GetOperandStrSrc(CString sDataLine, int* iCommandType);
const CString GetStrValue(int iScene, CString sDataLocal);
CString* GetStrValuePointer(int iScene, CString sArg);



const CString StrCombine(int iScene, CString sArg1, CString sArg2);
const CString StrLeft(int iScene, CString sArg1, CString sArg2);
const CString StrRight(int iScene, CString sArg1, CString sArg2);
const CString StrMid(int iScene, CString sArg1, CString sArg2, CString sArg3);
const CString NowDateTime(CString sArg);
ReturnValue SetStrValue(CString* sDstPointer, int iScene, CString sDataLocal);
BOOL PerseFormat(CString sFormat, int* iFormatOut);

const CString Int2Str(int iScene, CString sArg, CString sFormat);
int Str2Int(int iScene, CString sArg);