#ifndef __UIATTRITEM_H
#define __UIATTRITEM_H

#include <string>
#include "UILayer.h"
#include "UICanvas.h"

enum FormID;

class UIAttrItem
{
public:
	FormID mFormId;
	std::string mCodePath;               // 逻辑代码 path 
	std::string mWidgetPath;             // 拖放的控件 path 

	UICanvasId mCanvasId;           // 在哪个 Canvas
	UILayerId mLayerId;             // 所在的 Layer
	uint8 mUiSceneType;   // 场景类型列表

public:
	UIAttrItem();
};

#endif				// __FORMATTRITEM_H