#pragma once

#include <string>
#include <vector>
#include "UiLayer.h"
#include "UiLayerId.h"
#include "UiCanvasId.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

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
	UiCanvas(UiCanvasId canvasId);
	void setActorName(std::string& rhv);
	std::vector<UiLayer*>& getLayerList();
	void findCanvasActor();
};

MY_END_NAMESPACE