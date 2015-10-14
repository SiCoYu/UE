#ifndef __UIMGR_H
#define __UIMGR_H

#include <map>
#include <vector>
#include "UIFormID.h"

class UFormBase;
class UICanvas;
class UIAttrSystem;
class UILoadingItem;

/**
 * @brief ���� UI ����
 * 1. �����´�����Form�����������Ĳ�������ID������
 * 2. UI ���ԭ����Ҫ��������Դ������ɲ������߼���С�Ĺ���������߼�����Դͬʱ���У���Ϊ MVC �ṹʵ����Ҫд�ܶ���룬�����Ҫ���治���� MVC �ṹ
 */
class UIMgr
{
protected:
	std::map<UIFormID::UIFormID, UFormBase*> m_id2FormDic;
	std::vector<UICanvas*> m_canvasList;
	UIAttrSystem* m_UIAttrs;

	std::map<UIFormID::UIFormID, UILoadingItem*> m_ID2CodeLoadingItemDic;         // ��¼��ǰ�������ڼ��ص���
	std::map<UIFormID::UIFormID, UILoadingItem*> m_ID2WidgetLoadingItemDic;         // ��¼��ǰ���ڿؼ����ڼ��ص���

	std::vector<UIFormID::UIFormID> m_tmpList;
	//GameObject m_sceneUIRootGo;           // ÿһ������������һ�������Ľڵ㣬ר�ŷ�һЩ Scene �� UI ��һЩ��Ϣ


public:
	UIMgr();
	template <class T>
	UFormBase* loadForm(UIFormID formID);

	template <class T>
	T* getForm(UIFormID formID);

	void createCanvas();
	void findCanvasGO();
	void loadAndShow(UIFormID::UIFormID ID);
	void showForm(UIFormID::UIFormID ID);
	void showFormInternal(UIFormID::UIFormID ID);
	void hideFormInternal(UIFormID::UIFormID ID);
	void exitForm(UIFormID::UIFormID ID, bool bForce = false);
	void exitFormInternal(UIFormID::UIFormID ID);
	void addForm(Form form);
	void addFormNoReady(Form form);
	Form getForm(UIFormID::UIFormID ID);
	bool hasForm(UIFormID::UIFormID ID);
	void loadForm(UIFormID::UIFormID ID);
	void loadWidgetRes(UIFormID::UIFormID ID);
	void loadFromFile(string reaPath, Action<IDispatchObject> onLoadEventHandle);
	void onCodeLoadEventHandle(IDispatchObject dispObj);
	void onWidgetLoadEventHandle(IDispatchObject dispObj);
	void onCodeloadedByRes(UIPrefabRes res);
	void onCodeLoadedByForm(Form form);
	void onWidgetloadedByRes(UIPrefabRes res);
	void onResize(int viewWidth, int viewHeight);
	void exitAllWin();
	void findSceneUIRootGo();
	void unloadUIBySceneType(UISceneType unloadSceneType, UISceneType loadSceneTpe);
};

#include "UIMgr.inl"			// ģ������ʵ��

#endif				// __UIMANAGER_H