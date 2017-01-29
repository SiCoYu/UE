#ifndef __ClassAssetInsMgr_H
#define __ClassAssetInsMgr_H

#include "InsResMgrBase.h"

/**
 * @brief 类管理器， Blueprint
 */

class ClassAssetInsRes;

class ClassAssetInsMgr : public InsResMgrBase
{
public:
	ClassAssetInsMgr();

public:
	virtual void init() override;
	virtual void dispose() override;

	ClassAssetInsRes* getAndSyncLoadRes(std::string path, EventDispatchDelegate handle = nullptr);
	ClassAssetInsRes* getAndAsyncLoadRes(std::string path, EventDispatchDelegate handle = nullptr);
};

#endif