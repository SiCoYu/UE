#ifndef __FORMATTRITEM_H
#define __FORMATTRITEM_H

#include <string>
#include "UILayer.h"
#include "UICanvas.h"

enum FormID;

class FormAttrItem
{
protected:
	FormID m_formID;
	std::string m_codePath;               // �߼����� path 
	std::string m_widgetPath;             // �ϷŵĿؼ� path 

	UICanvasID m_canvasID;           // ���ĸ� Canvas
	UILayerID m_LayerID;             // ���ڵ� Layer
	uint8 m_uiSceneType;   // ���������б�

public:
	FormAttrItem();
};

#endif				// __FORMATTRITEM_H