#ifndef __UiAttrItem_H
#define __UiAttrItem_H

#include <string>
#include "UiLayer.h"
#include "UiCanvas.h"
#include "UiFormId.h"
#include "FormType.h"
#include "GObject.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class UiAttrItem : public GObject
{
	M_DECLARE_CLASS(UiAttrItem, GObject)

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

MY_END_NAMESPACE

#endif				// __UiAttrItem_H