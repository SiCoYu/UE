#include "MyProject.h"
#include "IRecycleObject.h"
#include "PoolSys.h"

PoolSys::PoolSys()
{
	this->mPoolList = new LockList<IRecycleObject*>("PoolList");
}

void PoolSys::init()
{

}

void PoolSys::dispose()
{

}

void PoolSys::deleteObj(IRecycleObject* obj)
{
	//if (this->mPoolList.IndexOf(obj) == -1)
	//{
	//    this->mPoolList.Add(obj);
	//}
}