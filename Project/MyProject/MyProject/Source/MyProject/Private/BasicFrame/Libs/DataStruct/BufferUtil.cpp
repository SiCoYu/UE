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