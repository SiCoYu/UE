#pragma once

enum UiCanvasId
{
	eCanvas_50,
	eCanvas_100,

	eCanvas_Total,
};

#include <string>
#include <vector>
#include "UiLayer.h"

/**
* @brief 描述一个 Canvas
*/
class UiCanvas
{
protected:
	std::string mGoName;				// GameObject 的名字
	UiCanvasId mCanvasId;				// CanvasID
	std::vector<UiLayer*> mLayerList;   // Canvas 中的 Layer

public:
	UiCanvas(UiCanvasId canvasID);
	void setGoName(std::string& rhv);
	std::vector<UiLayer*>& getLayerList();
	void findCanvasGO();
};