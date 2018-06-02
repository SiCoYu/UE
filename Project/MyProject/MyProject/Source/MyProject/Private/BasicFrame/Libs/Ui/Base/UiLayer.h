#pragma once

#include "MyProject.h"

#include <string>
#include <map>

#include "UiFormId.h"
#include "GObject.h"
#include "UiLayerId.h"
#include "PlatformDefine.h"

using namespace NSFormId;

class UForm;

MY_BEGIN_NAMESPACE(MyNS)

class UiLayer : public GObject
{
protected:
	UiLayerId mLayer;	                        // UiFormId.FirstLayer����
	FSlateRenderTransform* mLayerTrans;                 // ��ǰ���ڲ���ڵ�ת��
	std::map<UiFormId, UForm*> mWinDic;        // ��ǰ�����еĽ���
	std::string mActorName;

public:
	UiLayer(UiLayerId layerId);
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

MY_END_NAMESPACE