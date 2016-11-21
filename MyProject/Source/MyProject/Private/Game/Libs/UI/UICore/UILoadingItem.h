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
	UIFormID m_ID;               // Form ID
    std::string m_resPath;            // 拖放的控件 path 

public:
	UILoadingItem();
};

#endif