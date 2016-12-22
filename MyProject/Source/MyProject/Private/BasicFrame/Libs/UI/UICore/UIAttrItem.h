#ifndef __UIATTRITEM_H
#define __UIATTRITEM_H

#include <string>
#include "UILayer.h"
#include "UICanvas.h"
#include "UIFormId.h"

class UIAttrItem
{
public:
	UIFormId mFormId;
	std::string mCodePath;      // �߼����� path 
	std::string mWidgetPath;	// �ؼ� path 

	UICanvasId mCanvasId;       // ���ĸ� Canvas
	UILayerId mLayerId;			// ���ڵ� Layer
	uint8 mUiSceneType;			// ���������б�

public:
	UIAttrItem();
};

#endif				// __FORMATTRITEM_H