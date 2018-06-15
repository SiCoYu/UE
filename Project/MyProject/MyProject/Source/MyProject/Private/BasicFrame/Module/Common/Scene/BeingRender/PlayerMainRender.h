#pragma once

#include "BeingEntityRender.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

public class PlayerMainRender : PlayerRender
{
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