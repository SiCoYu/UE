#include "MyProject.h"
#include "EventDispatchGroup.h"
#include "Prequisites.h"
#include "EventDispatch.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(EventDispatchGroup, GObject)

EventDispatchGroup::EventDispatchGroup()
{
	this->mIsInLoop = false;
}

// 添加分发器
void EventDispatchGroup::addEventDispatch(int groupId, EventDispatch* disp)
{
	if (!this->mGroupId2DispatchDic.containsKey(groupId))
	{
		this->mGroupId2DispatchDic[groupId] = disp;
	}
}

void EventDispatchGroup::addEventHandle(int groupId, EventDispatchDelegate handle)
{
	this->mGroupId2DispatchDic[groupId]->addEventHandle(handle);
}

void EventDispatchGroup::removeEventHandle(int groupId, EventDispatchDelegate handle)
{
	if (this->mGroupId2DispatchDic.containsKey(groupId))
	{
		this->mGroupId2DispatchDic[groupId]->removeEventHandle(handle);
	}
	else
	{
		GLogSys->log("Event Dispatch Group not exist");
	}
}

void EventDispatchGroup::dispatchEvent(int groupId, IDispatchObject* dispatchObject)
{
	this->mIsInLoop = true;

	if (this->mGroupId2DispatchDic.containsKey(groupId))
	{
		this->mGroupId2DispatchDic[groupId]->dispatchEvent(dispatchObject);
	}
	else
	{
		GLogSys->log("Event Dispatch Group not exist");
	}

	this->mIsInLoop = false;
}

void EventDispatchGroup::clearAllEventHandle()
{
	if (!this->mIsInLoop)
	{
		// map for 语句
		for(auto dispatch : this->mGroupId2DispatchDic.getData())
		{
			dispatch.second->clearEventHandle();
		}

		this->mGroupId2DispatchDic.clear();
	}
	else
	{
		GLogSys->log("looping cannot delete element");
	}
}

void EventDispatchGroup::clearGroupEventHandle(int groupId)
{
	if (!this->mIsInLoop)
	{
		if (this->mGroupId2DispatchDic.containsKey(groupId))
		{
			this->mGroupId2DispatchDic[groupId]->clearEventHandle();
			mGroupId2DispatchDic.remove(groupId);
		}
		else
		{
			GLogSys->log("Event Dispatch Group not exist");
		}
	}
	else
	{
		GLogSys->log("looping cannot delete element");
	}
}

bool EventDispatchGroup::hasEventHandle(int groupId)
{
	bool ret = false;

	if (this->mGroupId2DispatchDic.containsKey(groupId))
	{
		ret = this->mGroupId2DispatchDic[groupId]->hasEventHandle();
	}

	return ret;
}

MY_END_NAMESPACE