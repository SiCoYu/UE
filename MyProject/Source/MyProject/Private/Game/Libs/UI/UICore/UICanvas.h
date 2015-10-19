#pragma once

enum UICanvasID
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
	std::string m_goName;				// GameObject 的名字
	UICanvasID m_canvasID;				// CanvasID
	std::vector<UILayer*> m_layerList;   // Canvas 中的 Layer

public:
	UICanvas(UICanvasID canvasID);
	void setGoName(std::string& rhv);
	std::vector<UILayer*>& getLayerList();
	void findCanvasGO();
};