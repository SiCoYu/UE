#include "MyProject.h"
#include "IPoolObject.h"
#include "StrIdObjectPoolGroup.h"

MY_BEGIN_NAMESPACE(MyNS)

StrIdObjectPoolGroup::StrIdObjectPoolGroup()
{
	this->mPoolList = MY_NEW LockList<IPoolObject*>("PoolList");
}

void StrIdObjectPoolGroup::init()
{

}

void StrIdObjectPoolGroup::dispose()
{

}

void StrIdObjectPoolGroup::deleteObj(IPoolObject* obj)
{
	//if (this->mPoolList.IndexOf(obj) == -1)
	//{
	//    this->mPoolList.Add(obj);
	//}
}