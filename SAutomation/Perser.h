#include "stdafx.h"
#include "MouseAutomation.h"

BOOL GetCommand(CString sDataLine, int* iCommandType);

BOOL ExtractData(const CString sInput, const CString sDelim, CString* sOut, CString* sRemin);

BOOL PerseCommand(int* iSceneData, CString sDataLine, int* iCommandType, CStringArray* saData);