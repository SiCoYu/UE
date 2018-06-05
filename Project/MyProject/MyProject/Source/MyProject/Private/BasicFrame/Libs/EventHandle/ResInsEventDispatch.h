#pragma once

#include "EventDispatch.h"
#include "IDispatchObject.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

class AActor;

MY_BEGIN_NAMESPACE(MyNS)

class IDispatchObject;

/**
 * @brief 资源实例化事件分发器
 */

class ResInsEventDispatch : public EventDispatch, public IDispatchObject
{
	M_DECLARE_CLASS(ResInsEventDispatch, EventDispatch)

protected:
	bool mIsValid;
	AActor* mInsActor;

public:
	ResInsEventDispatch();
public:
	void setIsValid(bool value);
	bool getIsValid();
	void setInsActor(AActor* go);
	AActor* getInsActor();
	virtual void dispatchEvent(IDispatchObject* dispatchObject) override;
};

MY_END_NAMESPACE