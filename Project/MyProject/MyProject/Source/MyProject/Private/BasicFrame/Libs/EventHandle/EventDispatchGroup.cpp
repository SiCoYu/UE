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
void EventDispatchGroup::addEventDispatch(int groupID, EventDispatch* disp)
{
	if (!UtilMap::ContainsKey(this->mGroupID2DispatchDic, groupID))
	{
		this->mGroupID2DispatchDic[groupID] = disp;
	}
}

void EventDispatchGroup::addEventHandle(int groupID, EventDispatchDelegate handle)
{
	this->mGroupID2DispatchDic[groupID]->addEventHandle(handle);
}

void EventDispatchGroup::removeEventHandle(int groupID, EventDispatchDelegate handle)
{
	if (UtilMap::ContainsKey(this->mGroupID2DispatchDic, groupID))
	{
		this->mGroupID2DispatchDic[groupID]->removeEventHandle(handle);
	}
	else
	{
		GLogSys->log("Event Dispatch Group not exist");
	}
}

void EventDispatchGroup::dispatchEvent(int groupID, IDispatchObject* dispatchObject)
{
	this->mIsInLoop = true;

	if (UtilMap::ContainsKey(this->mGroupID2DispatchDic, groupID))
	{
		this->mGroupID2DispatchDic[groupID]->dispatchEvent(dispatchObject);
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

void EventDispatchGroup::clearGroupEventHandle(int groupID)
{
	if (!this->mIsInLoop)
	{
		if (UtilMap::ContainsKey(this->mGroupID2DispatchDic, groupID))
		{
			this->mGroupID2DispatchDic[groupID]->clearEventHandle();
			UtilMap::Remove(mGroupID2DispatchDic, groupID);
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