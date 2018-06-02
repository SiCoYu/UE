#pragma once

#include <string>
#include <vector>
#include "UiLayer.h"
#include "UiLayerId.h"
#include "UiCanvasId.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
* @brief 描述一个 Canvas
*/
class UiCanvas
{
protected:
	std::string mActorName;				// GameObject 的名字
	UiCanvasId mCanvasId;				// CanvasID
	std::vector<UiLayer*> mLayerList;   // Canvas 中的 Layer

public:
	UiCanvas(UiCanvasId canvasId);
	void setActorName(std::string& rhv);
	std::vector<UiLayer*>& getLayerList();
	void findCanvasActor();
};

MY_END_NAMESPACE