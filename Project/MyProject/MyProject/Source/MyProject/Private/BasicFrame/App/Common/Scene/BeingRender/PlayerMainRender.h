#pragma once

#include "PlayerRender.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityBase;

class PlayerMainRender : public PlayerRender
{
	M_DECLARE_CLASS(PlayerMainRender, PlayerRender)

public:
	PlayerMainRender(SceneEntityBase* entity_);

	virtual void onInit() override;

protected:
	virtual void _onSelfChanged() override;

public:
	virtual void show() override;

public:
	virtual void hide() override;
	// 资源加载
	virtual void load() override;
	virtual void updateLocalTransform() override;
};

MY_END_NAMESPACE