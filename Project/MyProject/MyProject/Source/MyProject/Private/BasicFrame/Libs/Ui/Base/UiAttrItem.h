#ifndef __UiAttrItem_H
#define __UiAttrItem_H

#include <string>
#include "UiLayer.h"
#include "UiCanvas.h"
#include "UiFormId.h"
#include "FormType.h"
#include "GObject.h"

using namespace NSFormType;
using namespace NSFormId;

class UiAttrItem : public GObject
{
public:
	UiFormId mFormId;
	std::string mCodePath;      // �߼����� path 
	std::string mWidgetPath;	// �ؼ� path 

	UiCanvasId mCanvasId;       // CanvasId
	UiLayerId mLayerId;			// ���ڵ� Layer

	FormType mFormType;			// UI ����
	UMGOuterType mUMGOuterType;	// UMG Outer

public:
	UiAttrItem();
};

#endif				// __FORMATTRITEM_H