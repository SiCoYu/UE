#include "MyProject.h"
#include "IRecycleObject.h"
#include "ObjectPool.h"

ObjectPool::ObjectPool()
{
	this->mPoolList = new LockList<IRecycleObject*>("PoolList");
}

void ObjectPool::init()
{

}

void ObjectPool::dispose()
{

}

void ObjectPool::deleteObj(IRecycleObject* obj)
{
	//if (this->mPoolList.IndexOf(obj) == -1)
	//{
	//    this->mPoolList.Add(obj);
	//}
}