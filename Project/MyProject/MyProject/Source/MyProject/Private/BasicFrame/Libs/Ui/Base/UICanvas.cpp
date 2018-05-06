#include "MyProject.h"
#include "UICanvas.h"

UICanvas::UICanvas(UICanvasId canvasID)
{
	mCanvasId = canvasID;

	int idx = 0;
	for (idx = 0; idx < (int)eMaxLayer; ++idx)
	{
		mLayerList.push_back(new UILayer((UILayerId)idx));
	}

	//if (eCanvas_50 == mCanvasId)
	//{
	//	mLayerList[(int)eBtmLayer].goName = NotDestroyPath.ND_CV_UIBtmLayer_Canvas_50;
	//	mLayerList[(int)eFirstLayer].goName = NotDestroyPath.ND_CV_UIFirstLayer_Canvas_50;
	//	mLayerList[(int)eSecondLayer].goName = NotDestroyPath.ND_CV_UISecondLayer_Canvas_50;
	//	mLayerList[(int)eThirdLayer].goName = NotDestroyPath.ND_CV_UIThirdLayer_Canvas_50;
	//	mLayerList[(int)eForthLayer].goName = NotDestroyPath.ND_CV_UIForthLayer_Canvas_50;
	//	mLayerList[(int)eTopLayer].goName = NotDestroyPath.ND_CV_UITopLayer_Canvas_50;
	//}
	//else if (eCanvas_100 == mCanvasId)
	//{
	//	mLayerList[(int)eBtmLayer].goName = NotDestroyPath.ND_CV_UIBtmLayer_Canvas_100;
	//	mLayerList[(int)eFirstLayer].goName = NotDestroyPath.ND_CV_UIFirstLayer_Canvas_100;
	//	mLayerList[(int)eSecondLayer].goName = NotDestroyPath.ND_CV_UISecondLayer_Canvas_100;
	//	mLayerList[(int)eThirdLayer].goName = NotDestroyPath.ND_CV_UIThirdLayer_Canvas_100;
	//	mLayerList[(int)eForthLayer].goName = NotDestroyPath.ND_CV_UIForthLayer_Canvas_100;
	//	mLayerList[(int)eTopLayer].goName = NotDestroyPath.ND_CV_UITopLayer_Canvas_100;
	//}
}

void UICanvas::setGoName(std::string& rhv)
{
	mGoName = rhv;
}

std::vector<UILayer*>& UICanvas::getLayerList()
{
	return mLayerList;
}

void UICanvas::findCanvasGO()
{
	//int idx = 0;
	//for (idx = 0; idx < (int)eMaxLayer; ++idx)
	//{
	//	mLayerList[idx].findLayerGOAndTrans();
	//}
}