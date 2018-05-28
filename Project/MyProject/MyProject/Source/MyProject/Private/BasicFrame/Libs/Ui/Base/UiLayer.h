#pragma once

#include "MyProject.h"

#include <string>
#include <map>

#include "UiFormId.h"
#include "GObject.h"

using namespace NSFormId;

class UForm;

class UiLayer : public GObject
{
protected:
	UiLayerId mLayer;	                        // UiFormId.FirstLayer定义
	FSlateRenderTransform* mLayerTrans;                 // 当前所在层根节点转换
	std::map<UiFormId, UForm*> mWinDic;        // 当前层所有的界面
	std::string mActorName;
public:
	UiLayer(UiLayerId layerID);
	std::map<UiFormId, UForm*>& getWinDic();
	FSlateRenderTransform& getLayerTrans();
	void setLayerTrans(FSlateRenderTransform* rhv);
	void setActorName(std::string& rhv);
	bool hasForm(UForm* form);
	void removeForm(UForm* form);
	UiLayerId getLayerID();
	void addForm(UForm* form);
	void onStageReSize();
	void closeAllForm();
	void findLayerGOAndTrans();
};