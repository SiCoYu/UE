﻿#ifndef __PoolSys_H
#define __PoolSys_H

#include "MLockList.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IPoolObject;

/**
 * @brief 对象池
 */
class PoolSys : public GObject
{
protected:
	MLockList<IPoolObject*>* mPoolList;

public:
	PoolSys();

	void init();
	void dispose();

	template<class T>
	T* newObject()
	{
		//T retObj = default(T);
		//// 查找
		//int index = 0;
		//for(index = 0; index < mPoolList.Count; ++index)
		//{
		//    if (typeof(T) == mPoolList[index].GetType())
		//    {
		//        retObj = (T)mPoolList[index];
		//        mPoolList.RemoveAt(index);
		//        MethodInfo myMethodInfo = retObj.GetType().GetMethod("resetDefault");
		//        if (myMethodInfo != nullptr)
		//        {
		//            myMethodInfo.Invoke(retObj, nullptr);
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