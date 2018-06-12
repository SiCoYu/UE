#pragma once

#include <string>
#include "DelayPriorityHandleMgrBase.h"
#include "ITickedObject.h"
#include "INoOrPriorityObject.h"
#include "MDictionary.h"
#include "MList.h"
#include "TickMode.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityBase;
class UniqueStrIdGen;
class UniqueNumIdGen;

class EntityMgrBase : public DelayPriorityHandleMgrBase, public ITickedObject, public INoOrPriorityObject
{
protected
	MList<SceneEntityBase*> mSceneEntityList;
	MDictionary<std::string, SceneEntityBase*> mId2EntityDic;
	MDictionary<uint, SceneEntityBase*> mThisId2EntityDic;
	UniqueStrIdGen* mUniqueStrIdGen;
	UniqueNumIdGen* mUniqueNumIdGen;

public:
	EntityMgrBase()
	{
		//this.mSceneEntityList = new MList<SceneEntityBase*>();
		this.mSceneEntityList.setIsSpeedUpFind(true);
		this.mSceneEntityList.setIsOpKeepSort(true);

		//this.mId2EntityDic = new MDictionary<std::string, SceneEntityBase>();
		//this.mThisId2EntityDic = new MDictionary<uint, SceneEntityBase>();

		this.mUniqueNumIdGen = new UniqueNumIdGen(0);
	}

	virtual void init() override
	{

	}

	virtual void dispose() override
	{
		this.clearAll();
	}

	UniqueNumIdGen* getUniqueNumIdGen()
	{
		return this.mUniqueNumIdGen;
	}

	virtual void onPutInPool()
	{
		this.clearAll();
	}

protected:
	virtual void _addObject(IDelayHandleItem* entity, float priority = 0.0f) override
	{
		if (this._isInDepth())
		{
			base._addObject(entity);
		}
		else
		{
			if (!this.mSceneEntityList.contains((SceneEntityBase*)entity))
			{
				this.mSceneEntityList.add((SceneEntityBase*)entity);
			}
		}
	}

	virtual void _removeObject(IDelayHandleItem* entity) override
	{
		if (this._isInDepth())
		{
			base._removeObject(entity);
		}
		else
		{
			if (this.mSceneEntityList.contains((SceneEntityBase*)entity))
			{
				this.mSceneEntityList.remove((SceneEntityBase*)entity);
			}
		}
	}

public:
	virtual void addEntity(SceneEntityBase* entity)
	{
		this._addObject(entity);

		if(!this.mId2EntityDic.containsKey(entity.getEntityUniqueId()))
		{
			this.mId2EntityDic[entity.getEntityUniqueId()] = entity;
		}
		else
		{
			if (MacroDef.ENABLE_LOG)
			{
				Ctx.msInstance.mLogSys.log("EntityMgrBase already exist key", LogTypeId.eLogCommon);
			}
		}

		if (!this.mThisId2EntityDic.containsKey(entity.getThisId()))
		{
			this.mThisId2EntityDic[entity.getThisId()] = entity;
		}

		//entity.onInit();
	}

	virtual void removeEntity(SceneEntityBase* entity)
	{
		this._removeObject(entity);

		if (this.mId2EntityDic.containsKey(entity.getEntityUniqueId()))
		{
			this.mId2EntityDic.remove(entity.getEntityUniqueId());
		}
		else
		{
			if (MacroDef.ENABLE_LOG)
			{
				Ctx.msInstance.mLogSys.log("EntityMgrBase::removeEntity, already remove key", LogTypeId.eLogCommon);
			}
		}

		if (this.mThisId2EntityDic.containsKey(entity.getThisId()))
		{
			this.mThisId2EntityDic.remove(entity.getThisId());
		}
	}

	bool Contains(SceneEntityBase entity)
	{
		return this.mSceneEntityList.contains(entity);
	}

	virtual void onTick(float delta, TickMode tickMode)
	{
		this._incDepth();

		this._onTickExec(delta, tickMode);

		this._decDepth();
	}

protected:
	virtual void _onTickExec(float delta, TickMode tickMode)
	{
		int idx = 0;
		int count = this.mSceneEntityList.count();

		SceneEntityBase* entity = null;

		while(idx < count)
		{
			entity = this.mSceneEntityList[idx];

			if (!entity.isClientDispose())
			{
				entity.onTick(delta, tickMode);
			}

			++idx;
		}
	}

public:
	// 通过 Id 获取元素
	SceneEntityBase* getEntityByThisId(uint thisId)
	{
		SceneEntityBase* ret = null;

		this.mThisId2EntityDic.tryGetValue(thisId, out ret);

		return ret;
	}

	// 通过 Unique Id 获取元素，Unique Id 是客户端自己的唯一 id ，与服务器没有关系
	SceneEntityBase getEntityByUniqueId(std::string uniqueId)
	{
		SceneEntityBase* ret = null;

		this.mId2EntityDic.tryGetValue(uniqueId, out ret);

		return ret;
	}

	// 通过数组下标获取元素
	SceneEntityBase* getEntityByIndex(int index)
	{
		if (index < this.mSceneEntityList.count())
		{
			return this.mSceneEntityList[index];
		}

		return null;
	}

	std::string genNewStrId()
	{
		return this.mUniqueStrIdGen.genNewStrId();
	}

	std::string getCurStrId()
	{
		return this.mUniqueStrIdGen.getCurStrId();
	}

	uint getCurId()
	{
		return this.mUniqueStrIdGen.getCurId();
	}

	std::string genStrIdById(uint id)
	{
		return this.mUniqueStrIdGen.genStrIdById(id);
	}

	int getEntityCount()
	{
		return this.mSceneEntityList.count();
	}

	MList<SceneEntityBase*> getSceneEntityList()
	{
		return this.mSceneEntityList;
	}

	virtual void clearAll()
	{
		this._incDepth();

		int len = this.mSceneEntityList.count();
		int idx = len - 1;
		SceneEntityBase* entity = null;

		// 一定要从后往前删除，这样更新索引的时候不会更新所有的索引
		while (idx >= 0)
		{
			entity = this.mSceneEntityList[idx];

			if (!entity.isClientDispose())
			{
				EntityNumIdBufferObjectFactory.deleteObject(entity);
			}

			idx -= 1;
		}

		this._decDepth();
	}
}

MY_END_NAMESPACE