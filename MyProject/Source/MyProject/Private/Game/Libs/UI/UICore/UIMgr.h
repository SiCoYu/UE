#ifndef __UIMGR_H
#define __UIMGR_H

#include <map>
#include <vector>
#include "UIFormID.h"
#include "EventDispatchDelegate.h"
#include "UICanvas.h"
#include "UILayer.h"

class UFormBase;
class UICanvas;
class UIAttrSystem;
class UILoadingItem;
class IDispatchObject;
class UIAssetRes;

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

	std::map<UIFormID, UILoadingItem*> m_ID2CodeLoadingItemDic;         // ��¼��ǰ�������ڼ��ص���
	std::map<UIFormID, UILoadingItem*> m_ID2WidgetLoadingItemDic;         // ��¼��ǰ���ڿؼ����ڼ��ص���

	std::vector<UIFormID> m_tmpList;
	//GameObject m_sceneUIRootGo;           // ÿһ������������һ�������Ľڵ㣬ר�ŷ�һЩ Scene �� UI ��һЩ��Ϣ


public:
	UIMgr();
	template <class T>
	UFormBase* loadForm(UIFormID formID);

	template <class T>
	T* getForm(UIFormID formID);

	void createCanvas();
	void findCanvasGO();
	void loadAndShow(UIFormID ID);
	void showForm(UIFormID ID);
	void showFormInternal(UIFormID ID);
	void hideFormInternal(UIFormID ID);
	void exitForm(UIFormID ID, bool bForce = false);
	void exitFormInternal(UIFormID ID);
	void addForm(UFormBase* form);
	UILayer* getLayer(UICanvasID canvasID, UILayerID layerID);
	void addFormNoReady(UFormBase* form);
	UFormBase* getForm(UIFormID ID);
	bool hasForm(UIFormID ID);
	void loadForm(UIFormID ID);
	void loadWidgetRes(UIFormID ID);
	void loadFromFile(std::string reaPath, EventDispatchDelegate onLoadEventHandle);
	void onCodeLoadEventHandle(IDispatchObject* dispObj);
	void onWidgetLoadEventHandle(IDispatchObject* dispObj);
	void onCodeloadedByRes(UIAssetRes* res);
	void onCodeLoadedByForm(UFormBase* form);
	void onWidgetloadedByRes(UIAssetRes* res);
	void onResize(int viewWidth, int viewHeight);
	void exitAllWin();
	void findSceneUIRootGo();
	//void unloadUIBySceneType(UISceneType unloadSceneType, UISceneType loadSceneTpe);
};

#include "UIMgr.inl"			// ģ������ʵ��

#endif				// __UIMANAGER_H