#pragma once

#include "stdafx.h"
#include "common.h"



inline BYTE ConvertCharToUpperByte(char cU)
{
	if(cU=='0'){return 0x00;}
	if(cU=='1'){return 0x10;}
	if(cU=='2'){return 0x20;}
	if(cU=='3'){return 0x30;}
	if(cU=='4'){return 0x40;}
	if(cU=='5'){return 0x50;}
	if(cU=='6'){return 0x60;}
	if(cU=='7'){return 0x70;}
	if(cU=='8'){return 0x80;}
	if(cU=='9'){return 0x90;}
	if(cU=='A'){return 0xA0;}
	if(cU=='B'){return 0xB0;}
	if(cU=='C'){return 0xC0;}
	if(cU=='D'){return 0xD0;}
	if(cU=='E'){return 0xE0;}
	if(cU=='F'){return 0xF0;}
	if(cU=='a'){return 0xA0;}
	if(cU=='b'){return 0xB0;}
	if(cU=='c'){return 0xC0;}
	if(cU=='d'){return 0xD0;}
	if(cU=='e'){return 0xE0;}
	if(cU=='f'){return 0xF0;}
	return 0;
}

inline BYTE ConvertCharToByte(char cU, char cL)
{
	if(cL=='0'){return ConvertCharToUpperByte(cU) + 0x00;}
	if(cL=='1'){return ConvertCharToUpperByte(cU) + 0x01;}
	if(cL=='2'){return ConvertCharToUpperByte(cU) + 0x02;}
	if(cL=='3'){return ConvertCharToUpperByte(cU) + 0x03;}
	if(cL=='4'){return ConvertCharToUpperByte(cU) + 0x04;}
	if(cL=='5'){return ConvertCharToUpperByte(cU) + 0x05;}
	if(cL=='6'){return ConvertCharToUpperByte(cU) + 0x06;}
	if(cL=='7'){return ConvertCharToUpperByte(cU) + 0x07;}
	if(cL=='8'){return ConvertCharToUpperByte(cU) + 0x08;}
	if(cL=='9'){return ConvertCharToUpperByte(cU) + 0x09;}
	if(cL=='A'){return ConvertCharToUpperByte(cU) + 0x0A;}
	if(cL=='B'){return ConvertCharToUpperByte(cU) + 0x0B;}
	if(cL=='C'){return ConvertCharToUpperByte(cU) + 0x0C;}
	if(cL=='D'){return ConvertCharToUpperByte(cU) + 0x0D;}
	if(cL=='F'){return ConvertCharToUpperByte(cU) + 0x0F;}
	if(cL=='E'){return ConvertCharToUpperByte(cU) + 0x0E;}
	if(cL=='a'){return ConvertCharToUpperByte(cU) + 0x0A;}
	if(cL=='b'){return ConvertCharToUpperByte(cU) + 0x0B;}
	if(cL=='c'){return ConvertCharToUpperByte(cU) + 0x0C;}
	if(cL=='d'){return ConvertCharToUpperByte(cU) + 0x0D;}
	if(cL=='e'){return ConvertCharToUpperByte(cU) + 0x0E;}
	if(cL=='f'){return ConvertCharToUpperByte(cU) + 0x0F;}
	return ConvertCharToUpperByte(cU);
}
struct ByteVector
{
	BYTE* m_byData;
	int m_iLength;

	ByteVector(){m_byData=NULL;Init();}
	~ByteVector(){m_byData=NULL;Init();}
	void Init(){if(m_byData != NULL){delete [] m_byData;} m_byData=NULL; m_iLength=0;}
	BOOL Assign(BYTE* byData, int iLength)
	{
		Init();
		m_byData=new BYTE[iLength];

		memcpy(m_byData, byData, iLength);
		return TRUE;
	}

	BOOL Assign(CString* sData)
	{
		Init();
		int iStrLen=sData->GetLength();
		int iFilling=(iStrLen%2);
		int iByteLen=(iStrLen/2)+(iFilling);

		m_byData=new BYTE[iByteLen];
		for(int i=0; i<iByteLen; i++)
		{
			char cU;
			char cL;

			cU=sData->GetAt(2*i+0);

			if(i == iByteLen-1)
			{
				if(iFilling==1)
				{
					m_byData[i]=ConvertCharToByte(cU, 0);
					return TRUE;
				}

				cL = sData->GetAt(2*i + 1);
				m_byData[i]=ConvertCharToByte(cU, cL);
				return TRUE;
			}


			cL=sData->GetAt(2*i + 1);
			m_byData[i]=ConvertCharToByte(cU, cL);
		}

		return FALSE;
	}
};

BOOL GetOperandBytesSrc(CString sDataLine, int* iCommandType);
ByteVector* GetSetBytesValuePointer(CString sDir, int iScene, CString sArg);


ReturnValue SetBytesValue(CString sDir, int iScene, BYTE* byDstPointer, CString sDataLocal);
