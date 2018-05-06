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
* @brief ����һ�� Canvas
*/
class UiCanvas
{
protected:
	std::string mGoName;				// GameObject ������
	UiCanvasId mCanvasId;				// CanvasID
	std::vector<UiLayer*> mLayerList;   // Canvas �е� Layer

public:
	UiCanvas(UiCanvasId canvasID);
	void setGoName(std::string& rhv);
	std::vector<UiLayer*>& getLayerList();
	void findCanvasGO();
};