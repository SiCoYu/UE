#pragma once

#include <string>
#include "DelayPriorityHandleMgrBase.h"
#include "ITickedObject.h"
#include "INoOrPriorityObject.h"
#include "MDictionary.h"
#include "MList.h"
#include "TickMode.h"
#include "TypeDef.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityBase;
class UniqueStrIdGen;
class UniqueNumIdGen;

class SceneEntityMgrBase : public DelayPriorityHandleMgrBase, public ITickedObject, public INoOrPriorityObject
{
	M_DECLARE_CLASS(SceneEntityMgrBase, DelayPriorityHandleMgrBase)

protected:
	MList<SceneEntityBase*> mSceneEntityList;
	MDictionary<std::string, SceneEntityBase*> mId2EntityDic;
	MDictionary<uint, SceneEntityBase*> mThisId2EntityDic;
	UniqueStrIdGen* mUniqueStrIdGen;
	UniqueNumIdGen* mUniqueNumIdGen;

public:
	SceneEntityMgrBase();

	virtual void init() override;
	virtual void dispose() override;
	UniqueNumIdGen* getUniqueNumIdGen();
	virtual void onPutInPool();

protected:
	virtual void _addObject(IDelayHandleItem* entity, float priority = 0.0f) override;
	virtual void _removeObject(IDelayHandleItem* entity) override;

public:
	virtual void addEntity(SceneEntityBase* entity);
	virtual void removeEntity(SceneEntityBase* entity);
	bool Contains(SceneEntityBase* entity);
	virtual void onTick(float delta, TickMode tickMode);

protected:
	virtual void _onTickExec(float delta, TickMode tickMode);

public:
	// 通过 Id 获取元素
	SceneEntityBase* getEntityByThisId(uint thisId);
	// 通过 Unique Id 获取元素，Unique Id 是客户端自己的唯一 id ，与服务器没有关系
	SceneEntityBase* getEntityByUniqueId(std::string uniqueId);
	// 通过数组下标获取元素
	SceneEntityBase* getEntityByIndex(int index);
	std::string genNewStrId();
	std::string getCurStrId();
	uint getCurId();
	std::string genStrIdById(uint id);
	int getEntityCount();
	MList<SceneEntityBase*> getSceneEntityList();
	virtual void clearAll();
};

MY_END_NAMESPACE