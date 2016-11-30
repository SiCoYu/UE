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
	T* newObject()
	{
		//T retObj = default(T);
		//// 查找
		//int idx = 0;
		//for(idx = 0; idx < m_poolList.Count; ++idx)
		//{
		//    if (typeof(T) == m_poolList[idx].GetType())
		//    {
		//        retObj = (T)m_poolList[idx];
		//        m_poolList.RemoveAt(idx);
		//        MethodInfo myMethodInfo = retObj.GetType().GetMethod("resetDefault");
		//        if (myMethodInfo != null)
		//        {
		//            myMethodInfo.Invoke(retObj, null);
		//        }
		//        return retObj;
		//    }
		//}

		T* retObj = new T();
		return retObj;
	}

	void deleteObj(IRecycle* obj);
};

#endif