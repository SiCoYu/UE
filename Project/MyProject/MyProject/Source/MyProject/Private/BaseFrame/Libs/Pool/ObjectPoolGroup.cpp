#include "MyProject.h"
#include "IPoolObject.h"
#include "ObjectPoolGroup.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"

MY_BEGIN_NAMESPACE(MyNS)

ObjectPoolGroup::ObjectPoolGroup()
{
	this->mPoolList = MY_NEW MLockList<IPoolObject*>("PoolList");
}

void ObjectPoolGroup::init()
{

}

void ObjectPoolGroup::dispose()
{

}

void ObjectPoolGroup::deleteObj(IPoolObject* obj)
{
	//if (this->mPoolList.IndexOf(obj) == -1)
	//{
	//    this->mPoolList.Add(obj);
	//}
}

MY_END_NAMESPACE