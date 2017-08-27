#include "MyProject.h"
#include "UIMgr.h"
#include "Form.h"
#include "UIAttrSystem.h"
#include "NotDestroyPath.h"
#include "EngineApi.h"
#include "UtilContainers.h"
#include "UILoadingItem.h"
#include "Common.h"
#include "LoadParam.h"
#include "UIAttrItem.h"
#include "RefCountResLoadResultNotify.h"
#include "ResLoadState.h"
#include "Templates/SubclassOf.h"	// TSubclassOf
#include "UMGWidget.h"				// UUMGWidget
#include "UtilStr.h"				// UtilStr
#include "UMGWidget.h"				// UUMGWidget
#include "ClassAssetInsRes.h"
#include "AuxMUIClassLoader.h"
#include "SafePointer.h"

using namespace MyNS;

UIMgr::UIMgr()
{
	this->mUiAttrSystem = new UIAttrSystem();
	this->createCanvas();
}

void UIMgr::init()
{
	if (nullptr != this->mUiAttrSystem)
	{
		this->mUiAttrSystem->init();
	}
}

void UIMgr::dispose()
{
	if (nullptr != this->mUiAttrSystem)
	{
		this->mUiAttrSystem->dispose();
		this->mUiAttrSystem = nullptr;
	}
}

void UIMgr::createCanvas()
{
	int idx = 0;
	for (idx = 0; idx < (int)eCanvas_Total; ++idx)
	{
		this->mCanvasList.push_back(new UICanvas((UICanvasId)idx));
	}

	this->mCanvasList[(int)eCanvas_50]->setGoName(NotDestroyPath::ND_CV_UICanvas_50);
	this->mCanvasList[(int)eCanvas_100]->setGoName(NotDestroyPath::ND_CV_UICanvas_100);
}

// 关联每一层的对象
void UIMgr::findCanvasGO()
{
	int idx = 0;
	for (idx = 0; idx < (int)eCanvas_Total; ++idx)
	{
		this->mCanvasList[idx]->findCanvasGO();
	}
}

// 显示一个 UI
void UIMgr::showForm(UIFormId formId)
{
	if (hasForm(formId))
	{
		this->showFormInternal(formId);
	}
}

void UIMgr::showFormInternal(UIFormId formId)
{
	UForm* win = getForm<UForm>(formId);

	if (win != nullptr)
	{
		if (!win->getIsReady() && win->getIsLoadWidgetRes())
		{
			win->onReady();
		}
		if (!win->IsVisible())
		{
			EngineApi::SetActive(win->mGuiWin->mUiRoot, true);
			win->onShow();
		}
		else
		{
			EngineApi::SetActive(win->mGuiWin->mUiRoot, true);
		}
	}
}

// 隐藏一个 UI
void UIMgr::hideFormInternal(UIFormId formId)
{
	UForm* win = getForm<UForm>(formId);
	if (win != nullptr)
	{
		if (win->IsVisible())
		{
			EngineApi::SetActive(win->mGuiWin->mUiRoot, false);
			win->onHide();
		}
	}
}

// 退出一个 UI
void UIMgr::exitForm(UIFormId formId, bool bForce)
{
	UForm* win = getForm<UForm>(formId);

	if (win != nullptr)
	{
		if (win->getExitMode() || bForce)
		{
			this->exitFormInternal(formId);
		}
		else
		{
			this->hideFormInternal(formId);
		}
	}
}

void UIMgr::exitFormInternal(UIFormId formId)
{
	UForm* win = getForm<UForm>(formId);

	if (win != nullptr)
	{
		// 清理列表
		UILayer* layer = win->getUiLayer();
		UtilMap::Remove(layer->getWinDic(), formId);
		// 释放界面资源
		win->onExit();
		EngineApi::Destroy(win->mGuiWin->mUiRoot);
		win->mGuiWin->mUiRoot = nullptr;
		// 释放加载的资源
		//string path = mUiAttrSystem.getPath(formId);
		//if (path != null)
		//{
		//    Ctx.m_instance.mResLoadMgr.unload(path);
		//}
		EngineApi::UnloadUnusedAssets();       // 异步卸载共用资源
		UtilMap::Remove(mId2FormDic, formId);
		win = nullptr;
	}
}

void UIMgr::addForm(UForm* form)
{
	this->addFormNoReady(form);
	form->onInit();
}

UILayer* UIMgr::getLayer(UICanvasId canvasID, UILayerId layerID)
{
	UILayer* layer = nullptr;

	if (eCanvas_50 <= canvasID && canvasID <= eCanvas_100)
	{
		if (eBtmLayer <= layerID && layerID <= eTopLayer)
		{
			layer = this->mCanvasList[(int)canvasID]->getLayerList()[(int)layerID];
		}
	}

	return layer;
}

// 内部接口
void UIMgr::addFormNoReady(UForm* form)
{
	//UILayer* layer = getLayer(mUiAttrSystem->mId2AttrDic[form->getId()]->mCanvasId, mUiAttrSystem->mId2AttrDic[form->getId()]->mLayerId);
	//form->setUiLayer(layer);
	//layer->addForm(form);

	this->mId2FormDic[form->getId()] = form;
	form->init();        // 初始化
}

bool UIMgr::hasForm(UIFormId formId)
{
	return UtilMap::ContainsKey(mId2FormDic, formId);
}

// 加载窗口控件资源，窗口资源都是从文件加载
void UIMgr::loadWidgetRes(UIFormId formId)
{
	UIAttrItem* attrItem = this->mUiAttrSystem->mId2AttrDic[formId];
	if (!UtilMap::ContainsKey(this->mId2WidgetLoadingItemDic, formId))                       // 如果什么都没有创建，第一次加载
	{
		this->mId2WidgetLoadingItemDic[formId] = new UILoadingItem();
		this->mId2WidgetLoadingItemDic[formId]->mId = formId;

		//this->loadFromFile(attrItem->mWidgetPath, EventDispatchDelegate(this, &UIMgr::onWidgetLoadEventHandle));

		AuxMUIClassLoader* uiLoader = SAFE_NEW AuxMUIClassLoader();

		UForm* form = this->getForm<UForm>(formId);
		form->setAuxMUIClassLoader(uiLoader);

		uiLoader->setUMGOuterType(attrItem->mUMGOuterType);
		uiLoader->asyncLoad(attrItem->mWidgetPath, EventDispatchDelegate(this, &UIMgr::onWidgetAuxUIClassloadedByRes));
	}
}

// 从本地磁盘或者网络加载资源
void UIMgr::loadFromFile(std::string resPath, EventDispatchDelegate onLoadEventHandle)
{
	// TODO:
	//LoadParam* param = GPoolSys->newObject<LoadParam>();
	//LocalFileSys::modifyLoadParam(resPath, param);
	//param->mIsLoadNeedCoroutine = false;
	//param->mIsResNeedCoroutine = false;
	//param->mLoadEventHandle = onLoadEventHandle;
	//GClassAssetInsMgr->load<ClassAssetInsRes>(param);
	//GPoolSys->deleteObj(param);

	//GClassAssetInsMgr->getAndSyncLoadRes(resPath, onLoadEventHandle);
	GClassAssetInsMgr->getAndAsyncLoadRes(resPath, onLoadEventHandle);
}

// 代码资源加载处理
void UIMgr::onCodeLoadEventHandle(IDispatchObject* dispObj)
{
	ClassAssetInsRes* res = (ClassAssetInsRes*)dispObj;

	if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
	{
		this->onCodeloadedByRes(res);
	}
	else if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasFailed())
	{
		UIFormId formId = mUiAttrSystem->GetFormIDByPath(res->GetPath(), ePathCodePath);  // 获取 FormId
		UtilMap::Remove(mId2CodeLoadingItemDic, formId);
	}
}

// 窗口控件资源加载处理
void UIMgr::onWidgetLoadEventHandle(IDispatchObject* dispObj)
{
	ClassAssetInsRes* res = (ClassAssetInsRes*)dispObj;

	if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
	{
		this->onWidgetloadedByRes(res);
	}
	else if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasFailed())
	{
		UIFormId formId = this->mUiAttrSystem->GetFormIDByPath(res->GetPath(), ePathComUI);  // 获取 FormId
		UtilMap::Remove(mId2WidgetLoadingItemDic, formId);
		GLogSys->log("UIFormId =  ， Failed Prefab");
	}
}

// 代码资源加载完成处理
void UIMgr::onCodeloadedByRes(ClassAssetInsRes* res)
{
	UIFormId formId = this->mUiAttrSystem->GetFormIDByPath(res->GetPath(), ePathCodePath);  // 获取 FormId
	UtilMap::Remove(this->mId2CodeLoadingItemDic, formId);
	this->addFormNoReady(this->mId2FormDic[formId]);
	this->onCodeLoadedByForm(this->mId2FormDic[formId]);
}

void UIMgr::onCodeLoadedByForm(UForm* form)
{
	//if (null != Ctx.m_instance.m_cbUIEvent)
	//{
	//	Ctx.m_instance.m_cbUIEvent.onCodeFormLoaded(form);  // 资源加载完成
	//}
}

// 窗口控件资源加载完成处理
void UIMgr::onWidgetloadedByRes(ClassAssetInsRes* res)
{
	std::string path = res->GetPath();
	UIFormId formId = this->mUiAttrSystem->GetFormIDByPath(path, ePathComUI);  // 获取 FormId
	UtilMap::Remove(this->mId2WidgetLoadingItemDic, formId);

	UIAttrItem* attrItem = this->mUiAttrSystem->mId2AttrDic[formId];


	UClass* WidgetClass = res->getClass();

	UUMGWidget* WidgetObject = nullptr;

	if (NSFormType::eWorld == attrItem->mUMGOuterType)
	{

	}
	else if (NSFormType::ePlayerController == attrItem->mUMGOuterType)
	{
		WidgetObject = EngineApi::CreateWidget<UUMGWidget>(GEngineData->getMainPlayerController(), WidgetClass);
	}
	else if (NSFormType::eGameInstance == attrItem->mUMGOuterType)
	{

	}

	WidgetObject->AddToViewport();


	this->mId2FormDic[formId]->setIsLoadWidgetRes(true);
	//mId2FormDic[formId]->mGuiWin->mUiRoot = Cast<UUserWidget>(res->InstantiateObject(attrItem->mWidgetPath));
	//this->mId2FormDic[formId]->mGuiWin->mUiRoot = Cast<UUMGWidget>(res->InstantiateObject(attrItem->mWidgetPath));

	this->mId2FormDic[formId]->mGuiWin->mUiRoot = WidgetObject;

	//if (attrItem.m_bNeedLua)
	//{
	//	mId2FormDic[formId].luaCSBridgeForm.gameObject = mId2FormDic[formId].mGuiWin.mUiRoot;
	//	mId2FormDic[formId].luaCSBridgeForm.init();
	//}

	// 设置位置
	//EngineApi::SetParent(mId2FormDic[formId]->mGuiWin->mUiRoot.transform, mCanvasList[(int)(attrItem->mCanvasId)]->getLayerList()[(int)(attrItem->mLayerId)]->getLayerTrans(), false);

	// 先设置再设置缩放，否则无效
	//mId2FormDic[formId]->mGuiWin->mUiRoot.transform.SetAsLastSibling();               // 放在最后
	EngineApi::SetActive(mId2FormDic[formId]->mGuiWin->mUiRoot, false);      // 出发 onShow 事件
	//if (mId2FormDic[formId].hideOnCreate)
	//{
	//    UtilApi.SetActive(mId2FormDic[formId].mGuiWin.mUiRoot, false);
	//}
	//if (!this->mId2FormDic[formId]->getHideOnCreate())
	if(this->mId2FormDic[formId]->isVisible())
	{
		this->showFormInternal(formId);   // 如果 onShow 中调用 exit 函数，就会清掉 mId2FormDic 中的内容。如果设置了 exitMode = false，就不会清掉 mId2FormDic ，就不会有问题
	}

	//if (null != Ctx.m_instance.m_cbUIEvent)
	//{
	//	if (mId2FormDic.ContainsKey(formId))      // 如果 onShow 中调用 exit 函数，并且没有设置 exitMode = false ，就会清除 mId2FormDic， 这个时候再调用这个函数，就会有问题，是不是添加延迟卸载
	//	{
	//		Ctx.m_instance.m_cbUIEvent.onWidgetLoaded(mId2FormDic[formId]);  // 资源加载完成
	//	}
	//}

	// 卸载资源
	//GClassAssetInsMgr->unload(path, EventDispatchDelegate(this, &UIMgr::onWidgetLoadEventHandle));
}

void UIMgr::onWidgetAuxUIClassloadedByRes(IDispatchObject* dispObj)
{
	AuxMUIClassLoader* res = (AuxMUIClassLoader*)dispObj;

	std::string path = res->getLogicPath();
	UIFormId formId = this->mUiAttrSystem->GetFormIDByPath(path, ePathComUI);  // 获取 FormId
	UtilMap::Remove(this->mId2WidgetLoadingItemDic, formId);
	UIAttrItem* attrItem = this->mUiAttrSystem->mId2AttrDic[formId];

	UUMGWidget* WidgetObject = res->getWidgetObject();
	this->mId2FormDic[formId]->setIsLoadWidgetRes(true);
	this->mId2FormDic[formId]->mGuiWin->mUiRoot = WidgetObject;
	EngineApi::SetActive(mId2FormDic[formId]->mGuiWin->mUiRoot, false);      // 出发 onShow 事件

	if (this->mId2FormDic[formId]->isVisible())
	{
		this->showFormInternal(formId);   // 如果 onShow 中调用 exit 函数，就会清掉 mId2FormDic 中的内容。如果设置了 exitMode = false，就不会清掉 mId2FormDic ，就不会有问题
	}

	// 卸载资源
	//GClassAssetInsMgr->unload(path, EventDispatchDelegate(this, &UIMgr::onWidgetLoadEventHandle));
}

// 大小发生变化后，调用此函数
void UIMgr::onResize(int viewWidth, int viewHeight)
{
	int canvasIdx = 0;
	int layerIdx = 0;
	for (canvasIdx = 0; canvasIdx < (int)eCanvas_Total; ++canvasIdx)
	{
		for (layerIdx = 0; layerIdx <= (int)eMaxLayer; ++layerIdx)
		{
			this->mCanvasList[canvasIdx]->getLayerList()[layerIdx]->onStageReSize();
		}
	}
}

// 关闭所有显示的窗口
void UIMgr::exitAllWin()
{
	for(std::pair<UIFormId, UForm*> keyValue : this->mId2FormDic)
	{
		this->mTmpList.Add(keyValue.first);
	}

	for(UIFormId formId : this->mTmpList.getList())
	{
		this->exitForm(formId);
	}
	this->mTmpList.Clear();
}

void UIMgr::findSceneUIRootGo()
{
	//mSceneUIRootGo = UtilApi.GoFindChildByPObjAndName("SceneUIRootGo");
}

// 根据场景类型卸载 UI，强制卸载
//void UIMgr::unloadUIBySceneType(UISceneType unloadSceneType, UISceneType loadSceneTpe)
//{
//	foreach(UIFormId id in mId2FormDic.Keys)
//	{
//		if (mUiAttrSystem.mId2AttrDic[id].canUnloadUIBySceneType(unloadSceneType, loadSceneTpe))
//		{
//			mTmpList.Add(id);
//		}
//	}
//
//	foreach(UIFormId id in mTmpList)
//	{
//		exitForm(id, true);
//	}
//	mTmpList.Clear();
//}