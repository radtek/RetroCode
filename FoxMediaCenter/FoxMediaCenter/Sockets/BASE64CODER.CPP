
//  Base64Coder.cpp

#include "stdafx.h"
#include "Base64Coder.h"

// Digits...
static char	Base64Digits[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

#ifndef PAGESIZE
#define PAGESIZE					4096
#endif

#ifndef ROUNDTOPAGE
#define ROUNDTOPAGE(a)			(((a/4096)+1)*4096)
#endif

Base64Coder::Base64Coder()
:	m_pDBuffer(NULL),
	m_pEBuffer(NULL),
	m_nDBufLen(0),
	m_nEBufLen(0)
{
}

Base64Coder::~Base64Coder()
{
	if(m_pDBuffer != NULL)
		delete [] m_pDBuffer;

	if(m_pEBuffer != NULL)
		delete [] m_pEBuffer;
}

void Base64Coder::Encode(LPCTSTR szMessage)
{
	if(szMessage != NULL)
		Base64Coder::Encode((const PBYTE)szMessage, strlen(szMessage));
}

void Base64Coder::Encode(const PBYTE pBuffer, DWORD nBufLen)
{
	SetDecodeBuffer(pBuffer, nBufLen);
	AllocEncode(nBufLen * 2);

	TempBucket	Raw;
	DWORD		nIndex	= 0;

	while((nIndex + 3) <= nBufLen)
	{
		Raw.Clear();
		::CopyMemory(&Raw, m_pDBuffer + nIndex, 3);
		Raw.nSize = 3;
		_EncodeToBuffer(Raw, m_pEBuffer + m_nEDataLen);
		nIndex		+= 3;
		m_nEDataLen	+= 4;
	}

	if(nBufLen > nIndex)
	{
		Raw.Clear();
		Raw.nSize = (BYTE) (nBufLen - nIndex);
		::CopyMemory(&Raw, m_pDBuffer + nIndex, nBufLen - nIndex);
		_EncodeToBuffer(Raw, m_pEBuffer + m_nEDataLen);
		m_nEDataLen += 4;
	}
}

void Base64Coder::SetDecodeBuffer(const PBYTE pBuffer, DWORD nBufLen)
{
	AllocDecode(nBufLen);
	::CopyMemory(m_pDBuffer, pBuffer, nBufLen);
	m_nDDataLen = nBufLen;
}

void Base64Coder::AllocDecode(DWORD nSize)
{
	if(m_nDBufLen < nSize)
	{
		if(m_pDBuffer != NULL)
			delete [] m_pDBuffer;

		m_nDBufLen = ROUNDTOPAGE(nSize);
		m_pDBuffer = new BYTE[m_nDBufLen];
	}

	::ZeroMemory(m_pDBuffer, m_nDBufLen);
	m_nDDataLen = 0;
}

void Base64Coder::AllocEncode(DWORD nSize)
{
	if(m_nEBufLen < nSize)
	{
		if(m_pEBuffer != NULL)
			delete [] m_pEBuffer;

		m_nEBufLen = ROUNDTOPAGE(nSize);
		m_pEBuffer = new BYTE[m_nEBufLen];
	}

	::ZeroMemory(m_pEBuffer, m_nEBufLen);
	m_nEDataLen = 0;
}

void Base64Coder::_EncodeToBuffer(const TempBucket &Decode, PBYTE pBuffer)
{
	TempBucket	Data;

	_EncodeRaw(Data, Decode);

	for(int i = 0; i < 4; i++)
		pBuffer[i] = Base64Digits[Data.nData[i]];

	switch(Decode.nSize)
	{
	case 1:
		pBuffer[2] = '=';
	case 2:
		pBuffer[3] = '=';
	}
}

void Base64Coder::_EncodeRaw(TempBucket &Data, const TempBucket &Decode)
{
	BYTE		nTemp;

	Data.nData[0] = Decode.nData[0];
	Data.nData[0] >>= 2;
	
	Data.nData[1] = Decode.nData[0];
	Data.nData[1] <<= 4;
	nTemp = Decode.nData[1];
	nTemp >>= 4;
	Data.nData[1] |= nTemp;
	Data.nData[1] &= 0x3F;

	Data.nData[2] = Decode.nData[1];
	Data.nData[2] <<= 2;

	nTemp = Decode.nData[2];
	nTemp >>= 6;

	Data.nData[2] |= nTemp;
	Data.nData[2] &= 0x3F;

	Data.nData[3] = Decode.nData[2];
	Data.nData[3] &= 0x3F;
}

BOOL Base64Coder::_IsBadMimeChar(BYTE nData)
{
	switch(nData)
	{
		case '\r': case '\n': case '\t': case ' ' :
		case '\b': case '\a': case '\f': case '\v':
			return TRUE;
		default:
			return FALSE;
	}
}

LPCTSTR Base64Coder::EncodedMessage() const
{ 
	return (LPCTSTR) m_pEBuffer;
}


