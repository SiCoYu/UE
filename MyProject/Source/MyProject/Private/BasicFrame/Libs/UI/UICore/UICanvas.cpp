#include "MyProject.h"
#include "UICanvas.h"

UICanvas::UICanvas(UICanvasID canvasID)
{
	m_canvasID = canvasID;

	int idx = 0;
	for (idx = 0; idx < (int)eMaxLayer; ++idx)
	{
		m_layerList.push_back(new UILayer((UILayerID)idx));
	}

	//if (eCanvas_50 == m_canvasID)
	//{
	//	m_layerList[(int)eBtmLayer].goName = NotDestroyPath.ND_CV_UIBtmLayer_Canvas_50;
	//	m_layerList[(int)eFirstLayer].goName = NotDestroyPath.ND_CV_UIFirstLayer_Canvas_50;
	//	m_layerList[(int)eSecondLayer].goName = NotDestroyPath.ND_CV_UISecondLayer_Canvas_50;
	//	m_layerList[(int)eThirdLayer].goName = NotDestroyPath.ND_CV_UIThirdLayer_Canvas_50;
	//	m_layerList[(int)eForthLayer].goName = NotDestroyPath.ND_CV_UIForthLayer_Canvas_50;
	//	m_layerList[(int)eTopLayer].goName = NotDestroyPath.ND_CV_UITopLayer_Canvas_50;
	//}
	//else if (eCanvas_100 == m_canvasID)
	//{
	//	m_layerList[(int)eBtmLayer].goName = NotDestroyPath.ND_CV_UIBtmLayer_Canvas_100;
	//	m_layerList[(int)eFirstLayer].goName = NotDestroyPath.ND_CV_UIFirstLayer_Canvas_100;
	//	m_layerList[(int)eSecondLayer].goName = NotDestroyPath.ND_CV_UISecondLayer_Canvas_100;
	//	m_layerList[(int)eThirdLayer].goName = NotDestroyPath.ND_CV_UIThirdLayer_Canvas_100;
	//	m_layerList[(int)eForthLayer].goName = NotDestroyPath.ND_CV_UIForthLayer_Canvas_100;
	//	m_layerList[(int)eTopLayer].goName = NotDestroyPath.ND_CV_UITopLayer_Canvas_100;
	//}
}

void UICanvas::setGoName(std::string& rhv)
{
	m_goName = rhv;
}

std::vector<UILayer*>& UICanvas::getLayerList()
{
	return m_layerList;
}

void UICanvas::findCanvasGO()
{
	//int idx = 0;
	//for (idx = 0; idx < (int)eMaxLayer; ++idx)
	//{
	//	m_layerList[idx].findLayerGOAndTrans();
	//}
}