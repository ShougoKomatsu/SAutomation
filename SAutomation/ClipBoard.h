#pragma once
#include "Variables.h"

BOOL CopyToClipBoardStr(const CString sValue);
BOOL CopyToClipBoardImg(const ImgRGB* imgRGB);
const CString CopyFromClipBoardStr();
BOOL CopyFromClipBoardImg(ImgRGB* imgRGB);
const CString CopyFromClipBoardFilePath();