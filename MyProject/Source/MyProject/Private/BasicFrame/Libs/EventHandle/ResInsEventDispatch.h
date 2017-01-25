#pragma once

#include "EventDispatch.h"
#include "IDispatchObject.h"
#include "BaseClassDef.h"

class UObject;
class IDispatchObject;

/**
 * @brief 资源实例化事件分发器
 */

class ResInsEventDispatch : public EventDispatch, public IDispatchObject
{
	M_DECLARE_SUPER_KW(EventDispatch)

protected:
	bool mIsValid;
    UObject* mInsGO;

public:
	ResInsEventDispatch();
public:
	void setIsValid(bool value);
	bool getIsValid();
	void setInsGO(UObject* go);
	UObject* getInsGO();
	virtual void dispatchEvent(IDispatchObject* dispatchObject) override;
};