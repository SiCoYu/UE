#include "MyProject.h"
#include "DynBufResizePolicy.h"

// ��ȡһ������Ĵ�С
uint32 DynBufResizePolicy::getCloseSize(uint32 needSize, uint32 capacity)
{
	uint32 ret = 0;
	if (capacity >= needSize)
	{
		ret = capacity;
	}
	else
	{
		ret = 2 * capacity;
		while (ret < needSize && ret < MAXCAPACITY)
		{
			ret *= 2;
		}

		if (ret > MAXCAPACITY)
		{
			ret = MAXCAPACITY;
		}
	}

	return ret;
}