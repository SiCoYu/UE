#ifndef __ClassAssetInsMgr_H
#define __ClassAssetInsMgr_H

#include "ResInsMgrBase.h"
#include "ResPackType.h"

/**
 * @brief 类管理器， Blueprint
 */

class ClassAssetInsRes;

class ClassAssetInsMgr : public ResInsMgrBase
{
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

#endif