#pragma once

#include <string>
#include <vector>
#include "UiLayer.h"
#include "UiLayerId.h"
#include "UiCanvasId.h"

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
	UiCanvas(UiCanvasId canvasID);
	void setActorName(std::string& rhv);
	std::vector<UiLayer*>& getLayerList();
	void findCanvasActor();
};