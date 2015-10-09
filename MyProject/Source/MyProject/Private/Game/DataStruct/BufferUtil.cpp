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

	// 如果没有重叠区域
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
	char tmpChar;

	tmp_source = (char *)src + srcIndex;
	tmp_dest = (char *)dest + destIndex;

	// 函数memcpy()   从source  指向的区域向dest指向的区域复制count个字符，如果两数组重叠，不定义该函数的行为。而memmove(), 如果两函数重叠，赋值仍正确进行。memcpy函数假设要复制的内存区域不存在重叠，如果你能确保你进行复制操作的的内存区域没有任何重叠，可以直接用memcpy；如果你不能保证是否有重叠，为了确保复制的正确性，你必须用memmove。memcpy的效率会比memmove高一些，如果还不明白的话可以看一些两者的实现： 函数memcpy()   从source  指向的区域向dest指向的区域复制count个字符，如果两数组重叠，不定义该函数的行为。而memmove(), 如果两函数重叠，赋值仍正确进行。	memcpy函数假设要复制的内存区域不存在重叠，如果你能确保你进行复制操作的的内存区域没有任何重叠，可以直接用memcpy；如果你不能保证是否有重叠，为了确保复制的正确性，你必须用memmove。memcpy的效率会比memmove高一些
	// 不用调整从 0 开始存储数据，只要是线性就可以了
	memmove(tmp_dest, tmp_source, length);
}