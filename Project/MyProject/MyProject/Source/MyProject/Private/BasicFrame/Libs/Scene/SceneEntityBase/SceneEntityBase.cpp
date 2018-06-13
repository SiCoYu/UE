#include "MyProject.h"
#include "SceneEntityBase.h"
#include "UtilMath.h"
#include "UtilEngineWrap.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(SceneEntityBase, DelayPriorityHandleMgrBase)

SceneEntityBase::SceneEntityBase()
{
	this->mRotate = MWrapQuaternion(0, 0, 0, 1);
	this->mRender = nullptr;
}

// 这个接口调用之前，一定要先设置 ThisId ，调用 setThisId，必须先设置这个
void SceneEntityBase::init()
{
	this->onInit();
}

void SceneEntityBase::_onPreInit()
{

}

void SceneEntityBase::_onExecInit()
{

}

void SceneEntityBase::_onPostInit()
{

}

void SceneEntityBase::onInit()
{
	this->_onPreInit();
	this->_onExecInit();
	this->_onPostInit();
}

// 释放接口
void SceneEntityBase::dispose()
{
	this->onDestroy();
}

// 释放的时候回调的接口
void SceneEntityBase::onDestroy()
{
	if (nullptr != this->mRender)
	{
		this->mRender.dispose();
		this->mRender = nullptr;
	}

	if(nullptr != this->mTDTile)
	{
		this->mTDTile.removeEntity(this);
		this->mTDTile = nullptr;
	}

	this->setClientDispose(true);
}

// 缓存回收
void SceneEntityBase::onPutInPool()
{
	/*if (nullptr != this->mRender)
	{
		this->mRender.putInPool();
	}

	this->mRotate.clear();*/
}

void SceneEntityBase::onGetFromPool()
{
	//this->mPos = UtilMath.ZeroVec3;
	//this->mRotate.setRotateXYZW(0, 0, 0, 1);
	//this->mScale = UtilMath::OneVec3;

	//this->mIsVisible = false;        // 当前逻辑是否可见
}

void SceneEntityBase::show()
{
	if (!this->mIsVisible)
	{
		this->mIsVisible = true;

		if (nullptr != this->mRender)
		{
			this->mRender->show();
		}

		this->onClipShow();
	}
}

void SceneEntityBase::hide()
{
	if (this->mIsVisible)
	{
		this->mIsVisible = false;

		if (nullptr != this->mRender)
		{
			this->mRender->hide();
		}
	}
}

bool SceneEntityBase::IsVisible()
{
	return this->mIsVisible;
}

void SceneEntityBase::setClientDispose(bool isDispose)
{
	if (nullptr != this->mRender)
	{
		this->mRender->setClientDispose(isDispose);
	}
}

AActor* SceneEntityBase::getActor()
{
	if(nullptr != this->mRender)
	{
		return this->mRender->getSelfActor();
	}

	return nullptr;
}

// 每一帧执行
void SceneEntityBase::onTick(float delta, TickMode tickMode)
{
	this->_onPreTick(delta, tickMode);
	this->_onExecTick(delta, tickMode);
	this->_onPostTick(delta, tickMode);

	if (nullptr != this->mRender)
	{
		this->mRender->onTick(delta, tickMode);
	}
}

// Tick 第一阶段执行
void SceneEntityBase::_onPreTick(float delta, TickMode tickMode)
{

}

void SceneEntityBase::_onExecTick(float delta, TickMode tickMode)
{

}

// Tick 第二阶段执行
void SceneEntityBase::_onPostTick(float delta, TickMode tickMode)
{

}

uint SceneEntityBase::getThisId()
{
	return this->mThisId;
}

AActor* SceneEntityBase::gameObject()
{
	if (nullptr != this->mRender)
	{
		return this->mRender->getSelfActor();
	}

	return nullptr;
}

void SceneEntityBase::setGameObject(AActor* rhv)
{
	if (nullptr != this->mRender)
	{
		this->mRender->setSelfActor(rhv);
	}
}

void SceneEntityBase::setPos(FVector pos)
{
	if (!UtilMath::isEqualVec3(this->mPos, pos))
	{
		this->mPos = pos;

		if (nullptr != this->mRender)
		{
			this->mRender->setPos(pos);
		}
	}
}

void SceneEntityBase::setRenderPos(FVector pos)
{
	if (!UtilEngineWrap::isInFakePos(pos) && !UtilMath::isEqualVec3(this->mPos, pos))
	{
		this->mPos = pos;
	}
}

FVector SceneEntityBase::getPos()
{
	return this->mPos;
}

// 获取世界空间中的绝对位置
FVector SceneEntityBase::getFullPos()
{
	return this->mPos;
}

void SceneEntityBase::setRotate(FQuat rotation)
{
	if (!UtilMath::isEqualQuat(this->mRotate, rotation))
	{
		this->mRotate.setRotation(rotation);

		if (nullptr != this->mRender)
		{
			this->mRender->setRotate(rotation);
		}
	}
}

// 这个是单位方向向量
void SceneEntityBase::setRotateNormalDir(FVector normalDir)
{
	FQuat quad = UtilMath::getRotateByOrient(normalDir);
	this->setRotateEulerAngle(UtilMath::Euler(quad));
}

// 这个是欧拉角
void SceneEntityBase::setRotateEulerAngle(FVector rotation)
{
	if (!UtilMath.isEqualVec3(this->mRotate.getRotateEulerAngle(), rotation))
	{
		this->mRotate.setRotateEulerAngle(rotation);

		if (nullptr != this->mRender)
		{
			this->mRender->setRotate(this->mRotate->getRotate());
		}
	}
}

// 获取前向向量
FVector SceneEntityBase::getForward()
{
	FVector forward = this->mRotate->getRotate() * UtilMath::ForwardVec3;

	return forward;
}

FQuat SceneEntityBase::getRotate()
{
	return this->mRotate->getRotate();
}

FVector SceneEntityBase::getRotateEulerAngle()
{
	return this->mRotate->getRotateEulerAngle();
}

FVector SceneEntityBase::getScale()
{
	return this->mScale;
}

void SceneEntityBase::setScale(FVector value)
{
	if (!UtilMath::isEqualVec3(this->mScale, value))
	{
		this->mScale = value;

		if (nullptr != this->mRender)
		{
			this->mRender->setScale(this->mScale);
		}
	}
}

void SceneEntityBase::setSelfName(std::string name)
{
	if (nullptr != this->mRender)
	{
		this->mRender->setSelfName(name);
	}
}

// 自动管理
void SceneEntityBase::autoHandle()
{

}

// 初始化渲染器
void SceneEntityBase::initRender()
{

}

void SceneEntityBase::loadRenderRes()
{

}

EntityRenderBase* SceneEntityBase::getRender()
{
	return this->mRender;
}
	
MY_END_NAMESPACE