#include "MyProject.h"
#include "IPoolObject.h"
#include "NumIdObjectPoolGroup.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"

MY_BEGIN_NAMESPACE(MyNS)

NumIdObjectPoolGroup::NumIdObjectPoolGroup()
{
	this->mPoolList = MY_NEW LockList<IPoolObject*>("PoolList");
}

void NumIdObjectPoolGroup::init()
{

}

void NumIdObjectPoolGroup::dispose()
{

}

void NumIdObjectPoolGroup::deleteObj(IPoolObject* obj)
{
	//if (this->mPoolList.IndexOf(obj) == -1)
	//{
	//    this->mPoolList.Add(obj);
	//}
}