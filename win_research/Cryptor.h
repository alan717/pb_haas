/**************************************************************************
*Copyright(c): Meiya Pico Information Technology Co Ltd
*All rights reserved.
*@n	FileName	:Cryptor.h
*@n	Function	:上次组数据加密解密类
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
	* Brief		:加密函数
	* Param		:pInput	：加密内容
	* Param		:nInputLen ：加密内容长度
	* Return	:const char* ：加密结果
	*************************************************************************/
	const char* encrypt(const char* pInput, int nInputLen);		

	/************************************************************************
	* Function	:decrypt
	* Brief		:解密函数
	* Param		:pInput	：解密内容
	* Param		:nInputLen ：解密内容长度
	* Return	:const char* ：解密结果
	*************************************************************************/
	const char* decrypt(const char* pInput, int nInputLen);		

	/************************************************************************
	* Function	:setKey
	* Brief		:解密函数
	* Param		:pKey：秘钥
	* Return	:void 无返回值
	*************************************************************************/
	void setKey(const char* pKey) const;						

	/************************************************************************
	* Function	:next
	* Brief		:解密函数
	* Return	:int：一个随机值
	*************************************************************************/
	unsigned int next() const;									

	/************************************************************************
	* Function	:teaEncryptECB
	* Brief		:解密函数
	* Param		:pSrcbuf：加密内容
	* Param		:pOutBuf：加密结果
	* Return	:void 无返回值
	*************************************************************************/
	void teaEncryptECB(const char* pSrcbuf, char* pOutBuf);		

	/************************************************************************
	* Function	:teaDecryptECB
	* Brief		:解密函数
	* Param		:pSrcbuf：解密内容
	* Param		:pOutBuf：解密结果
	* Return	:void 无返回值
	*************************************************************************/
	void teaDecryptECB(const char* pSrcbuf, char* pOutBuf);		

	/************************************************************************
	* Function	:teaDecryptECB
	* Brief		:加密数据转换
	* Param		:pSrc：buf地址
	* Param		:nPos：偏移
	* Param		:nCount：字节数
	* Return	:int： 转换后的结果
	*************************************************************************/
	int getValue(const char* pSrc, int nPos, int nCount);	  

	int getLength();											

private:
	int m_nLen;
	char m_key[0x20];
};
#endif
