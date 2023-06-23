#include "stdafx.h"

#define CHANNEL_UNDEFINED (0)
#define CHANNEL_1_8 (1)
#define CHANNEL_3_8 (3)
#define CHANNEL_1_24 (24)

struct ImgRGB
{
	int iWidth;
	int iHeight;
	int iChannel;
	BYTE* byImgR;
	BYTE* byImgG;
	BYTE* byImgB;
	BOOL Set(int iWidthIn, int iHeightIn, int iChannelIn)
	{
		Init();
		if(iWidthIn<=0){return FALSE;}
		if(iHeightIn<=0){return FALSE;}

		iWidth = iWidthIn;
		iHeight = iHeightIn;
		iChannel = iChannelIn;
		if(iChannel == CHANNEL_1_8)
		{
			byImgR = new BYTE[iWidth*iHeight];
		}
		if(iChannel == CHANNEL_3_8)
		{
			byImgR = new BYTE[iWidth*iHeight];
			byImgG = new BYTE[iWidth*iHeight];
			byImgB = new BYTE[iWidth*iHeight];
		}
		if(iChannel == CHANNEL_1_24)
		{
			byImgR = new BYTE[iWidth*iHeight*3];
		}
		return TRUE;
	}
	BOOL Init()
	{
		if(byImgR!=NULL){delete [] byImgR; byImgR=NULL;}
		if(byImgG!=NULL){delete [] byImgG; byImgG=NULL;}
		if(byImgB!=NULL){delete [] byImgB; byImgB=NULL;}
		iWidth=0;
		iHeight=0;
		iChannel=CHANNEL_UNDEFINED;
		return TRUE;
	}
	ImgRGB(){byImgR=NULL;byImgG=NULL;byImgB=NULL;Init();}
	~ImgRGB(){Init();}
	BOOL Assign(CString sFilePath);
};
BOOL Screenshot(ImgRGB* imgRGB);

BOOL IsInRegion(ImgRGB* imgTarget, ImgRGB* imgModel, int iR0, int iC0, int iR1, int iC1);