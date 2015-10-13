#pragma once

#include "MyProject.h"

namespace UILayerID
{
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
}

#include <string>
#include <map>

#include "UIFormID.h"

class UFormBase;

class UILayer
{
protected:
	UILayerID m_layer;	                        // UIFormID.FirstLayer����
	FSlateRenderTransform* m_layerTrans;                 // ��ǰ���ڲ���ڵ�ת��
	std::map<UIFormID, UFormBase*> m_winDic;        // ��ǰ�����еĽ���
	std::string m_goName;
public:
	UILayer(UILayerID layerID);
	std::map<UIFormID, UFormBase*>& getWinDic();
	FSlateRenderTransform& getLayerTrans();
	void setLayerTrans(FSlateRenderTransform* rhv);
	void setGoName(std::string& rhv);
	bool hasForm(UFormBase* form);
	void removeForm(UFormBase* form);
	UILayerID getLayerID();
	void addForm(UFormBase* form);
	void onStageReSize();
	void closeAllForm();
	void findLayerGOAndTrans();
};