#ifndef __BUFFERUTIL_H
#define __BUFFERUTIL_H

class BufferUtil
{
public:
	/**
	 *@brief �����������е����ݣ�dest �� source ��ʼ���� count ���Լ��������Լ���֤��Խ��
	 */
	static void* memSwap(void* dest, void* source, size_t count);
};

#endif		// __BUFFERUTIL_H