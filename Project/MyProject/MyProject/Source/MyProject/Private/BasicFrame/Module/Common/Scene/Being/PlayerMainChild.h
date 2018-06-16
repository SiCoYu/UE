#pragma once

#include "SceneEntityBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

public class PlayerMainChild : PlayerChild
{
public:
	PlayerMainChild();
	virtual void initRender() override;

protected:
	virtual void _onPreInit() override;

public:
	virtual void onTick(float delta, TickMode tickMode) override;
	void postUpdate();

	virtual void onDestroy() override;
	virtual void onPutInPool() override;
	virtual void dispose() override;
	virtual void putInPool() override;
	virtual void setBeingState(BeingState state) override;
	virtual void setRenderPos(UnityEngine.Vector3 pos) override;
};

MY_END_NAMESPACE