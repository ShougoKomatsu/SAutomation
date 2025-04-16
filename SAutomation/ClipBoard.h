#pragma once
#include "Variables.h"

int CopyToClipBoardStr(const CString sValue);
int CopyToClipBoardImg(const ImgRGB* imgRGB);
const CString CopyFromClipBoardStr();
BOOL CopyFromClipBoardImg(ImgRGB* imgRGB);
const CString CopyFromClipBoardFilePath();