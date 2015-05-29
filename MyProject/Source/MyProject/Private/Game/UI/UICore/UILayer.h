#pragma once

#include "MyProject.h"

enum UILayerID
{
	eBtmLayer,                   // 最低层啊，一般不放东西，以备不时之需，目前放模糊的界面
	eFirstLayer,                 // 第一层，聊天之类的主界面窗口
	eSecondLayer,                // 第二层，主要是功能性的界面，弹出需要关闭的界面
	eThirdLayer,                 // 第三层，新手引导层
	eForthLayer,                 // 第四层，提示窗口层
	eTopLayer,                   // 最顶层，一般不放东西，以备不时之需

	eMaxLayer
};

#include <string>
#include <map>

#include "UIFormID.h"

class UFormBase;

class UILayer
{
protected:
	UILayerID m_layer;	                        // UIFormID.FirstLayer定义
	USceneComponent* m_layerTrans;                 // 当前所在层根节点转换
	std::map<UIFormID, UFormBase*> m_winDic;        // 当前层所有的界面
	std::string m_goName;
public:
	UILayer();
	std::map<UIFormID, UFormBase*>& getWinDic();
	USceneComponent& getLayerTrans();
	USceneComponent& setLayerTrans(USceneComponent* rhv);
	void setGoName(std::string& rhv);
};