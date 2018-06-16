#pragma once

#include "Player.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class PlayerOtherMovement;
class PlayerOtherAttack;
class PlayerOtherRender;

/**
 * @brief 其它玩家
 */
class PlayerOther : public Player
{
	M_DECLARE_CLASS(PlayerOther, Player)

public:
	PlayerOther();

protected:
	virtual void _onPostInit() override;

public:
	virtual void initRender() override;
	virtual void dispose() override;
	virtual void putInPool() override;
	virtual void onPutInPool() override;
	virtual void autoHandle() override;
	virtual void setPos(FVector pos) override;
};

MY_END_NAMESPACE