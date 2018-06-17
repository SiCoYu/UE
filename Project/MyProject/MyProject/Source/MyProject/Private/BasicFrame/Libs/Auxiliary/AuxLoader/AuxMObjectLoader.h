#pragma once

#include "AuxMObjectLoaderBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "ResPackType.h"

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 预制
 */
class AuxMObjectLoader : public AuxMObjectLoaderBase
{
	M_DECLARE_CLASS(AuxMObjectLoader, AuxMObjectLoaderBase)

public:
	AuxMObjectLoader();
};

MY_END_NAMESPACE