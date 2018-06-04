#ifndef __ClassAssetInsMgr_H
#define __ClassAssetInsMgr_H

#include "ResInsMgrBase.h"
#include "ResPackType.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 类管理器， Blueprint
 */

class ClassAssetInsRes;

class ClassAssetInsMgr : public ResInsMgrBase
{
	M_DECLARE_CLASS(ClassAssetInsMgr, ResInsMgrBase)

public:
	ClassAssetInsMgr();
	virtual ~ClassAssetInsMgr();

public:
	virtual void init() override;
	virtual void dispose() override;
	virtual ResPackType getResPackType() override;

	ClassAssetInsRes* getAndSyncLoadRes(std::string path, EventDispatchDelegate handle = nullptr);
	ClassAssetInsRes* getAndAsyncLoadRes(std::string path, EventDispatchDelegate handle = nullptr);
};

MY_END_NAMESPACE

#endif