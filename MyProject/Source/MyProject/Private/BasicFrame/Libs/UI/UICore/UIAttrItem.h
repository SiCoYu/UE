#ifndef __UIATTRITEM_H
#define __UIATTRITEM_H

#include <string>
#include "UILayer.h"
#include "UICanvas.h"
#include "UIFormId.h"
#include "FormType.h"

using namespace NSFormType;
using namespace NSFormId;

class UIAttrItem
{
public:
	UIFormId mFormId;
	std::string mCodePath;      // 逻辑代码 path 
	std::string mWidgetPath;	// 控件 path 

	UICanvasId mCanvasId;       // CanvasId
	UILayerId mLayerId;			// 所在的 Layer
	uint8 mUiSceneType;			// 场景类型列表

	FormType mFormType;			// UI 类型
	UMGOuterType mUMGOuterType;	// UMG Outer

public:
	UIAttrItem();
};

#endif				// __FORMATTRITEM_H