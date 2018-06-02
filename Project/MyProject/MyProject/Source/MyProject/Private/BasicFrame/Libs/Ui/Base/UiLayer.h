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
	UiLayerId mLayer;	                        // UiFormId.FirstLayer����
	FSlateRenderTransform* mLayerTrans;			// ��ǰ���ڲ���ڵ�ת��
	MDictionary<UiFormId, UForm*> mWinDic;			// ��ǰ�����еĽ���
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