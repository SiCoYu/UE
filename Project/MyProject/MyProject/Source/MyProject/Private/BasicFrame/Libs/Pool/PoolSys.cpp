#include "MyProject.h"
#include "PoolSys.h"
#include "IPoolObject.h"
#include "SafePointer.h"

MY_BEGIN_NAMESPACE(MyNS)

PoolSys::PoolSys()
{
	this->mPoolList = MY_NEW MLockList<IPoolObject*>("PoolList");
}

void PoolSys::init()
{

}

void PoolSys::dispose()
{
	MY_SAFE_DISPOSE(this->mPoolList);
}

void PoolSys::deleteObj(IPoolObject* obj)
{
	//if (this->mPoolList.IndexOf(obj) == -1)
	//{
	//    this->mPoolList.Add(obj);
	//}
}

MY_END_NAMESPACE