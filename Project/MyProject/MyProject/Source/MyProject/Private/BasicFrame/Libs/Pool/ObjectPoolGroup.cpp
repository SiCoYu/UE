#include "MyProject.h"
#include "IRecycleObject.h"
#include "ObjectPoolGroup.h"

ObjectPoolGroup::ObjectPoolGroup()
{
	this->mPoolList = new LockList<IRecycleObject*>("PoolList");
}

void ObjectPoolGroup::init()
{

}

void ObjectPoolGroup::dispose()
{

}

void ObjectPoolGroup::deleteObj(IRecycleObject* obj)
{
	//if (this->mPoolList.IndexOf(obj) == -1)
	//{
	//    this->mPoolList.Add(obj);
	//}
}