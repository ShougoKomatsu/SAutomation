#include "stdafx.h"
#include "ClipBoard.h"


BOOL DispAvailableClipboardFormat()
{
	int iFormat;
	iFormat = 0;
	while(1)
	{
		CString sFormat;

		iFormat = EnumClipboardFormats(iFormat);
		switch(iFormat)
		{
		case 0:{ return TRUE;}
		case CF_TEXT:{ sFormat.Format(_T("CF_TEXT"));break;}
		case CF_BITMAP:{ sFormat.Format(_T("CF_BITMAP"));break;}
		case CF_METAFILEPICT:{ sFormat.Format(_T("CF_METAFILEPICT"));break;}
		case CF_SYLK:{ sFormat.Format(_T("CF_SYLK"));break;}
		case CF_DIF:{ sFormat.Format(_T("CF_DIF"));break;}
		case CF_TIFF:{ sFormat.Format(_T("CF_TIFF"));break;}
		case CF_OEMTEXT:{ sFormat.Format(_T("CF_OEMTEXT"));break;}
		case CF_DIB:{ sFormat.Format(_T("CF_DIB"));break;}
		case CF_PALETTE:{ sFormat.Format(_T("CF_PALETTE"));break;}
		case CF_PENDATA:{ sFormat.Format(_T("CF_PENDATA"));break;}
		case CF_RIFF:{ sFormat.Format(_T("CF_RIFF"));break;}
		case CF_WAVE:{ sFormat.Format(_T("CF_WAVE"));break;}
		case CF_UNICODETEXT:{ sFormat.Format(_T("CF_UNICODETEXT"));break;}
		case CF_ENHMETAFILE:{ sFormat.Format(_T("CF_ENHMETAFILE"));break;}
		case CF_HDROP:{ sFormat.Format(_T("CF_HDROP"));break;}
		case CF_LOCALE:{ sFormat.Format(_T("CF_LOCALE"));break;}
		case CF_DIBV5:{ sFormat.Format(_T("CF_DIBV5"));break;}
		case CF_MAX:{ sFormat.Format(_T("CF_MAX"));break;}
		default:
			{
				TCHAR tchData[256];
				int iRet = GetClipboardFormatName(iFormat, tchData, 255);
				if(iRet>0)
				{
					sFormat.Format(_T("%s"),tchData);
				}
				else
				{
					sFormat.Format(_T(""));
				}
			}
		}



		CString sss;
		sss.Format(_T("%d %s"),iFormat, sFormat);
		AfxMessageBox(sss);
		if(iFormat == 0){break;}
	}
	return TRUE;
}


int CopyToClipBoardStr(const CString sValue)
{
	BOOL bRet;
	bRet = OpenClipboard(g_hWnd);
	if(bRet == FALSE){return RETURN_FAILED;}
//	DispAvailableClipboardFormat();
	bRet = EmptyClipboard();
	if(bRet == FALSE){return RETURN_FAILED;}

	
	HGLOBAL hGL;
	hGL = GlobalAlloc(GPTR, (sValue.GetLength()+1)*sizeof(TCHAR) );
	if(hGL==NULL){return RETURN_FAILED;}

	_stprintf((TCHAR*)hGL, _T("%s"), sValue);
	
	HANDLE hResult;
	hResult = SetClipboardData(CF_UNICODETEXT, hGL);
	if(hResult == NULL)
	{
		GlobalFree(hGL);
		return RETURN_FAILED;
	}

	bRet = CloseClipboard();
	if(bRet == FALSE)
	{
		GlobalFree(hGL);
		return RETURN_FAILED;
	}
	return RETURN_NORMAL;
}

int CopyToClipBoardImg(const ImgRGB* imgRGB)
{
	int iFillerSize;

	if(((imgRGB->iWidth*3)%4)==0)
	{
		iFillerSize = 0;
	}
	else
	{
		iFillerSize = (4-((imgRGB->iWidth*3)%4));
	}


	int iBitSize;

	iBitSize = ((imgRGB->iWidth*3)+iFillerSize)*(imgRGB->iHeight);

	
	BOOL bRet;
	bRet = OpenClipboard(g_hWnd);
	if(bRet == FALSE){return RETURN_FAILED;}
	
	

	HGLOBAL hGL= GlobalAlloc(GPTR, sizeof(BITMAPINFOHEADER)+iBitSize);
	
	BITMAPINFOHEADER* bmih=(BITMAPINFOHEADER*)hGL;
	BYTE* byOutBuf=(BYTE*)(bmih + 1);
	
	bmih->biSize=0x00000028;
	bmih->biWidth=imgRGB->iWidth;
	bmih->biHeight=imgRGB->iHeight;
	bmih->biPlanes=1;
	bmih->biBitCount=24;
	bmih->biCompression=0;
	bmih->biSizeImage=iBitSize;
	bmih->biXPelsPerMeter=0;
	bmih->biYPelsPerMeter=0;
	bmih->biClrUsed=0;
	bmih->biClrImportant=0;

	if(imgRGB->iChannel==CHANNEL_3_8)
	{
		for(int r=0; r<imgRGB->iHeight; r++)
		{
			for(int c=0; c<imgRGB->iWidth; c++)
			{
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFillerSize+0] = imgRGB->byImgB[(imgRGB->iHeight-r-1)*imgRGB->iWidth+c];
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFillerSize+1] = imgRGB->byImgG[(imgRGB->iHeight-r-1)*imgRGB->iWidth+c];
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFillerSize+2] = imgRGB->byImgR[(imgRGB->iHeight-r-1)*imgRGB->iWidth+c];
			}
		}
	}
	if(imgRGB->iChannel==CHANNEL_1_24BGR)
	{
		for(int r=0; r<imgRGB->iHeight; r++)
		{
			for(int c=0; c<imgRGB->iWidth; c++)
			{
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFillerSize+0] = imgRGB->byImg[3*((imgRGB->iHeight-r-1)*imgRGB->iWidth+c)+0];
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFillerSize+1] = imgRGB->byImg[3*((imgRGB->iHeight-r-1)*imgRGB->iWidth+c)+1];
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFillerSize+2] = imgRGB->byImg[3*((imgRGB->iHeight-r-1)*imgRGB->iWidth+c)+2];
			}
		}
	}
	if(imgRGB->iChannel==CHANNEL_1_8)
	{
		for(int r=0; r<imgRGB->iHeight; r++)
		{
			for(int c=0; c<imgRGB->iWidth; c++)
			{
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFillerSize+0] = imgRGB->byImg[(imgRGB->iHeight-r-1)*imgRGB->iWidth+c];
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFillerSize+1] = imgRGB->byImg[(imgRGB->iHeight-r-1)*imgRGB->iWidth+c];
				byOutBuf[3*(r*imgRGB->iWidth+c)+r*iFillerSize+2] = imgRGB->byImg[(imgRGB->iHeight-r-1)*imgRGB->iWidth+c];
			}
		}
	}

	HANDLE hResult;
	hResult = SetClipboardData(CF_DIB, hGL);
	if(hResult == NULL)
	{
		GlobalFree(hGL);
		return RETURN_FAILED;
	}

	bRet = CloseClipboard();
	if(bRet == FALSE)
	{
		GlobalFree(hGL);
		return RETURN_FAILED;
	}
	return RETURN_NORMAL;
}

const CString CopyFromClipBoardStr()
{
	BOOL bRet;

	bRet = OpenClipboard(g_hWnd);
	if(bRet == FALSE){return _T("");}

	HANDLE hResult;
	hResult = GetClipboardData(CF_UNICODETEXT);
	if(hResult == NULL){return _T("");}

	LPVOID pStr = GlobalLock(hResult);
	if(pStr==NULL){return _T("");}

	CString sResult;
	sResult.Format(_T("%s"), pStr);

	GlobalUnlock(hResult);

	bRet = CloseClipboard();
	if(bRet == FALSE){return _T("");}

	return sResult;
}

const CString CopyFromClipBoardFilePath()
{
	BOOL bRet;

	bRet = OpenClipboard(g_hWnd);
	if(bRet == FALSE){return _T("");}
//	DispAvailableClipboardFormat();
	bRet = IsClipboardFormatAvailable(49159);
	if(bRet != TRUE)
	{
		CloseClipboard();
		return _T("");
	}

	HANDLE hResult;
	hResult = GetClipboardData(49159);
	if(hResult == NULL){return _T("");}

	LPVOID pStr = GlobalLock(hResult);
	if(pStr==NULL){return _T("");}

	CString sResult;
	sResult.Format(_T("%s"), pStr);

	GlobalUnlock(hResult);

	bRet = CloseClipboard();
	if(bRet == FALSE){return _T("");}

	return sResult;
}

BOOL CopyFromClipBoardImg(ImgRGB* imgRGB)
{
	BOOL bRet;
	BITMAPINFOHEADER bmih;

	bRet = OpenClipboard(g_hWnd);
	if(bRet == FALSE){return FALSE;}

	HANDLE hResult;
	hResult = GetClipboardData(CF_DIB);
	if(hResult == NULL){return FALSE;}

	LPVOID byData = GlobalLock(hResult);
	if(byData==NULL){return FALSE;}
	
	for(int i=0; i<sizeof(bmih); i++)
	{
		((BYTE*)&bmih)[i] = ((BYTE*)byData)[i];
	}
	int iWidthLocal;
	int iHeightLocal;

	iWidthLocal = bmih.biWidth;
	if(bmih.biHeight<0){iHeightLocal=-1*(bmih.biHeight);}
	else{iHeightLocal=(bmih.biHeight);}

	if(bmih.biClrUsed>0)
	{
		return FALSE;
	}

	BYTE* byImgData;
	byImgData = &(((BYTE*)(byData))[sizeof(BITMAPINFOHEADER)]);
		
	
	int iFiller;

	imgRGB->Set(iWidthLocal, iHeightLocal, CHANNEL_3_8);
	
	iFiller = iWidthLocal%4;

	for(int r=0; r<iHeightLocal; r++)
	{
		for(int c=0; c< iWidthLocal; c++)
		{
			(imgRGB->byImgB)[(imgRGB->iHeight - r -1) *imgRGB->iWidth+c]=byImgData[3*( r*iWidthLocal + c)+r*iFiller+0];
			(imgRGB->byImgG)[(imgRGB->iHeight - r -1) *imgRGB->iWidth+c]=byImgData[3*( r*iWidthLocal + c)+r*iFiller+1];
			(imgRGB->byImgR)[(imgRGB->iHeight - r -1) *imgRGB->iWidth+c]=byImgData[3*( r*iWidthLocal + c)+r*iFiller+2];
		}
	}

	GlobalUnlock(hResult);

	bRet = CloseClipboard();
	if(bRet == FALSE){return FALSE;}

	return TRUE;
}
