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
	LockList<IRecycle*> mPoolList;

public:
	void init();
	void dispose();

	template<class T>
	T* newObject()
	{
		//T retObj = default(T);
		//// 查找
		//int idx = 0;
		//for(idx = 0; idx < mPoolList.Count; ++idx)
		//{
		//    if (typeof(T) == mPoolList[idx].GetType())
		//    {
		//        retObj = (T)mPoolList[idx];
		//        mPoolList.RemoveAt(idx);
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