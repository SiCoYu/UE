#include "MyProject.h"
#include "PlayerOtherChild.h"
#include "PlayerOtherChildMovement.h"
#include "PlayerOtherChildAttack.h"
#include "PlayerOtherChildRender.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

PlayerOtherChild::PlayerOtherChild()
{
	this->mMovement = new PlayerOtherChildMovement(this);
	this->mAttack = new PlayerOtherChildAttack(this);
}

void PlayerOtherChild::initRender()
{
	if (!this->isPrefabPathValid())
	{
		this->setPrefabPath("World/Model/PlayerOther.prefab");
	}

	if (nullptr == this->mRender)
	{
		this->mRender = new PlayerOtherChildRender(this);
	}

	this->mRender.init();
}

MY_END_NAMESPACE