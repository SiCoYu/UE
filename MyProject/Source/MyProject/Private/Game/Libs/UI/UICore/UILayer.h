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

#include "UIFormID.h"

class UForm;

class UILayer
{
protected:
	UILayerID m_layer;	                        // UIFormID.FirstLayer����
	FSlateRenderTransform* m_layerTrans;                 // ��ǰ���ڲ���ڵ�ת��
	std::map<UIFormID, UForm*> m_winDic;        // ��ǰ�����еĽ���
	std::string m_goName;
public:
	UILayer(UILayerID layerID);
	std::map<UIFormID, UForm*>& getWinDic();
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