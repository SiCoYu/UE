#pragma once

#include "IDispatchObject.h"

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