#include "MyProject.h"
#include "EventDispatchGroup.h"
#include "Common.h"
#include "UtilContainers.h"
#include "EventDispatch.h"

EventDispatchGroup::EventDispatchGroup()
{
	this->mIsInLoop = false;
}

// 添加分发器
void EventDispatchGroup::addEventDispatch(int groupId, EventDispatch* disp)
{
	if (!UtilMap::ContainsKey(this->mGroupID2DispatchDic, groupId))
	{
		this->mGroupID2DispatchDic[groupId] = disp;
	}
}

void EventDispatchGroup::addEventHandle(int groupId, EventDispatchDelegate handle)
{
	this->mGroupID2DispatchDic[groupId]->addEventHandle(handle);
}

void EventDispatchGroup::removeEventHandle(int groupId, EventDispatchDelegate handle)
{
	if (UtilMap::ContainsKey(this->mGroupID2DispatchDic, groupId))
	{
		this->mGroupID2DispatchDic[groupId]->removeEventHandle(handle);
	}
	else
	{
		GLogSys->log("Event Dispatch Group not exist");
	}
}

void EventDispatchGroup::dispatchEvent(int groupId, IDispatchObject* dispatchObject)
{
	this->mIsInLoop = true;

	if (UtilMap::ContainsKey(this->mGroupID2DispatchDic, groupId))
	{
		this->mGroupID2DispatchDic[groupId]->dispatchEvent(dispatchObject);
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
		for(auto dispatch : this->mGroupID2DispatchDic)
		{
			dispatch.second->clearEventHandle();
		}

		this->mGroupID2DispatchDic.clear();
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
		if (UtilMap::ContainsKey(this->mGroupID2DispatchDic, groupId))
		{
			this->mGroupID2DispatchDic[groupId]->clearEventHandle();
			UtilMap::Remove(mGroupID2DispatchDic, groupId);
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