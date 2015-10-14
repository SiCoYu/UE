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
 * @brief 所有 UI 管理
 * 1. 对于新创建的Form对象，其所属的层是由其ID决定的
 * 2. UI 设计原则，主要界面是资源创建完成才运行逻辑，小的共享界面是逻辑和资源同时运行，因为 MVC 结构实在是要写很多代码，因此主要界面不适用 MVC 结构
 */
class UIMgr
{
protected:
	std::map<UIFormID::UIFormID, UFormBase*> m_id2FormDic;
	std::vector<UICanvas*> m_canvasList;
	UIAttrSystem* m_UIAttrs;

	std::map<UIFormID::UIFormID, UILoadingItem*> m_ID2CodeLoadingItemDic;         // 记录当前代码正在加载的项
	std::map<UIFormID::UIFormID, UILoadingItem*> m_ID2WidgetLoadingItemDic;         // 记录当前窗口控件正在加载的项

	std::vector<UIFormID::UIFormID> m_tmpList;
	//GameObject m_sceneUIRootGo;           // 每一个场景都会有一个这样的节点，专门放一些 Scene 中 UI 的一些信息


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

#include "UIMgr.inl"			// 模板具体的实现

#endif				// __UIMANAGER_H