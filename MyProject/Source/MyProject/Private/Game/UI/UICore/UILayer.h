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

class UFormBase;

class UILayer
{
protected:
	UILayerID m_layer;	                        // UIFormID.FirstLayer����
	USceneComponent* m_layerTrans;                 // ��ǰ���ڲ���ڵ�ת��
	std::map<UIFormID, UFormBase*> m_winDic;        // ��ǰ�����еĽ���
	std::string m_goName;
public:
	UILayer();
	std::map<UIFormID, UFormBase*>& getWinDic();
	USceneComponent& getLayerTrans();
	USceneComponent& setLayerTrans(USceneComponent* rhv);
	void setGoName(std::string& rhv);
};