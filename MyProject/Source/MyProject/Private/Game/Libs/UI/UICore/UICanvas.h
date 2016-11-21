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
* @brief ����һ�� Canvas
*/
class UICanvas
{
protected:
	std::string m_goName;				// GameObject ������
	UICanvasID m_canvasID;				// CanvasID
	std::vector<UILayer*> m_layerList;   // Canvas �е� Layer

public:
	UICanvas(UICanvasID canvasID);
	void setGoName(std::string& rhv);
	std::vector<UILayer*>& getLayerList();
	void findCanvasGO();
};