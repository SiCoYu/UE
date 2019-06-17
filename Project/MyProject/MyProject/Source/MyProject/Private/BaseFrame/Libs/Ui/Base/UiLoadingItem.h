#ifndef __UiLoadingItem_H
#define __UiLoadingItem_H

#include <string>
#include "UiFormId.h"
#include "GObject.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 正在加载的 Item ，主要是防止重复加载
 */
class UiLoadingItem : public GObject
{
	M_DECLARE_CLASS(UiLoadingItem, GObject)

public:
	UiFormId mId;               // Form formId
    std::string mResPath;            // 拖放的控件 path 

public:
	UiLoadingItem();
};

MY_END_NAMESPACE

#endif