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
	std::string mCodePath;      // �߼����� path 
	std::string mWidgetPath;	// �ؼ� path 

	UiCanvasId mCanvasId;       // CanvasId
	UiLayerId mLayerId;			// ���ڵ� Layer
	uint8 mUiSceneType;			// ���������б�

	FormType mFormType;			// UI ����
	UMGOuterType mUMGOuterType;	// UMG Outer

public:
	UiAttrItem();
};

#endif				// __FORMATTRITEM_H