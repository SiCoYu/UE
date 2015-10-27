#include "MyProject.h"
#include "BufferUtil.h"
#include <assert.h>
#include <string.h>

void* BufferUtil::memSwap(void* dest, void* source, std::size_t count)
{
	assert((NULL != dest) && (NULL != source));

	char *tmp_source, *tmp_dest;
	char tmpChar;

	tmp_source = (char *)source;
	tmp_dest = (char *)dest;

	// ���û���ص�����
	while (count--)
	{
		tmpChar = *tmp_dest;
		*tmp_dest = *tmp_source;
		*tmp_source = tmpChar;
		++tmp_dest;
		++tmp_source;
	}

	return dest;
}

void BufferUtil::Copy(void* src, long srcIndex, void* dest, long destIndex, long length)
{
	char *tmp_source, *tmp_dest;
	tmp_source = (char *)src + srcIndex;
	tmp_dest = (char *)dest + destIndex;

	// ����memcpy()   ��source  ָ���������destָ���������count���ַ�������������ص���������ú�������Ϊ����memmove(), ����������ص�����ֵ����ȷ���С�memcpy��������Ҫ���Ƶ��ڴ����򲻴����ص����������ȷ������и��Ʋ����ĵ��ڴ�����û���κ��ص�������ֱ����memcpy������㲻�ܱ�֤�Ƿ����ص���Ϊ��ȷ�����Ƶ���ȷ�ԣ��������memmove��memcpy��Ч�ʻ��memmove��һЩ������������׵Ļ����Կ�һЩ���ߵ�ʵ�֣� ����memcpy()   ��source  ָ���������destָ���������count���ַ�������������ص���������ú�������Ϊ����memmove(), ����������ص�����ֵ����ȷ���С�	memcpy��������Ҫ���Ƶ��ڴ����򲻴����ص����������ȷ������и��Ʋ����ĵ��ڴ�����û���κ��ص�������ֱ����memcpy������㲻�ܱ�֤�Ƿ����ص���Ϊ��ȷ�����Ƶ���ȷ�ԣ��������memmove��memcpy��Ч�ʻ��memmove��һЩ
	// ���õ����� 0 ��ʼ�洢���ݣ�ֻҪ�����ԾͿ�����
	memmove(tmp_dest, tmp_source, length);
}

void BufferUtil::Reverse(char* buff, int index, int length)
{
	// ����� length 0 ���� 1 ֱ�ӷ���
	if (length <= 1)
	{
		return;
	}

	char* tmp_source = buff + index;
	char* tmp_dest = buff + index + (length - 1);
	char tmpChar;

	while (tmp_source < tmp_dest)	// ֻ����ʼ��ַû�г���Ŀ�ĵ�ַ�Ž���
	{
		tmpChar = *tmp_dest;
		*tmp_dest = *tmp_source;
		*tmp_source = tmpChar;

		++tmp_source;
		--tmp_dest;
	}
}

void BufferUtil::Clear(char* buff, int index, int length)
{
	memset(buff + index, 0, length);
}