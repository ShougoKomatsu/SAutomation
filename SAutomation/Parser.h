
#pragma once
#include "stdafx.h"
#ifndef PARSER_DEFINE
#define PARSER_DEFINE

#include "MouseAutomation.h"


BOOL GetCommand(CString sDataLine, int* iCommandType);

BOOL ExtractData(const CString sInput, const CString sDelim, CString* sOut, CString* sRemin);

BOOL PerseCommand(int* iSceneData, CString sDataLine, int* iCommandType, CStringArray* saData, CString sDir);


ErrTreatValue GetErroTreat(CString sDataLine, CString* sLabel);

BOOL PerseLabelFromGotoStatement(CString sData, CString* sLabel);

BOOL ExtractTokenInBracket(CString sInput, int iIndexIn, CString* sToken);

BOOL CountTokenInBracket(CString sParameter, int* iCount);

#endif