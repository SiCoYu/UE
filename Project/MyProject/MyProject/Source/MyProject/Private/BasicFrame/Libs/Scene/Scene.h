#pragma once

#include "IDispatchObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class Scene : public IDispatchObject
{
protected:
	bool mIsSceneLoaded;          // 场景是否加载完成

public:
	Scene();

public:
	void init();
	void dispose();
	bool isSceneLoaded();
};

MY_END_NAMESPACE