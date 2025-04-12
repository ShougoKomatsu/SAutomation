#pragma once
#include "Variables.h"

int CopyToClipBoardStr(CString sValue);
int CopyToClipBoardImg(ImgRGB* imgRGB);
const CString CopyFromClipBoardStr();
BOOL CopyFromClipBoardImg(ImgRGB* imgRGB);