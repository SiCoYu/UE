#include "MyProject.h"
#include "IPoolObject.h"
#include "ObjectPool.h"

ObjectPool::ObjectPool()
{
	this->mPoolList = new LockList<IPoolObject*>("PoolList");
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