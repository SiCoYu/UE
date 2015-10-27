#ifndef __BUFFERUTIL_H
#define __BUFFERUTIL_H

class BufferUtil
{
public:
	/**
	 *@brief �����������е����ݣ�dest �� source ��ʼ���� count ���Լ��������Լ���֤��Խ��
	 */
	static void* memSwap(void* dest, void* source, size_t count);
	/**
	 *@brief �� src �� srcIndex ��ʼ���������ݵ� dest ��ַ�� destIndex ƫ�ƴ����ܹ����� length �ֽڸ���
	 */
	static void Copy(void* src, long srcIndex, void* dest, long destIndex, long length);

	/**
	 * @brief �����������ֽ�˳��
	 */
	static void Reverse(char* buff, int index, int length);

	static void Clear(char* buff, int index, int length);
};

#endif		// __BUFFERUTIL_H