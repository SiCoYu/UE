#pragma once

#include <string>
#include "MList.h"
#include "UiLayer.h"
#include "UiLayerId.h"
#include "UiCanvasId.h"
#include "GObject.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
* @brief ����һ�� Canvas
*/
class UiCanvas : public GObject
{
	M_DECLARE_CLASS(UiCanvas, GObject)

protected:
	std::string mActorName;				// GameObject ������
	UiCanvasId mCanvasId;				// CanvasID
	MList<UiLayer*> mLayerList;   // Canvas �е� Layer

public:
	UiCanvas(UiCanvasId canvasId);

	void init();
	void dispose();

	void setActorName(std::string& rhv);
	MList<UiLayer*>& getLayerList();
	void findCanvasActor();
};

MY_END_NAMESPACE