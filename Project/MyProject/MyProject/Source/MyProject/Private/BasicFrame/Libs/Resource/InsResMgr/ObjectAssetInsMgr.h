#ifndef __ObjectAssetInsMgr_H
#define __ObjectAssetInsMgr_H

#include "ResInsMgrBase.h"
#include "EventDispatchDelegate.h"
#include "BaseClassDef.h"

class ObjectAssetInsRes;

/**
 * @brief 资源管理器
 */
class ObjectAssetInsMgr : public ResInsMgrBase
{
	M_DECLARE_SUPER_KW(ResInsMgrBase)

public:
	ObjectAssetInsMgr();
	virtual ~ObjectAssetInsMgr();

	virtual void init() override;
	virtual void dispose() override;

	ObjectAssetInsRes* getAndSyncLoadRes(std::string path, EventDispatchDelegate evtHandle);
	ObjectAssetInsRes* getAndAsyncLoadRes(std::string path, EventDispatchDelegate evtHandle);
};

#endif