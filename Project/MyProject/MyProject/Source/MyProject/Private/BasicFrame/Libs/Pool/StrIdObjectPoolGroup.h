#ifndef __StrIdObjectPoolGroup_H
#define __StrIdObjectPoolGroup_H

#include "MLockList.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IPoolObject;

/**
 * @brief 对象池
 */
class StrIdObjectPoolGroup : public GObject
{
protected:
	MLockList<IPoolObject*>* mPoolList;

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