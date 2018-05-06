#pragma once

#include "MyProject.h"

enum UiLayerId
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

#include "UiFormId.h"

using namespace NSFormId;

class UForm;

class UiLayer
{
protected:
	UiLayerId mLayer;	                        // UiFormId.FirstLayer定义
	FSlateRenderTransform* mLayerTrans;                 // 当前所在层根节点转换
	std::map<UiFormId, UForm*> mWinDic;        // 当前层所有的界面
	std::string mGoName;
public:
	UiLayer(UiLayerId layerID);
	std::map<UiFormId, UForm*>& getWinDic();
	FSlateRenderTransform& getLayerTrans();
	void setLayerTrans(FSlateRenderTransform* rhv);
	void setGoName(std::string& rhv);
	bool hasForm(UForm* form);
	void removeForm(UForm* form);
	UiLayerId getLayerID();
	void addForm(UForm* form);
	void onStageReSize();
	void closeAllForm();
	void findLayerGOAndTrans();
};