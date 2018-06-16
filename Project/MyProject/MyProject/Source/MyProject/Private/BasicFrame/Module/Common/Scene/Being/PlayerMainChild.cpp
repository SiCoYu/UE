#include "MyProject.h"
#include "PlayerMainChild.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

PlayerMainChild::PlayerMainChild()
{
	this->mMovement = new PlayerMainChildMovement(this);
	this->mAttack = new PlayerMainChildAttack(this);
}

void PlayerMainChild::initRender()
{
	if (!this->isPrefabPathValid())
	{
		this->setPrefabPath("World/Model/PlayerMain.prefab");
	}

	if (nullptr == this->mRender)
	{
		this->mRender = new PlayerMainChildRender(this);
	}

	this->mRender.init();
}

void PlayerMainChild::_onPreInit()
{
	Super::_onPreInit();

	this->mMovement.init();
	this->mAttack.init();
}

void PlayerMainChild::onTick(float delta, TickMode tickMode)
{
	Super::onTick(delta, tickMode);
}

void PlayerMainChild::postUpdate()
{
	if(this->mRender.isValid())
	{
		this->setRenderPos(this->mRender.getPos());
	}
}

void PlayerMainChild::onDestroy()
{
	Super::onDestroy();
}

void PlayerMainChild::onPutInPool()
{
	Super::onPutInPool();
}

void PlayerMainChild::dispose()
{
	Super::dispose();
}

void PlayerMainChild::putInPool()
{
	Super::putInPool();
}

void PlayerMainChild::setBeingState(BeingState state)
{
	Super::setBeingState(state);

	if(BeingState.eBSBirth == this->mBeingState)
	{
		this->mMoveSpeedFactor = 5;
	}
	else
	{
		this->mMoveSpeedFactor = 1;
	}
}

void PlayerMainChild::setRenderPos(FVector pos)
{
	if (!UtilEngineWrap.isInFakePos(pos) && !UtilMath.isEqualVec3(this->mPos, pos))
	{
		this->mPos = pos;
	}
}

MY_END_NAMESPACE