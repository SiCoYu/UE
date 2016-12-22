#pragma once

enum UICanvasId
{
	eCanvas_50,
	eCanvas_100,

	eCanvas_Total,
};

#include <string>
#include <vector>
#include "UILayer.h"

/**
* @brief 描述一个 Canvas
*/
class UICanvas
{
protected:
	std::string mGoName;				// GameObject 的名字
	UICanvasId mCanvasId;				// CanvasID
	std::vector<UILayer*> mLayerList;   // Canvas 中的 Layer

public:
	UICanvas(UICanvasId canvasID);
	void setGoName(std::string& rhv);
	std::vector<UILayer*>& getLayerList();
	void findCanvasGO();
};