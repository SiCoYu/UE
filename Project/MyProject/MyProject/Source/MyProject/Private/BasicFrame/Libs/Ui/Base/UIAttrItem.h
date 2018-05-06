#ifndef __UiAttrItem_H
#define __UiAttrItem_H

#include <string>
#include "UiLayer.h"
#include "UiCanvas.h"
#include "UiFormId.h"
#include "FormType.h"

using namespace NSFormType;
using namespace NSFormId;

class UiAttrItem
{
public:
	UiFormId mFormId;
	std::string mCodePath;      // 逻辑代码 path 
	std::string mWidgetPath;	// 控件 path 

	UiCanvasId mCanvasId;       // CanvasId
	UiLayerId mLayerId;			// 所在的 Layer
	uint8 mUiSceneType;			// 场景类型列表

	FormType mFormType;			// UI 类型
	UMGOuterType mUMGOuterType;	// UMG Outer

public:
	UiAttrItem();
};

#endif				// __FORMATTRITEM_H