#ifndef __StrIdObjectPoolGroup_H
#define __StrIdObjectPoolGroup_H

#include "LockList.h"

class IPoolObject;

/**
 * @brief 对象池
 */
class StrIdObjectPoolGroup
{
protected:
	LockList<IPoolObject*>* mPoolList;

public:
	StrIdObjectPoolGroup();

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

	void deleteObj(IPoolObject* obj);
};

#endif