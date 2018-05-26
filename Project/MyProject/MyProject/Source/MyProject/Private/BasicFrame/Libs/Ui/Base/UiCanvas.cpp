#include "MyProject.h"
#include "UiCanvas.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"

UiCanvas::UiCanvas(UiCanvasId canvasID)
{
	this->mCanvasId = canvasID;

	int idx = 0;
	for (idx = 0; idx < (int)eMaxLayer; ++idx)
	{
		this->mLayerList.push_back(MY_NEW UiLayer((UiLayerId)idx));
	}

	//if (eCanvas_50 == mCanvasId)
	//{
	//	this->mLayerList[(int)eBtmLayer].goName = LayerPath.ND_CV_UIBtmLayer_Canvas_50;
	//	this->mLayerList[(int)eFirstLayer].goName = LayerPath.ND_CV_UIFirstLayer_Canvas_50;
	//	this->mLayerList[(int)eSecondLayer].goName = LayerPath.ND_CV_UISecondLayer_Canvas_50;
	//	this->mLayerList[(int)eThirdLayer].goName = LayerPath.ND_CV_UIThirdLayer_Canvas_50;
	//	this->mLayerList[(int)eForthLayer].goName = LayerPath.ND_CV_UIForthLayer_Canvas_50;
	//	this->mLayerList[(int)eTopLayer].goName = LayerPath.ND_CV_UITopLayer_Canvas_50;
	//}
	//else if (eCanvas_100 == mCanvasId)
	//{
	//	this->mLayerList[(int)eBtmLayer].goName = LayerPath.ND_CV_UIBtmLayer_Canvas_100;
	//	this->mLayerList[(int)eFirstLayer].goName = LayerPath.ND_CV_UIFirstLayer_Canvas_100;
	//	this->mLayerList[(int)eSecondLayer].goName = LayerPath.ND_CV_UISecondLayer_Canvas_100;
	//	this->mLayerList[(int)eThirdLayer].goName = LayerPath.ND_CV_UIThirdLayer_Canvas_100;
	//	this->mLayerList[(int)eForthLayer].goName = LayerPath.ND_CV_UIForthLayer_Canvas_100;
	//	this->mLayerList[(int)eTopLayer].goName = LayerPath.ND_CV_UITopLayer_Canvas_100;
	//}
}

void UiCanvas::setActorName(std::string& rhv)
{
	this->mActorName = rhv;
}

std::vector<UiLayer*>& UiCanvas::getLayerList()
{
	return this->mLayerList;
}

void UiCanvas::findCanvasActor()
{
	//int idx = 0;
	//for (idx = 0; idx < (int)eMaxLayer; ++idx)
	//{
	//	mLayerList[idx].findLayerGOAndTrans();
	//}
}