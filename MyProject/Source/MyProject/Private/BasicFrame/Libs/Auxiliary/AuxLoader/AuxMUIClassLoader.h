#pragma once

#include "AuxMObjectLoaderBase.h"
#include "BaseClassDef.h"

namespace MyNS
{
    /**
     * @brief 预制
     */
    class AuxMUIClassLoader : public AuxMObjectLoaderBase
    {
		M_DECLARE_SUPER_KW(AuxMObjectLoaderBase)

	public:
		AuxMUIClassLoader(std::string path = "", bool isNeedInsPrefab = true, bool isInsNeedCoroutine = true);
	};
}