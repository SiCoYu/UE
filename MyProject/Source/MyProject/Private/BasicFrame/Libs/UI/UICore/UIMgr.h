#ifndef __UIMgr_H
#define __UIMgr_H

#include <map>
#include "MList.h"
#include "UIFormId.h"
#include "EventDispatchDelegate.h"
#include "UICanvas.h"
#include "UILayer.h"
#include "UIAttrItem.h"
#include "UIAttrSystem.h"
#include "Form.h"

using namespace NSFormId;

class UForm;
class UICanvas;
class UIAttrSystem;
class UILoadingItem;
class IDispatchObject;
class UIAssetRes;

/**
 * @brief 所有 UI 管理
 * 1. 对于新创建的Form对象，其所属的层是由其ID决定的
 * 2. UI 设计原则，主要界面是资源创建完成才运行逻辑，小的共享界面是逻辑和资源同时运行，因为 MVC 结构实在是要写很多代码，因此主要界面不适用 MVC 结构
 */
class UIMgr
{
protected:
	std::map<UIFormId, UForm*> mId2FormDic;
	std::vector<UICanvas*> mCanvasList;
	UIAttrSystem* mUiAttrs;

	std::map<UIFormId, UILoadingItem*> mId2CodeLoadingItemDic;         // 记录当前代码正在加载的项
	std::map<UIFormId, UILoadingItem*> mId2WidgetLoadingItemDic;         // 记录当前窗口控件正在加载的项

	MList<UIFormId> mTmpList;
	//GameObject mSceneUIRootGo;           // 每一个场景都会有一个这样的节点，专门放一些 Scene 中 UI 的一些信息

public:
	UIMgr();
	template <class T>
	T* loadForm(UIFormId formID);

	template <class T>
	T* getForm(UIFormId formID);

	template <class T>
	T* loadAndShow(UIFormId ID);

	void createCanvas();
	void findCanvasGO();
	void showForm(UIFormId ID);
	void showFormInternal(UIFormId ID);
	void hideFormInternal(UIFormId ID);
	void exitForm(UIFormId ID, bool bForce = false);
	void exitFormInternal(UIFormId ID);
	void addForm(UForm* form);
	UILayer* getLayer(UICanvasId canvasID, UILayerId layerID);
	void addFormNoReady(UForm* form);
	UForm* getForm(UIFormId ID);
	bool hasForm(UIFormId ID);
	void loadForm(UIFormId ID);
	void loadWidgetRes(UIFormId ID);
	void loadFromFile(std::string reaPath, EventDispatchDelegate onLoadEventHandle);
	void onCodeLoadEventHandle(IDispatchObject* dispObj);
	void onWidgetLoadEventHandle(IDispatchObject* dispObj);
	void onCodeloadedByRes(UIAssetRes* res);
	void onCodeLoadedByForm(UForm* form);
	void onWidgetloadedByRes(UIAssetRes* res);
	void onResize(int viewWidth, int viewHeight);
	void exitAllWin();
	void findSceneUIRootGo();
	//void unloadUIBySceneType(UISceneType unloadSceneType, UISceneType loadSceneTpe);
};

#include "UIMgr.inl"			// 模板具体的实现

#endif				// __UIMANAGER_H