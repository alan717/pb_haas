#include "Cryptor.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

Cryptor::Cryptor()
{
	srand(unsigned(time(0)));
}

Cryptor::~Cryptor()
{

}

const char* Cryptor::encrypt(const char* pInput, int nInputLen)
{
	char* pRet = nullptr;
	
	if (nullptr  == pInput || nInputLen == 0)
	{
		return pRet;
	}

	int nPadSaltBodyZeroLen = 0;
	int nPadlen = 0;;
	char arySrcBuf[8] = { 0 };
	char aryIvPlain[8] = { 0 };
	char *pIvCrypt = nullptr;;
	int nSrci = 0;
	int i = 0;
	int j = 0;
	char* pOutBuf = nullptr;

	nPadSaltBodyZeroLen = nInputLen + 1 + 9;
	if ((nPadlen = nPadSaltBodyZeroLen % 8))
	{

		nPadlen = 8 - nPadlen;
	}

	int nLen = nInputLen + nPadlen + 10;

	pOutBuf = new char[nLen]; //申请加密buf

	m_nLen = nLen;
	if (nullptr == pOutBuf)
	{
		return pRet;
	}

	memset(pOutBuf, 0, nLen);

	arySrcBuf[0] = (((char)next()) & 0x0f8) | (char)nPadlen;
	nSrci = 1;

	while (nPadlen--)
	{
		arySrcBuf[nSrci++] = (char)next();
	}
	
	for (i = 0; i < 8; i++)
	{
		aryIvPlain[i] = 0;
	}
	pIvCrypt = aryIvPlain;

	for (i = 1; i <= 2;)
	{
		if (nSrci < 8)
		{
			arySrcBuf[nSrci++] = (char)next();
			i++;
		}

		if (nSrci == 8)
		{

			for (j = 0; j < 8; j++)
			{
				arySrcBuf[j] ^= pIvCrypt[j];
			}

			teaEncryptECB(arySrcBuf, pOutBuf);

			for (j = 0; j < 8; j++)
			{
				pOutBuf[j] ^= aryIvPlain[j];
			}

			/*保存当前的iv_plain*/
			for (j = 0; j < 8; j++)
			{
				aryIvPlain[j] = arySrcBuf[j];
			}

			nSrci = 0;
			pIvCrypt = pOutBuf;
			pOutBuf += 8;
		}
	}

	while (nInputLen)
	{
		if (nSrci < 8)
		{
			arySrcBuf[nSrci++] = *(pInput++);
			nInputLen--;
		}


		//缓冲区够八个 进行加密处理
		if (nSrci == 8)
		{

			for (j = 0; j < 8; j++)
				arySrcBuf[j] ^= pIvCrypt[j];
		
			teaEncryptECB(arySrcBuf, pOutBuf);

			for (j = 0; j < 8; j++)
				pOutBuf[j] ^= aryIvPlain[j];

			for (j = 0; j < 8; j++)
				aryIvPlain[j] = arySrcBuf[j];

			nSrci = 0;
			pIvCrypt = pOutBuf;
		
			pOutBuf += 8;
		}
	}
	i = 1;

	while (i < 8)
	{
		if (nSrci < 8)
		{
			arySrcBuf[nSrci++] = 0;
			i++;
		}

		if (nSrci == 8)
		{

			for (j = 0; j < 8; j++)
			{
				arySrcBuf[j] ^= pIvCrypt[j];
			}
		
			teaEncryptECB(arySrcBuf, pOutBuf);

			for (j = 0; j < 8; j++)
			{
				pOutBuf[j] ^= aryIvPlain[j];
			}
				
			for (j = 0; j < 8; j++)
			{
				aryIvPlain[j] = arySrcBuf[j];
			}
				
			nSrci = 0;
			pIvCrypt = pOutBuf;
			pOutBuf += 8;
		}
	}

	pRet = pOutBuf - nLen;
	return pRet;
}

void Cryptor::teaEncryptECB(const char* pSrcbuf, char* pOutBuf)
{
	int a = getValue(pSrcbuf, 0, 4);
	int a2 = getValue(pSrcbuf, 4, 4);
	int a3 = getValue(m_key, 0, 4);
	int a4 = getValue(m_key, 4, 4);
	int a5 = getValue(m_key, 8, 4);
	int a6 = getValue(m_key, 12, 4);
	int j = 0;
	int j2 = -1640531527 & 4294967295L;

	for(int i = 0; i < 16; i++)
	{
		j = (j + j2) & 4294967295L;
		a = (a + ((((a2 << 4) + a3) ^ (a2 + j)) ^ (((unsigned int)a2 >> 5) + a4))) & 4294967295L;
		a2 = (a2 + ((((a << 4) + a5) ^ (a + j)) ^ (((unsigned int)a >> 5) + a6))) & 4294967295L;
	}

	*(int*)pOutBuf = getValue((char*)&a, 0, 4);
	*(int*)(pOutBuf + 4) = getValue((char*)&a2, 0, 4);
}

int Cryptor::getValue(const char* pSrc, int nPos, int nCount)
{
	int nTemp;
	long lTemp = 0;

	if (nCount > 4)
	{
		nTemp = nPos + 4;
	}
	else 
	{
		nTemp = nPos + nCount;
	}

	while (nPos < nTemp)
	{
		lTemp = (lTemp << 8) | ((long)(pSrc[nPos] & 255));
		nPos++;
	}
	return 4294967295L & lTemp;
}

const char* Cryptor::decrypt(const char* pInput, int nInputLen)
{
	char* pRet = NULL;

	int nPadLen = 0;
	int nPlainLen = 0;
	char aryDestBuf[8] = { 0 };
	char aryZeroBuf[8] = { 0 };
	const char* pIvPreCrypt = nullptr; //前一个解密块
	const char* pivCurCrypt = nullptr; //当前一个解密块
	int nDestLen = 0;
	int  i = 0; 
	int j = 0;
	const char *pInBufBoundary = nullptr;
	int nBufPos = 0;

	if ((nInputLen % 8) || (nInputLen < 16))
		return pRet;

	if (nullptr == pInput || nInputLen == 0)
	{
		return pRet;
	}

	//第一次解密求长度
	teaDecryptECB(pInput, aryDestBuf);

	nPadLen = aryDestBuf[0] & 0x7/*只要最低三位*/;

	i = nInputLen - nPadLen - 10;
	if ((nInputLen < i) || (i < 0))
	{
		return pRet;
	}

	m_nLen = i;

	char* pOutput = new char[m_nLen];

	if (nullptr ==  pOutput)
	{
		return pRet;
	}

	memset(pOutput, 0, m_nLen);

	for (i = 0; i < 8; i++)
		aryZeroBuf[i] = 0;

	pIvPreCrypt = aryZeroBuf;
	pivCurCrypt = pInput;

	pInput += 8;
	nBufPos += 8;
	nDestLen = 1;
	nDestLen += nPadLen;

	for (i = 1; i <= 2;)
	{
		if (nDestLen < 8)
		{
			nDestLen++;
			i++;
		}

		if (nDestLen == 8)
		{
			pIvPreCrypt = pivCurCrypt;
			pivCurCrypt = pInput;

			for (j = 0; j < 8; j++)
			{
				if ((nBufPos + j) >= nInputLen)
					return pRet;

				aryDestBuf[j] ^= pInput[j];
			}

			teaDecryptECB(aryDestBuf, aryDestBuf);
			
			pInput += 8;
			nBufPos += 8;
			nDestLen = 0;
		}
	}

	nPlainLen = m_nLen;
	while (nPlainLen)
	{
		if (nDestLen < 8)
		{
			*(pOutput++) = aryDestBuf[nDestLen] ^ pIvPreCrypt[nDestLen];
			nDestLen++;
			nPlainLen--;
		}
		else if (nDestLen == 8)
		{

			pIvPreCrypt = pivCurCrypt;
			pivCurCrypt = pInput;
	
			for (j = 0; j < 8; j++)
			{
				if ((nBufPos + j) >= nInputLen)
					return pRet;
				aryDestBuf[j] ^= pInput[j];
			}

			teaDecryptECB(aryDestBuf, aryDestBuf);

			pInput += 8;
			nBufPos += 8;
			nDestLen = 0;
		}
	}

	for (i = 1; i <= 2;)
	{
		if (nDestLen < 8)
		{
			if (aryDestBuf[nDestLen] ^ pIvPreCrypt[nDestLen])
				return pRet;
			nDestLen++;
			i++;
		}
		else if (nDestLen == 8)
		{
			/*改变前一个加密块的指针*/
			pIvPreCrypt = pivCurCrypt;
			pivCurCrypt = pInput;

			/*解开一个新的加密块*/

			/*异或前一块明文(在nDestLen[]中)*/
			for (j = 0; j < 8; j++)
			{
				if ((nBufPos + j) >= nInputLen)
					return pRet;
				aryDestBuf[j] ^= pInput[j];
			}

			teaDecryptECB(aryDestBuf, aryDestBuf);

			/*在取出的时候才异或前一块密文(pivCurCrypt)*/

			pInput += 8;
			nBufPos += 8;
		}
	}

	pRet = pOutput - m_nLen;
	return pRet;
}

void Cryptor::teaDecryptECB(const char* pSrcbuf, char* pOutBuf)
{
	int a = getValue(pSrcbuf, 0, 4);
	int a2 = getValue(pSrcbuf, 4, 4);
	int a3 = getValue(m_key, 0, 4);
	int a4 = getValue(m_key, 4, 4);
	int a5 = getValue(m_key, 8, 4);
	int a6 = getValue(m_key, 12, 4);
	int j = -478700656 & 4294967295L;
	int j2 = -1640531527 & 4294967295L;

	for (int i = 0; i < 16; i++)
	{
		a2 = (a2 - ((((a << 4) + a5) ^ (a + j)) ^ (((unsigned int)a >>  5) + a6))) & 4294967295L;
		a = (a - ((((a2 << 4) + a3) ^ (a2 + j)) ^ (((unsigned int)a2 >> 5) + a4))) & 4294967295L;
		j = (j - j2) & 4294967295L;
	}

	*(int*)pOutBuf = getValue((char*)&a, 0, 4);
	*(int*)(pOutBuf + 4) = getValue((char*)&a2, 0, 4);
}

unsigned int Cryptor::next() const
{
	return 10;
}	

void Cryptor::setKey(const char* pKey) const
{
	memcpy((char*)m_key, pKey, 0x20);
}

int Cryptor::getLength()
{
	return m_nLen;
}