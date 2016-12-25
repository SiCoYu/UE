#ifndef __ClassAssetInsMgr_H
#define __ClassAssetInsMgr_H

#include "ResMgrBase.h"

/**
 * @brief 类管理器， Blueprint
 */

class ClassAssetInsRes;

class ClassAssetInsMgr : public ResMgrBase
{
public:
	ClassAssetInsMgr();

public:
	virtual void init() override;
	virtual void dispose() override;

	ClassAssetInsRes* getAndSyncLoadClass(std::string path);
};

#endif