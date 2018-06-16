#include "MyProject.h"
#include "PlayerMainChild.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

PlayerMainChild::PlayerMainChild()
{
	this.mMovement = new PlayerMainChildMovement(this);
	this.mAttack = new PlayerMainChildAttack(this);
}

void PlayerMainChild::initRender()
{
	if (!this.isPrefabPathValid())
	{
		this.setPrefabPath("World/Model/PlayerMain.prefab");
	}

	if (null == this.mRender)
	{
		this.mRender = new PlayerMainChildRender(this);
	}

	this.mRender.init();
}

void PlayerMainChild::_onPreInit()
{
	base._onPreInit();

	this.mMovement.init();
	this.mAttack.init();
}

void PlayerMainChild::onTick(float delta, TickMode tickMode)
{
	base.onTick(delta, tickMode);
}

void PlayerMainChild::postUpdate()
{
	if(this.mRender.isValid())
	{
		this.setRenderPos(this.mRender.getPos());
	}
}

void PlayerMainChild::onDestroy()
{
	base.onDestroy();
}

void PlayerMainChild::onPutInPool()
{
	base.onPutInPool();
}

void PlayerMainChild::dispose()
{
	base.dispose();
}

void PlayerMainChild::putInPool()
{
	base.putInPool();
}

void PlayerMainChild::setBeingState(BeingState state)
{
	base.setBeingState(state);

	if(BeingState.eBSBirth == this.mBeingState)
	{
		this.mMoveSpeedFactor = 5;
	}
	else
	{
		this.mMoveSpeedFactor = 1;
	}
}

void PlayerMainChild::setRenderPos(UnityEngine.Vector3 pos)
{
	if (!UtilEngineWrap.isInFakePos(pos) && !UtilMath.isEqualVec3(this.mPos, pos))
	{
		this.mPos = pos;
	}
}

MY_END_NAMESPACE