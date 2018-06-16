#pragma once

#include "SceneEntityBase.h"
#include "TickMode.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 玩家管理器
 */
class PlayerMgr : public EntityMgrBase
{
	M_DECLARE_CLASS(BeingEntity, SceneEntityBase)

protected:
	PlayerMain* mHero;

	int mCurNum;
	int mMaxNum;

public:
	PlayerMgr();

protected:
	virtual void _onTickExec(float delta, TickMode tickMode) override;
	void postUpdate();
	PlayerMain* createHero();
	void addHero(PlayerMain* hero);
	void removeHero();

	PlayerMain* getHero();
	virtual void init() override;
	void addPlayer(Player* player);
	void removePlayer(Player* player);
	void createPlayerMain();
};

MY_END_NAMESPACE