#include "MyProject.h"
#include "EntityMgrBase.h"
#include "SceneEntityBase.h"
#include "UniqueStrIdGen.h"
#include "UniqueNumIdGen.h"
#include "MacroDef.h"
#include "LogTypeId.h"
#include "Ctx.h"
#include "LogSys.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(EntityMgrBase, DelayPriorityHandleMgrBase)

EntityMgrBase::EntityMgrBase()
{
	//this->mSceneEntityList = new MList<SceneEntityBase*>();
	this->mSceneEntityList.setIsSpeedUpFind(true);
	this->mSceneEntityList.setIsOpKeepSort(true);

	//this->mId2EntityDic = new MDictionary<std::string, SceneEntityBase>();
	//this->mThisId2EntityDic = new MDictionary<uint, SceneEntityBase>();

	this->mUniqueNumIdGen = new UniqueNumIdGen(0);
}

void EntityMgrBase::init()
{

}

void EntityMgrBase::dispose()
{
	this->clearAll();
}

UniqueNumIdGen* EntityMgrBase::getUniqueNumIdGen()
{
	return this->mUniqueNumIdGen;
}

void EntityMgrBase::onPutInPool()
{
	this->clearAll();
}

void EntityMgrBase::_addObject(IDelayHandleItem* entity, float priority)
{
	if (this->_isInDepth())
	{
		Super::_addObject(entity);
	}
	else
	{
		if (!this->mSceneEntityList.contains((SceneEntityBase*)entity))
		{
			this->mSceneEntityList.add((SceneEntityBase*)entity);
		}
	}
}

void EntityMgrBase::_removeObject(IDelayHandleItem* entity)
{
	if (this->_isInDepth())
	{
		Super::_removeObject(entity);
	}
	else
	{
		if (this->mSceneEntityList.contains((SceneEntityBase*)entity))
		{
			this->mSceneEntityList.remove((SceneEntityBase*)entity);
		}
	}
}

void EntityMgrBase::addEntity(SceneEntityBase* entity)
{
	this->_addObject(entity);

	if(!this->mId2EntityDic.containsKey(entity->getEntityUniqueId()))
	{
		this->mId2EntityDic[entity->getEntityUniqueId()] = entity;
	}
	else
	{
		if (MacroDef.ENABLE_LOG)
		{
			GLogSys.log(
				"EntityMgrBase already exist key", 
				LogTypeId::eLogCommon
			);
		}
	}

	if (!this->mThisId2EntityDic.containsKey(entity->getThisId()))
	{
		this->mThisId2EntityDic[entity->getThisId()] = entity;
	}

	//entity->onInit();
}

void EntityMgrBase::removeEntity(SceneEntityBase* entity)
{
	this->_removeObject(entity);

	if (this->mId2EntityDic.containsKey(entity->getEntityUniqueId()))
	{
		this->mId2EntityDic.remove(entity->getEntityUniqueId());
	}
	else
	{
		if (MacroDef.ENABLE_LOG)
		{
			GLogSys.log(
				"EntityMgrBase::removeEntity, already remove key", 
				LogTypeId::eLogCommon
			);
		}
	}

	if (this->mThisId2EntityDic.containsKey(entity->getThisId()))
	{
		this->mThisId2EntityDic.remove(entity->getThisId());
	}
}

bool EntityMgrBase::Contains(SceneEntityBase entity)
{
	return this->mSceneEntityList.contains(entity);
}

void EntityMgrBase::onTick(float delta, TickMode tickMode)
{
	this->_incDepth();

	this->_onTickExec(delta, tickMode);

	this->_decDepth();
}

void EntityMgrBase::_onTickExec(float delta, TickMode tickMode)
{
	int idx = 0;
	int count = this->mSceneEntityList.count();

	SceneEntityBase* entity = nullptr;

	while(idx < count)
	{
		entity = this->mSceneEntityList[idx];

		if (!entity->isClientDispose())
		{
			entity->onTick(delta, tickMode);
		}

		++idx;
	}
}

// 通过 Id 获取元素
SceneEntityBase* EntityMgrBase::getEntityByThisId(uint thisId)
{
	SceneEntityBase* ret = nullptr;

	this->mThisId2EntityDic.tryGetValue(thisId, ret);

	return ret;
}

// 通过 Unique Id 获取元素，Unique Id 是客户端自己的唯一 id ，与服务器没有关系
SceneEntityBase EntityMgrBase::getEntityByUniqueId(std::string uniqueId)
{
	SceneEntityBase* ret = nullptr;

	this->mId2EntityDic.tryGetValue(uniqueId, out ret);

	return ret;
}

// 通过数组下标获取元素
SceneEntityBase* EntityMgrBase::getEntityByIndex(int index)
{
	if (index < this->mSceneEntityList.count())
	{
		return this->mSceneEntityList[index];
	}

	return nullptr;
}

std::string EntityMgrBase::genNewStrId()
{
	return this->mUniqueStrIdGen.genNewStrId();
}

std::string EntityMgrBase::getCurStrId()
{
	return this->mUniqueStrIdGen.getCurStrId();
}

uint EntityMgrBase::getCurId()
{
	return this->mUniqueStrIdGen.getCurId();
}

std::string EntityMgrBase::genStrIdById(uint id)
{
	return this->mUniqueStrIdGen.genStrIdById(id);
}

int EntityMgrBase::getEntityCount()
{
	return this->mSceneEntityList.count();
}

MList<SceneEntityBase*> EntityMgrBase::getSceneEntityList()
{
	return this->mSceneEntityList;
}

void EntityMgrBase::clearAll()
{
	this->_incDepth();

	int len = this->mSceneEntityList.count();
	int idx = len - 1;
	SceneEntityBase* entity = nullptr;

	// 一定要从后往前删除，这样更新索引的时候不会更新所有的索引
	while (idx >= 0)
	{
		entity = this->mSceneEntityList[idx];

		if (!entity->isClientDispose())
		{
			EntityNumIdBufferObjectFactory.deleteObject(entity);
		}

		idx -= 1;
	}

	this->_decDepth();
}

MY_END_NAMESPACE