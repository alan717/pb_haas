/**************************************************************************
*Copyright(c): Meiya Pico Information Technology Co Ltd
*All rights reserved.
*@n	FileName	:Cryptor.h
*@n	Function	:�ϴ������ݼ��ܽ�����
*@n	Author		:libo@mail.pico.net
*@n	Version		:V1.0
*@n	DataTime	:2019-03-08
*@n	Brief		:
****************************************************************************/

#ifndef _CRYPTOR_H_
#define _CRYPTOR_H_

class Cryptor
{
public:
	Cryptor();
	~Cryptor();

	/************************************************************************
	* Function	:encrypt
	* Brief		:���ܺ���
	* Param		:pInput	����������
	* Param		:nInputLen ���������ݳ���
	* Return	:const char* �����ܽ��
	*************************************************************************/
	const char* encrypt(const char* pInput, int nInputLen);		

	/************************************************************************
	* Function	:decrypt
	* Brief		:���ܺ���
	* Param		:pInput	����������
	* Param		:nInputLen ���������ݳ���
	* Return	:const char* �����ܽ��
	*************************************************************************/
	const char* decrypt(const char* pInput, int nInputLen);		

	/************************************************************************
	* Function	:setKey
	* Brief		:���ܺ���
	* Param		:pKey����Կ
	* Return	:void �޷���ֵ
	*************************************************************************/
	void setKey(const char* pKey) const;						

	/************************************************************************
	* Function	:next
	* Brief		:���ܺ���
	* Return	:int��һ�����ֵ
	*************************************************************************/
	unsigned int next() const;									

	/************************************************************************
	* Function	:teaEncryptECB
	* Brief		:���ܺ���
	* Param		:pSrcbuf����������
	* Param		:pOutBuf�����ܽ��
	* Return	:void �޷���ֵ
	*************************************************************************/
	void teaEncryptECB(const char* pSrcbuf, char* pOutBuf);		

	/************************************************************************
	* Function	:teaDecryptECB
	* Brief		:���ܺ���
	* Param		:pSrcbuf����������
	* Param		:pOutBuf�����ܽ��
	* Return	:void �޷���ֵ
	*************************************************************************/
	void teaDecryptECB(const char* pSrcbuf, char* pOutBuf);		

	/************************************************************************
	* Function	:teaDecryptECB
	* Brief		:��������ת��
	* Param		:pSrc��buf��ַ
	* Param		:nPos��ƫ��
	* Param		:nCount���ֽ���
	* Return	:int�� ת����Ľ��
	*************************************************************************/
	int getValue(const char* pSrc, int nPos, int nCount);	  

	int getLength();											

private:
	int m_nLen;
	char m_key[0x20];
};
#endif
