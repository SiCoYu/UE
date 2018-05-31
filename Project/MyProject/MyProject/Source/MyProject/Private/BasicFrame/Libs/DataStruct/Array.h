#ifndef __Array_H
#define __Array_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief �ڴ����
 */
class Array
{
public:
	/**
	*@brief �� src �� srcIndex ��ʼ���������ݵ� dest ��ַ�� destIndex ƫ�ƴ����ܹ����� length �ֽڸ���
	*/
	static void Copy(void* src, long srcIndex, void* dest, long destIndex, long length);

	/**
	* @brief �����������ֽ�˳��
	*/
	static void Reverse(char* buff, int index, int length);
	/**
	* @brief ����� index ��ʼ�ģ������� length �� buff ָ���Ļ�����
	*/
	static void Clear(char* buff, int index, int length);
};

#endif