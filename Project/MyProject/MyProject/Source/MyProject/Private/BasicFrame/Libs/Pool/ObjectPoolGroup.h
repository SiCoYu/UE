#ifndef __ObjectPoolGroup_H
#define __ObjectPoolGroup_H

#include "LockList.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IPoolObject;

/**
 * @brief 对象池
 */
class ObjectPoolGroup
{
protected:
	LockList<IPoolObject*>* mPoolList;

public:
	ObjectPoolGroup();

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

		T* retObj = MY_NEW T();
		return retObj;
	}

	void deleteObj(IPoolObject* obj);
};

MY_END_NAMESPACE

#endif