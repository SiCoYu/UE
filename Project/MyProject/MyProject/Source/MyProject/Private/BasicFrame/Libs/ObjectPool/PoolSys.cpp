#include "MyProject.h"
#include "IRecycle.h"
#include "PoolSys.h"

PoolSys::PoolSys()
{
	mPoolList = new LockList<IRecycle*>("PoolList");
}

void PoolSys::init()
{

}

void PoolSys::dispose()
{

}

void PoolSys::deleteObj(IRecycle* obj)
{
	//if (mPoolList.IndexOf(obj) == -1)
	//{
	//    mPoolList.Add(obj);
	//}
}