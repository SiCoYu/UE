#pragma once

#include "BeingEntityRender.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class SceneEntityBase;

/**
 * @brief Player 渲染器
 */
class PlayerRender : public BeingEntityRender
{
	M_DECLARE_CLASS(PlayerRender, BeingEntityRender)
	
	/**
	 * @brief 构造函数
	 */
public:
	PlayerRender(SceneEntityBase* entity_);

protected:
	virtual void _onSelfChanged() override;
	
public:
	/**
	 * @brief 释放基本数据
	 */
	virtual void dispose() override;
	virtual void attachToParentNode(EntityRenderBase* render) override;
	virtual void onTick(float delta, TickMode tickMode) override;
};

MY_END_NAMESPACE