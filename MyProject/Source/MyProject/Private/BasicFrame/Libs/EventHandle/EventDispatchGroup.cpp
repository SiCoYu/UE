#include "MyProject.h"
#include "EventDispatchGroup.h"
#include "Common.h"
#include "UtilContainers.h"
#include "EventDispatch.h"

EventDispatchGroup::EventDispatchGroup()
{
	mIsInLoop = false;
}

// 添加分发器
void EventDispatchGroup::addEventDispatch(int groupID, EventDispatch* disp)
{
	if (!UtilMap::ContainsKey(mGroupID2DispatchDic, groupID))
	{
		mGroupID2DispatchDic[groupID] = disp;
	}
}

void EventDispatchGroup::addEventHandle(int groupID, EventDispatchDelegate handle)
{
	mGroupID2DispatchDic[groupID]->addEventHandle(handle);
}

void EventDispatchGroup::removeEventHandle(int groupID, EventDispatchDelegate handle)
{
	if (UtilMap::ContainsKey(mGroupID2DispatchDic, groupID))
	{
		mGroupID2DispatchDic[groupID]->removeEventHandle(handle);
	}
	else
	{
		GLogSys->log("Event Dispatch Group not exist");
	}
}

void EventDispatchGroup::dispatchEvent(int groupID, IDispatchObject* dispatchObject)
{
	mIsInLoop = true;
	if (UtilMap::ContainsKey(mGroupID2DispatchDic, groupID))
	{
		mGroupID2DispatchDic[groupID]->dispatchEvent(dispatchObject);
	}
	else
	{
		GLogSys->log("Event Dispatch Group not exist");
	}
	mIsInLoop = false;
}

void EventDispatchGroup::clearAllEventHandle()
{
	if (!mIsInLoop)
	{
		// map for 语句
		for(auto dispatch : mGroupID2DispatchDic)
		{
			dispatch.second->clearEventHandle();
		}

		mGroupID2DispatchDic.clear();
	}
	else
	{
		GLogSys->log("looping cannot delete element");
	}
}

void EventDispatchGroup::clearGroupEventHandle(int groupID)
{
	if (!mIsInLoop)
	{
		if (UtilMap::ContainsKey(mGroupID2DispatchDic, groupID))
		{
			mGroupID2DispatchDic[groupID]->clearEventHandle();
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