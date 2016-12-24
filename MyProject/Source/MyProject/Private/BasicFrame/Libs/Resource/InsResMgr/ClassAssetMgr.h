#ifndef __ClassAssetMgr_H
#define __ClassAssetMgr_H

#include "ResMgrBase.h"

/**
 * @brief 类管理器， Blueprint
 */
class ClassAssetMgr : public ResMgrBase
{
public:
	ClassAssetMgr();

	virtual void init() override;
	virtual void dispose() override;
};

#endif