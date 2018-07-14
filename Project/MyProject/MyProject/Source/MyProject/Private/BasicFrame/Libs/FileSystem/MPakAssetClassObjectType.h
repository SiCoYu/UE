#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class MPakAssetClassObjectType
{
	eObject,		// 资源类型，加载的时候不需要加 "_C"
	eClass,			// BluePrint 类类型，加载的时候需要加 "_C",但是  Pak 包中加载 BluePrint 类型可以不加 "_C" ，但是原始包必须加 "_C" ，但是没有测试过 Pak 包中资源类型如果加 "_C" 是否可以加载，因此目前可以统一不用加 "_C"
};

MY_END_NAMESPACE