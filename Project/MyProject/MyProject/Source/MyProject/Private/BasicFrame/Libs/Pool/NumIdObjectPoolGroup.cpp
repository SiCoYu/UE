#include "MyProject.h"
#include "IPoolObject.h"
#include "NumIdObjectPoolGroup.h"

NumIdObjectPoolGroup::NumIdObjectPoolGroup()
{
	this->mPoolList = new LockList<IPoolObject*>("PoolList");
}

void NumIdObjectPoolGroup::init()
{

}

void NumIdObjectPoolGroup::dispose()
{

}

void NumIdObjectPoolGroup::deleteObj(IPoolObject* obj)
{
	//if (this->mPoolList.IndexOf(obj) == -1)
	//{
	//    this->mPoolList.Add(obj);
	//}
}