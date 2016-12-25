#ifndef __ObjectAssetInsMgr_H
#define __ObjectAssetInsMgr_H

#include "ResMgrBase.h"

/**
 * @brief 资源管理器
 */
class ObjectAssetInsMgr : public ResMgrBase
{
public:
	ObjectAssetInsMgr();

	virtual void init() override;
	virtual void dispose() override;
};

#endif