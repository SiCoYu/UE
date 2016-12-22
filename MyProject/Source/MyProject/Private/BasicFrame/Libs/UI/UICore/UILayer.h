#pragma once

#include "MyProject.h"

enum UILayerId
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

#include "UIFormId.h"

using namespace NSFormId;

class UForm;

class UILayer
{
protected:
	UILayerId mLayer;	                        // UIFormId.FirstLayer����
	FSlateRenderTransform* mLayerTrans;                 // ��ǰ���ڲ���ڵ�ת��
	std::map<UIFormId, UForm*> mWinDic;        // ��ǰ�����еĽ���
	std::string mGoName;
public:
	UILayer(UILayerId layerID);
	std::map<UIFormId, UForm*>& getWinDic();
	FSlateRenderTransform& getLayerTrans();
	void setLayerTrans(FSlateRenderTransform* rhv);
	void setGoName(std::string& rhv);
	bool hasForm(UForm* form);
	void removeForm(UForm* form);
	UILayerId getLayerID();
	void addForm(UForm* form);
	void onStageReSize();
	void closeAllForm();
	void findLayerGOAndTrans();
};