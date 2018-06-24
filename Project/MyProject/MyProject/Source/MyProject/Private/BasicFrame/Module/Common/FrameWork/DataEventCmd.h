#pragma once

#include "TypeDef.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IDispatchObject;

/**
* @brief 全局性的事件
*/
class DataEventCmd
{
public:
	DataEventCmd();

	void init();
	void dispose();

public:
	static void onCoreInitedHandle(/*uint eventId, */IDispatchObject* dispObj);
};

MY_END_NAMESPACE