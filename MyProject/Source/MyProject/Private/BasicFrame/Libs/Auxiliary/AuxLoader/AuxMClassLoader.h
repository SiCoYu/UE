#pragma once

#include "AuxMObjectLoaderBase.h"
#include "BaseClassDef.h"
#include "ResPackType.h"

namespace MyNS
{
    /**
     * @brief 预制
     */
    class AuxMClassLoader : public AuxMObjectLoaderBase
    {
		M_DECLARE_SUPER_KW(AuxMObjectLoaderBase)

	public:
		AuxMClassLoader(std::string path = "", bool isNeedInsPrefab = true, bool isInsNeedCoroutine = true);
	};
}