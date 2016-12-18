#ifndef __UILoadingItem_H
#define __UILoadingItem_H

#include <string>
#include "UIFormID.h"

/**
 * @brief 正在加载的 Item ，主要是防止重复加载
 */
class UILoadingItem
{
public:
	UIFormID mId;               // Form ID
    std::string mResPath;            // 拖放的控件 path 

public:
	UILoadingItem();
};

#endif