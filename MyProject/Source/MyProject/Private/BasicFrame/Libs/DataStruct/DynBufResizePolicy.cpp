#include "MyProject.h"
#include "DynBufResizePolicy.h"

// ��ȡһ������Ĵ�С
uint32 DynBufResizePolicy::getCloseSize(uint32 needSize, uint32 capacity, uint32 maxCapacity)
{
	uint32 ret = 0;

	if (needSize <= maxCapacity)
	{
		if (capacity >= needSize)
		{
			ret = capacity;
		}
		else
		{
			ret = 2 * capacity;
			while (ret < needSize && ret < maxCapacity)
			{
				ret *= 2;
			}

			if (ret > maxCapacity)
			{
				ret = maxCapacity;
			}
		}
	}
	else	// ��Ҫ�����ݱ���������������Ĵ�С����
	{
		// ��־����Ҫ�Ĵ洢�ռ�̫��
	}

	return ret;
}