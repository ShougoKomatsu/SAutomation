#include "stdafx.h"
#ifndef PERSER_DEFINE
#define PERSER_DEFINE

#include "MouseAutomation.h"
#include "Automation.h"


BOOL GetCommand(CString sDataLine, int* iCommandType);

BOOL ExtractData(const CString sInput, const CString sDelim, CString* sOut, CString* sRemin);

BOOL PerseCommand(int* iSceneData, CString sDataLine, int* iCommandType, CStringArray* saData, CString sDir);


ErrTreatValue GetErroTreat(CString sDataLine, CString* sLabel);

BOOL PerseLabelFromGotoStatement(CString sData, CString* sLabel);
#endif