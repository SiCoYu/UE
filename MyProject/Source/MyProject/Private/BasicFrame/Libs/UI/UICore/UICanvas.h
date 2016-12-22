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
* @brief ����һ�� Canvas
*/
class UICanvas
{
protected:
	std::string mGoName;				// GameObject ������
	UICanvasId mCanvasId;				// CanvasID
	std::vector<UILayer*> mLayerList;   // Canvas �е� Layer

public:
	UICanvas(UICanvasId canvasID);
	void setGoName(std::string& rhv);
	std::vector<UILayer*>& getLayerList();
	void findCanvasGO();
};