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

	ClassAssetInsRes* getAndSyncLoadClass(std::string path, EventDispatchDelegate handle = nullptr);
	ClassAssetInsRes* getAndAsyncLoadClass(std::string path, EventDispatchDelegate handle = nullptr);
};

#endif