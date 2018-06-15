#pragma once

#include "BeingEntityRender.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

public class PlayerOtherRender : PlayerRender
{
public:
	PlayerOtherRender(SceneEntityBase* entity_);

	virtual void onInit() override;
	// 资源加载
	virtual void load() override;
	virtual void updateLocalTransform() override;
};

MY_END_NAMESPACE