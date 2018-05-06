#ifndef __UiMgr_H
#define __UiMgr_H

#include <map>
#include "MList.h"
#include "UiFormId.h"
#include "EventDispatchDelegate.h"
#include "UiCanvas.h"
#include "UiLayer.h"
#include "UiAttrItem.h"
#include "UiAttrSystem.h"
#include "Form.h"

using namespace NSFormId;
using namespace MyNS;

class UForm;
class UiCanvas;
class UiAttrSystem;
class UiLoadingItem;
class IDispatchObject;
class ClassAssetInsRes;

/**
 * @brief 所有 UI 管理
 * 1. 对于新创建的Form对象，其所属的层是由其ID决定的
 * 2. UI 设计原则，主要界面是资源创建完成才运行逻辑，小的共享界面是逻辑和资源同时运行，因为 MVC 结构实在是要写很多代码，因此主要界面不适用 MVC 结构
 */
class UiMgr
{
protected:
	std::map<UiFormId, UForm*> mId2FormDic;
	std::vector<UiCanvas*> mCanvasList;
	UiAttrSystem* mUiAttrSystem;

	std::map<UiFormId, UiLoadingItem*> mId2CodeLoadingItemDic;         // 记录当前代码正在加载的项
	std::map<UiFormId, UiLoadingItem*> mId2WidgetLoadingItemDic;         // 记录当前窗口控件正在加载的项

	MList<UiFormId> mTmpList;
	//GameObject mSceneUIRootGo;           // 每一个场景都会有一个这样的节点，专门放一些 Scene 中 UI 的一些信息

public:
	UiMgr();

	void init();
	void dispose();

	template <class T>
	T* loadForm(UiFormId formID);

	template <class T>
	T* getForm(UiFormId formID);

	template <class T>
	T* loadAndShow(UiFormId ID);

	void createCanvas();
	void findCanvasGO();

	void showForm(UiFormId ID);
	void showFormInternal(UiFormId ID);
	void hideFormInternal(UiFormId ID);
	void exitForm(UiFormId ID, bool bForce = false);
	void exitFormInternal(UiFormId ID);
	void addForm(UForm* form);

	UiLayer* getLayer(UiCanvasId canvasID, UiLayerId layerID);

	void addFormNoReady(UForm* form);
	bool hasForm(UiFormId ID);

	void loadWidgetRes(UiFormId ID);
	void loadFromFile(std::string reaPath, EventDispatchDelegate onLoadEventHandle);

	void onCodeLoadEventHandle(IDispatchObject* dispObj);
	void onWidgetLoadEventHandle(IDispatchObject* dispObj);
	void onCodeloadedByRes(ClassAssetInsRes* res);
	void onCodeLoadedByForm(UForm* form);
	void onWidgetloadedByRes(ClassAssetInsRes* res);
	void onWidgetAuxUIClassloadedByRes(IDispatchObject* res);

	void onResize(int viewWidth, int viewHeight);

	void exitAllWin();
	void findSceneUIRootGo();
	//void unloadUIBySceneType(UISceneType unloadSceneType, UISceneType loadSceneTpe);
};

#include "UiMgr.inl"			// 模板具体的实现

#endif				// __UIMANAGER_H