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
	AuxScenePrefabLoader(
		std::string path, 
		bool isNeedInsPrefab, 
		bool isInsNeedCoroutine
	);
};

MY_END_NAMESPACE