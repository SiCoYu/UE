#ifndef __ObjectAssetInsMgr_H
#define __ObjectAssetInsMgr_H

#include "ResInsMgrBase.h"
#include "EventDispatchDelegate.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class ObjectAssetInsRes;

/**
 * @brief 资源管理器
 */
class ObjectAssetInsMgr : public ResInsMgrBase
{
	M_DECLARE_CLASS(ObjectAssetInsMgr, ResInsMgrBase)

public:
	ObjectAssetInsMgr();
	virtual ~ObjectAssetInsMgr();

	virtual void init() override;
	virtual void dispose() override;

	ObjectAssetInsRes* getAndSyncLoadRes(std::string path, EventDispatchDelegate evtHandle);
	ObjectAssetInsRes* getAndAsyncLoadRes(std::string path, EventDispatchDelegate evtHandle);
};

MY_END_NAMESPACE

#endif