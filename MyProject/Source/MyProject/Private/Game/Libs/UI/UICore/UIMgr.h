#ifndef __UIMGR_H
#define __UIMGR_H

#include <map>
#include <vector>
#include "UIFormID.h"

class UFormBase;
class UICanvas;
class UIAttrSystem;

/**
 * @brief ���� UI ����
 * 1. �����´�����Form�����������Ĳ�������ID������
 * 2. UI ���ԭ����Ҫ��������Դ������ɲ������߼���С�Ĺ���������߼�����Դͬʱ���У���Ϊ MVC �ṹʵ����Ҫд�ܶ���룬�����Ҫ���治���� MVC �ṹ
 */
class UIMgr
{
protected:
	std::map<UIFormID, UFormBase*> m_id2FormDic;
	std::vector<UICanvas*> m_canvasList;
	UIAttrSystem* m_UIAttrs;

	std::map<UIFormID, UILoadingItem> m_ID2CodeLoadingItemDic;         // ��¼��ǰ�������ڼ��ص���
	Dictionary<UIFormID, UILoadingItem> m_ID2WidgetLoadingItemDic;         // ��¼��ǰ���ڿؼ����ڼ��ص���

	List<UIFormID> m_tmpList = new List<UIFormID>();
	GameObject m_sceneUIRootGo;           // ÿһ������������һ�������Ľڵ㣬ר�ŷ�һЩ Scene �� UI ��һЩ��Ϣ


public:
	UIMgr();
	template <class T>
	UFormBase* loadForm(UIFormID formID);

	template <class T>
	T* getForm(UIFormID formID);
};

#include "UIMgr.inl"			// ģ������ʵ��

#endif				// __UIMANAGER_H