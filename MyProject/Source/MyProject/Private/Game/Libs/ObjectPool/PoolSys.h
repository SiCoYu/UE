#ifndef __PoolSys_H
#define __PoolSys_H

#include "LockList.h"

class IRecycle;

/**
 * @brief 对象池
 */
class PoolSys
{
protected:
	LockList<IRecycle*> m_poolList;

public:
	template<class T>
	T* newObject();
	void deleteObj(IRecycle* obj);
};

#endif