#include "MyProject.h"
#include "IPoolObject.h"
#include "PoolSys.h"

MY_BEGIN_NAMESPACE(MyNS)

PoolSys::PoolSys()
{
	this->mPoolList = MY_NEW LockList<IPoolObject*>("PoolList");
}

void PoolSys::init()
{

}

void PoolSys::dispose()
{

}

void PoolSys::deleteObj(IPoolObject* obj)
{
	//if (this->mPoolList.IndexOf(obj) == -1)
	//{
	//    this->mPoolList.Add(obj);
	//}
}