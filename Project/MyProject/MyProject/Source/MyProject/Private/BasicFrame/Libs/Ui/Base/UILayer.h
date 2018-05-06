#pragma once

#include "MyProject.h"

enum UiLayerId
{
	eBtmLayer,                   // ��Ͳ㰡��һ�㲻�Ŷ������Ա���ʱ֮�裬Ŀǰ��ģ���Ľ���
	eFirstLayer,                 // ��һ�㣬����֮��������洰��
	eSecondLayer,                // �ڶ��㣬��Ҫ�ǹ����ԵĽ��棬������Ҫ�رյĽ���
	eThirdLayer,                 // �����㣬����������
	eForthLayer,                 // ���Ĳ㣬��ʾ���ڲ�
	eTopLayer,                   // ��㣬һ�㲻�Ŷ������Ա���ʱ֮��

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
	UiLayerId mLayer;	                        // UiFormId.FirstLayer����
	FSlateRenderTransform* mLayerTrans;                 // ��ǰ���ڲ���ڵ�ת��
	std::map<UiFormId, UForm*> mWinDic;        // ��ǰ�����еĽ���
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