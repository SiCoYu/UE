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
	std::string mCodePath;      // �߼����� path 
	std::string mWidgetPath;	// �ؼ� path 

	UICanvasId mCanvasId;       // CanvasId
	UILayerId mLayerId;			// ���ڵ� Layer
	uint8 mUiSceneType;			// ���������б�

	FormType mFormType;			// UI ����
	UMGOuterType mUMGOuterType;	// UMG Outer

public:
	UIAttrItem();
};

#endif				// __FORMATTRITEM_H