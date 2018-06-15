#include "MyProject.h"
#include "PlayerOther.h"
#include "PlayerOtherMovement.h"
#include "PlayerOtherAttack.h"
#include "PlayerOtherRender.h"
#include "PlayerOther.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

PlayerOther::PlayerOther()
{
	this.mMovement = new PlayerOtherMovement(this);
	this.mAttack = new PlayerOtherAttack(this);
}

void PlayerOther::_onPostInit()
{
	base._onPostInit();

	//this.hide();

	this.mMovement.init();
	this.mAttack.init();
}

void PlayerOther::initRender()
{
	if (null == this.mRender)
	{
		this.mRender = new PlayerOtherRender(this);
	}

	this.mRender.init();
}

void PlayerOther::dispose()
{
	if (null != Ctx.msInstance.mPlayerMgr)
	{
		Ctx.msInstance.mPlayerMgr.removePlayer(this);
	}

	base.dispose();
}

void PlayerOther::putInPool()
{
	Ctx.msInstance.mPlayerMgr.removePlayer(this);

	base.putInPool();
}

void PlayerOther::onPutInPool()
{
	if(null != Ctx.msInstance.mBeginnerGuideSys && 
	   Ctx.msInstance.mBeginnerGuideSys.isEnableGuide())
	{
		Ctx.msInstance.mBeginnerGuideSys.beatOneEnemy();
	}

	base.onPutInPool();
}

void PlayerOther::autoHandle()
{
	base.autoHandle();

	Ctx.msInstance.mPlayerMgr.addPlayer(this);
}

void PlayerOther::setPos(UnityEngine.Vector3 pos)
{
	base.setPos(pos);
	// 如果 Hero ，没有移动的时候，才更新，如果 Hero 在移动，直接通过相机移动更新
	//if (!Ctx.msInstance.mPlayerMgr.isHeroMoving())
	{
		if (null != this.mHud)
		{
			this.mHud.onPosChanged();
		}
	}
}

MY_END_NAMESPACE