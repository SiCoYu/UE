#pragma once

#include "GObject.h"
#include "IDispatchObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 移动类型
 */
class SceneEntityMovement : GObject, IDispatchObject
{
protected:
	SceneEntityBase* mEntity;          // 关联的实体

public:
	SceneEntityMovement(SceneEntityBase entity);
	virtual void init();
	virtual void dispose();
	virtual void onTick(float delta, TickMode tickMode);
};

MY_END_NAMESPACE