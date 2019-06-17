#include "MyProject.h"
#include "SceneEntityMgrBase.h"
#include "SceneEntityBase.h"
#include "UniqueStrIdGen.h"
#include "UniqueNumIdGen.h"
#include "MacroDef.h"
#include "LogTypeId.h"
#include "Ctx.h"
#include "LogSys.h"
#include "SafePointer.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(SceneEntityMgrBase, DelayPriorityHandleMgrBase)

SceneEntityMgrBase::SceneEntityMgrBase()
{
	//this->mSceneEntityList = new MList<SceneEntityBase*>();
	//this->mSceneEntityList.setIsSpeedUpFind(true);
	//this->mSceneEntityList.setIsOpKeepSort(true);

	//this->mId2EntityDic = new MDictionary<std::string, SceneEntityBase>();
	//this->mThisId2EntityDic = new MDictionary<uint, SceneEntityBase>();

	this->mUniqueNumIdGen = MY_NEW UniqueNumIdGen(0);
}

void SceneEntityMgrBase::init()
{

}

void SceneEntityMgrBase::dispose()
{
	this->clearAll();
}

UniqueNumIdGen* SceneEntityMgrBase::getUniqueNumIdGen()
{
	return this->mUniqueNumIdGen;
}

void SceneEntityMgrBase::onPutInPool()
{
	this->clearAll();
}

void SceneEntityMgrBase::_addObject(IDelayHandleItem* entity, float priority)
{
	if (this->_isInDepth())
	{
		Super::_addObject(entity);
	}
	else
	{
		SceneEntityBase* sceneEntity = (SceneEntityBase*)entity;

		if (!this->mSceneEntityList.contains(sceneEntity))
		{
			this->mSceneEntityList.add(sceneEntity);
		}
	}
}

void SceneEntityMgrBase::_removeObject(IDelayHandleItem* entity)
{
	if (this->_isInDepth())
	{
		Super::_removeObject(entity);
	}
	else
	{
		SceneEntityBase* sceneEntity = (SceneEntityBase*)entity;

		if (this->mSceneEntityList.contains(sceneEntity))
		{
			this->mSceneEntityList.remove(sceneEntity);
		}
	}
}

void SceneEntityMgrBase::addEntity(SceneEntityBase* entity)
{
	this->_addObject(entity);

	std::string uniqueId = entity->getGlobalUniqueId();

	if(!this->mId2EntityDic.containsKey(uniqueId))
	{
		this->mId2EntityDic[uniqueId] = entity;
	}
	else
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log(
				"SceneEntityMgrBase already exist key", 
				LogTypeId::eLogCommon
			);
		}
	}

	uint thisId = entity->getThisId();

	if (!this->mThisId2EntityDic.containsKey(thisId))
	{
		this->mThisId2EntityDic[thisId] = entity;
	}

	//entity->onInit();
}

void SceneEntityMgrBase::removeEntity(SceneEntityBase* entity)
{
	this->_removeObject(entity);

	std::string uniqueId = entity->getGlobalUniqueId();

	if (this->mId2EntityDic.containsKey(uniqueId))
	{
		this->mId2EntityDic.remove(uniqueId);
	}
	else
	{
		if (MacroDef::ENABLE_LOG)
		{
			GLogSys->log(
				"SceneEntityMgrBase::removeEntity, already remove key", 
				LogTypeId::eLogCommon
			);
		}
	}

	uint thisId = entity->getThisId();

	if (this->mThisId2EntityDic.containsKey(thisId))
	{
		this->mThisId2EntityDic.remove(thisId);
	}
}

bool SceneEntityMgrBase::Contains(SceneEntityBase* entity)
{
	return this->mSceneEntityList.contains(entity);
}

void SceneEntityMgrBase::onTick(float delta, TickMode tickMode)
{
	this->_incDepth();

	this->_onTickExec(delta, tickMode);

	this->_decDepth();
}

void SceneEntityMgrBase::_onTickExec(float delta, TickMode tickMode)
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
SceneEntityBase* SceneEntityMgrBase::getEntityByThisId(uint thisId)
{
	SceneEntityBase* ret = nullptr;

	this->mThisId2EntityDic.tryGetValue(thisId, ret);

	return ret;
}

// 通过 Unique Id 获取元素，Unique Id 是客户端自己的唯一 id ，与服务器没有关系
SceneEntityBase* SceneEntityMgrBase::getEntityByUniqueId(std::string uniqueId)
{
	SceneEntityBase* ret = nullptr;

	this->mId2EntityDic.tryGetValue(uniqueId, ret);

	return ret;
}

// 通过数组下标获取元素
SceneEntityBase* SceneEntityMgrBase::getEntityByIndex(int index)
{
	if (index < this->mSceneEntityList.count())
	{
		return this->mSceneEntityList[index];
	}

	return nullptr;
}

std::string SceneEntityMgrBase::genNewStrId()
{
	return this->mUniqueStrIdGen->genNewStrId();
}

std::string SceneEntityMgrBase::getCurStrId()
{
	return this->mUniqueStrIdGen->getCurStrId();
}

uint SceneEntityMgrBase::getCurId()
{
	return this->mUniqueStrIdGen->getCurId();
}

std::string SceneEntityMgrBase::genStrIdById(uint id)
{
	return this->mUniqueStrIdGen->genStrIdById(id);
}

int SceneEntityMgrBase::getEntityCount()
{
	return this->mSceneEntityList.count();
}

MList<SceneEntityBase*> SceneEntityMgrBase::getSceneEntityList()
{
	return this->mSceneEntityList;
}

void SceneEntityMgrBase::clearAll()
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
			//EntityNumIdBufferObjectFactory.deleteObject(entity);
			MY_SAFE_DISPOSE(entity);
		}

		idx -= 1;
	}

	this->_decDepth();
}

MY_END_NAMESPACE