#ifndef __BufferUtil_H
#define __BufferUtil_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class BufferUtil
{
public:
	/**
	 *@brief �����������е����ݣ�dest �� source ��ʼ���� count ���Լ��������Լ���֤��Խ��
	 */
	static void* memSwap(void* dest, void* source, size_t count);
};

MY_END_NAMESPACE

#endif		// __BufferUtil_H