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
	std::string mCodePath;               // �߼����� path 
	std::string mWidgetPath;             // �ϷŵĿؼ� path 

	UICanvasId mCanvasId;           // ���ĸ� Canvas
	UILayerId mLayerId;             // ���ڵ� Layer
	uint8 mUiSceneType;   // ���������б�

public:
	UIAttrItem();
};

#endif				// __FORMATTRITEM_H