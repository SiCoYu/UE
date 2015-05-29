#ifndef __FORMATTRITEM_H
#define __FORMATTRITEM_H

#include <string>

enum FormID;

class FormAttrItem
{
protected:
	FormID m_formID;
	std::string m_codePath;               // 逻辑代码 path 
	std::string m_widgetPath;             // 拖放的控件 path 

	UICanvasID m_canvasID;           // 在哪个 Canvas
	UILayerID m_LayerID;             // 所在的 Layer
	uint8 m_uiSceneType;   // 场景类型列表

public:
	FormAttrItem();
};

#endif				// __FORMATTRITEM_H