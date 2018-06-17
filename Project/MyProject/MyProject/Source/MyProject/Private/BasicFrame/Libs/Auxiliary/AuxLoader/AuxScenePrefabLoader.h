#pragma once

#include <string>
#include "AuxMObjectLoader.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "ResPackType.h"

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 预制
 */
class AuxScenePrefabLoader : public AuxMObjectLoader
{
	M_DECLARE_CLASS(AuxScenePrefabLoader, AuxMObjectLoader)

public:
	AuxScenePrefabLoader();
};

MY_END_NAMESPACE