#pragma once

#include "SceneEntityBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 主角
 */
public class PlayerMain : Player
{
public:
	PlayerMain();
	
	virtual void initRender() override;

protected:
	virtual void _onPreInit() override;
	virtual void _onPostInit();

public:
	virtual void dispose() override;
	virtual void putInPool() override;
	virtual void onPutInPool() override;
	virtual void autoHandle() override;

protected:
	virtual void _onExecTick(float delta, TickMode tickMode) override;
	virtual void _onPreTick(float delta, TickMode tickMode) override;
	virtual void _onPostTick(float delta, TickMode tickMode) override;
};

MY_END_NAMESPACE