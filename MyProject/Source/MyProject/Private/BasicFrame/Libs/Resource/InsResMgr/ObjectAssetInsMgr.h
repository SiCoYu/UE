#ifndef __ObjectAssetInsMgr_H
#define __ObjectAssetInsMgr_H

#include "InsResMgrBase.h"
#include "BaseClassDef.h"

class ObjectAssetResItem;

/**
 * @brief 资源管理器
 */
class ObjectAssetInsMgr : public InsResMgrBase
{
	M_DECLARE_SUPER_KW(InsResMgrBase)

public:
	ObjectAssetInsMgr();

	virtual void init() override;
	virtual void dispose() override;

	ObjectAssetResItem* getAndSyncLoadRes(std::string path, EventDispatchDelegate evtHandle);
};

#endif