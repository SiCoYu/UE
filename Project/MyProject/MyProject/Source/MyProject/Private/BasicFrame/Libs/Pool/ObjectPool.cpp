#include "MyProject.h"
#include "IPoolObject.h"
#include "ObjectPool.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"

MY_BEGIN_NAMESPACE(MyNS)

ObjectPool::ObjectPool()
{
	this->mPoolList = MY_NEW LockList<IPoolObject*>("PoolList");
}

void ObjectPool::init()
{

}

void ObjectPool::dispose()
{

}

void ObjectPool::deleteObj(IPoolObject* obj)
{
	//if (this->mPoolList.IndexOf(obj) == -1)
	//{
	//    this->mPoolList.Add(obj);
	//}
}