#ifndef __UIAssetMgr_H
#define __UIAssetMgr_H

#include "ResMgrBase.h"

/**
 * @brief 主要管理各种 UI 的 Asset 元素
 */
class UIAssetMgr : public ResMgrBase
{
public:
	UIAssetMgr();

	virtual void init() override;
	virtual void dispose() override;
};

#endif