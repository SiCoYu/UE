#pragma once

#include "AuxMObjectLoaderBase.h"
#include "BaseClassDef.h"
#include "ResPackType.h"

namespace MyNS
{
    /**
     * @brief 预制
     */
    class AuxMObjectLoader : public AuxMObjectLoaderBase
    {
		M_DECLARE_SUPER_KW(AuxMObjectLoaderBase)

	public:
		AuxMObjectLoader(std::string path, bool isNeedInsPrefab, bool isInsNeedCoroutine);
	};
}