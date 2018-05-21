#include "MyProject.h"
#include "IRecycleObject.h"
#include "NumIdObjectPoolGroup.h"

NumIdObjectPoolGroup::NumIdObjectPoolGroup()
{
	this->mPoolList = new LockList<IRecycleObject*>("PoolList");
}

void NumIdObjectPoolGroup::init()
{

}

void NumIdObjectPoolGroup::dispose()
{

}

void NumIdObjectPoolGroup::deleteObj(IRecycleObject* obj)
{
	//if (this->mPoolList.IndexOf(obj) == -1)
	//{
	//    this->mPoolList.Add(obj);
	//}
}