#include "MyProject.h"
#include "IRecycle.h"
#include "PoolSys.h"

PoolSys::PoolSys()
{
	this->mPoolList = new LockList<IRecycle*>("PoolList");
}

void PoolSys::init()
{

}

void PoolSys::dispose()
{

}

void PoolSys::deleteObj(IRecycle* obj)
{
	//if (this->mPoolList.IndexOf(obj) == -1)
	//{
	//    this->mPoolList.Add(obj);
	//}
}