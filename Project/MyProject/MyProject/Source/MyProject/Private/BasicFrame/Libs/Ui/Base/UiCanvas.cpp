#include "MyProject.h"
#include "UiCanvas.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"

MY_BEGIN_NAMESPACE(MyNS)

UiCanvas::UiCanvas(UiCanvasId canvasId)
{
	this->mCanvasId = canvasId;

	int idx = 0;
	for (idx = 0; idx < (int)UiLayerId::eMaxLayer; ++idx)
	{
		this->mLayerList.add(MY_NEW UiLayer((UiLayerId)idx));
	}

	//if (eCanvas_50 == mCanvasId)
	//{
	//	this->mLayerList[(int)UiLayerId::eBtmLayer].goName = LayerPath.ND_CV_UIBtmLayer_Canvas_50;
	//	this->mLayerList[(int)UiLayerId::eFirstLayer].goName = LayerPath.ND_CV_UIFirstLayer_Canvas_50;
	//	this->mLayerList[(int)UiLayerId::eSecondLayer].goName = LayerPath.ND_CV_UISecondLayer_Canvas_50;
	//	this->mLayerList[(int)UiLayerId::eThirdLayer].goName = LayerPath.ND_CV_UIThirdLayer_Canvas_50;
	//	this->mLayerList[(int)UiLayerId::eForthLayer].goName = LayerPath.ND_CV_UIForthLayer_Canvas_50;
	//	this->mLayerList[(int)UiLayerId::eTopLayer].goName = LayerPath.ND_CV_UITopLayer_Canvas_50;
	//}
	//else if (eCanvas_100 == mCanvasId)
	//{
	//	this->mLayerList[(int)UiLayerId::eBtmLayer].goName = LayerPath.ND_CV_UIBtmLayer_Canvas_100;
	//	this->mLayerList[(int)UiLayerId::eFirstLayer].goName = LayerPath.ND_CV_UIFirstLayer_Canvas_100;
	//	this->mLayerList[(int)UiLayerId::eSecondLayer].goName = LayerPath.ND_CV_UISecondLayer_Canvas_100;
	//	this->mLayerList[(int)UiLayerId::eThirdLayer].goName = LayerPath.ND_CV_UIThirdLayer_Canvas_100;
	//	this->mLayerList[(int)UiLayerId::eForthLayer].goName = LayerPath.ND_CV_UIForthLayer_Canvas_100;
	//	this->mLayerList[(int)UiLayerId::eTopLayer].goName = LayerPath.ND_CV_UITopLayer_Canvas_100;
	//}
}

void UiCanvas::setActorName(std::string& rhv)
{
	this->mActorName = rhv;
}

MList<UiLayer*>& UiCanvas::getLayerList()
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

MY_END_NAMESPACE