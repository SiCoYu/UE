#include "MyProject.h"
#include "IRecycleObject.h"
#include "StrIdObjectPoolGroup.h"

StrIdObjectPoolGroup::StrIdObjectPoolGroup()
{
	this->mPoolList = new LockList<IRecycleObject*>("PoolList");
}

void StrIdObjectPoolGroup::init()
{

}

void StrIdObjectPoolGroup::dispose()
{

}

void StrIdObjectPoolGroup::deleteObj(IRecycleObject* obj)
{
	//if (this->mPoolList.IndexOf(obj) == -1)
	//{
	//    this->mPoolList.Add(obj);
	//}
}