#pragma once

#include <string>
#include <vector>
#include "UiLayer.h"

/**
* @brief ����һ�� Canvas
*/
class UiCanvas
{
protected:
	std::string mActorName;				// GameObject ������
	UiCanvasId mCanvasId;				// CanvasID
	std::vector<UiLayer*> mLayerList;   // Canvas �е� Layer

public:
	UiCanvas(UiCanvasId canvasID);
	void setActorName(std::string& rhv);
	std::vector<UiLayer*>& getLayerList();
	void findCanvasActor();
};