#pragma once

#include "MyProject.h"

enum UILayerID
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

class UForm;

class UILayer
{
protected:
	UILayerID mLayer;	                        // UIFormId.FirstLayer����
	FSlateRenderTransform* mLayerTrans;                 // ��ǰ���ڲ���ڵ�ת��
	std::map<UIFormId, UForm*> mWinDic;        // ��ǰ�����еĽ���
	std::string mGoName;
public:
	UILayer(UILayerID layerID);
	std::map<UIFormId, UForm*>& getWinDic();
	FSlateRenderTransform& getLayerTrans();
	void setLayerTrans(FSlateRenderTransform* rhv);
	void setGoName(std::string& rhv);
	bool hasForm(UForm* form);
	void removeForm(UForm* form);
	UILayerID getLayerID();
	void addForm(UForm* form);
	void onStageReSize();
	void closeAllForm();
	void findLayerGOAndTrans();
};