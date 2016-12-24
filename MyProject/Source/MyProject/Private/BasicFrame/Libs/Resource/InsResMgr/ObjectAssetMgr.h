#ifndef __ObjectAssetMgr_H
#define __ObjectAssetMgr_H

#include "ResMgrBase.h"

/**
 * @brief 资源管理器
 */
class ObjectAssetMgr : public ResMgrBase
{
public:
	ObjectAssetMgr();

	virtual void init() override;
	virtual void dispose() override;
};

#endif