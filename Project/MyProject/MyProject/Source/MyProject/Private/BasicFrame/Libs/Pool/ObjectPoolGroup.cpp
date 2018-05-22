#include "MyProject.h"
#include "IPoolObject.h"
#include "ObjectPoolGroup.h"

ObjectPoolGroup::ObjectPoolGroup()
{
	this->mPoolList = new LockList<IPoolObject*>("PoolList");
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