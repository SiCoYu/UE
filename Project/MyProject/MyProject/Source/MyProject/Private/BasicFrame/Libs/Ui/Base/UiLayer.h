#pragma once

#include "MyProject.h"

#include <string>
#include "MDictionary.h"

#include "UiFormId.h"
#include "GObject.h"
#include "UiLayerId.h"
#include "PlatformDefine.h"

class UForm;

MY_BEGIN_NAMESPACE(MyNS)

class UiLayer : public GObject
{
protected:
	UiLayerId mLayer;	                        // UiFormId.FirstLayer定义
	FSlateRenderTransform* mLayerTrans;			// 当前所在层根节点转换
	MDictionary<UiFormId, UForm*> mWinDic;			// 当前层所有的界面
	std::string mActorName;

public:
	UiLayer(UiLayerId layerId);
	MDictionary<UiFormId, UForm*>& getWinDic();
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

MY_END_NAMESPACE