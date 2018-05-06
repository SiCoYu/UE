#include "MyProject.h"
#include "UiMgr.h"
#include "Form.h"
#include "UiAttrSystem.h"
#include "NotDestroyPath.h"
#include "EngineApi.h"
#include "UtilContainers.h"
#include "UiLoadingItem.h"
#include "Common.h"
#include "LoadParam.h"
#include "UiAttrItem.h"
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

UiMgr::UiMgr()
{
	this->mUiAttrSystem = new UiAttrSystem();
	this->createCanvas();
}

void UiMgr::init()
{
	if (nullptr != this->mUiAttrSystem)
	{
		this->mUiAttrSystem->init();
	}
}

void UiMgr::dispose()
{
	if (nullptr != this->mUiAttrSystem)
	{
		this->mUiAttrSystem->dispose();
		this->mUiAttrSystem = nullptr;
	}
}

void UiMgr::createCanvas()
{
	int idx = 0;
	for (idx = 0; idx < (int)eCanvas_Total; ++idx)
	{
		this->mCanvasList.push_back(new UiCanvas((UiCanvasId)idx));
	}

	this->mCanvasList[(int)eCanvas_50]->setGoName(NotDestroyPath::ND_CV_UICanvas_50);
	this->mCanvasList[(int)eCanvas_100]->setGoName(NotDestroyPath::ND_CV_UICanvas_100);
}

// 关联每一层的对象
void UiMgr::findCanvasGO()
{
	int idx = 0;
	for (idx = 0; idx < (int)eCanvas_Total; ++idx)
	{
		this->mCanvasList[idx]->findCanvasGO();
	}
}

// 显示一个 UI
void UiMgr::showForm(UiFormId formId)
{
	if (hasForm(formId))
	{
		this->showFormInternal(formId);
	}
}

void UiMgr::showFormInternal(UiFormId formId)
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
			EngineApi::SetActive(win->mWinRender->mUiRoot, true);
			win->onShow();
		}
		else
		{
			EngineApi::SetActive(win->mWinRender->mUiRoot, true);
		}
	}
}

// 隐藏一个 UI
void UiMgr::hideFormInternal(UiFormId formId)
{
	UForm* win = getForm<UForm>(formId);
	if (win != nullptr)
	{
		if (win->IsVisible())
		{
			EngineApi::SetActive(win->mWinRender->mUiRoot, false);
			win->onHide();
		}
	}
}

// 退出一个 UI
void UiMgr::exitForm(UiFormId formId, bool bForce)
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

void UiMgr::exitFormInternal(UiFormId formId)
{
	UForm* win = getForm<UForm>(formId);

	if (win != nullptr)
	{
		// 清理列表
		UiLayer* layer = win->getUiLayer();
		UtilMap::Remove(layer->getWinDic(), formId);
		// 释放界面资源
		win->onExit();
		EngineApi::Destroy(win->mWinRender->mUiRoot);
		win->mWinRender->mUiRoot = nullptr;
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

void UiMgr::addForm(UForm* form)
{
	this->addFormNoReady(form);
	form->onInit();
}

UiLayer* UiMgr::getLayer(UiCanvasId canvasID, UiLayerId layerID)
{
	UiLayer* layer = nullptr;

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
void UiMgr::addFormNoReady(UForm* form)
{
	//UiLayer* layer = getLayer(mUiAttrSystem->mId2AttrDic[form->getId()]->mCanvasId, mUiAttrSystem->mId2AttrDic[form->getId()]->mLayerId);
	//form->setUiLayer(layer);
	//layer->addForm(form);

	this->mId2FormDic[form->getId()] = form;
	form->init();        // 初始化
}

bool UiMgr::hasForm(UiFormId formId)
{
	return UtilMap::ContainsKey(mId2FormDic, formId);
}

// 加载窗口控件资源，窗口资源都是从文件加载
void UiMgr::loadWidgetRes(UiFormId formId)
{
	UiAttrItem* attrItem = this->mUiAttrSystem->mId2AttrDic[formId];
	if (!UtilMap::ContainsKey(this->mId2WidgetLoadingItemDic, formId))                       // 如果什么都没有创建，第一次加载
	{
		this->mId2WidgetLoadingItemDic[formId] = new UiLoadingItem();
		this->mId2WidgetLoadingItemDic[formId]->mId = formId;

		//this->loadFromFile(attrItem->mWidgetPath, EventDispatchDelegate(this, &UiMgr::onWidgetLoadEventHandle));

		AuxMUIClassLoader* uiLoader = SAFE_NEW AuxMUIClassLoader();

		UForm* form = this->getForm<UForm>(formId);
		form->setAuxMUIClassLoader(uiLoader);

		uiLoader->setUMGOuterType(attrItem->mUMGOuterType);
		uiLoader->asyncLoad(attrItem->mWidgetPath, EventDispatchDelegate(this, &UiMgr::onWidgetAuxUIClassloadedByRes));
	}
}

// 从本地磁盘或者网络加载资源
void UiMgr::loadFromFile(std::string resPath, EventDispatchDelegate onLoadEventHandle)
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
void UiMgr::onCodeLoadEventHandle(IDispatchObject* dispObj)
{
	ClassAssetInsRes* res = (ClassAssetInsRes*)dispObj;

	if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
	{
		this->onCodeloadedByRes(res);
	}
	else if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasFailed())
	{
		UiFormId formId = mUiAttrSystem->GetFormIDByPath(res->GetPath(), ePathCodePath);  // 获取 FormId
		UtilMap::Remove(mId2CodeLoadingItemDic, formId);
	}
}

// 窗口控件资源加载处理
void UiMgr::onWidgetLoadEventHandle(IDispatchObject* dispObj)
{
	ClassAssetInsRes* res = (ClassAssetInsRes*)dispObj;

	if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
	{
		this->onWidgetloadedByRes(res);
	}
	else if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasFailed())
	{
		UiFormId formId = this->mUiAttrSystem->GetFormIDByPath(res->GetPath(), ePathComUI);  // 获取 FormId
		UtilMap::Remove(mId2WidgetLoadingItemDic, formId);
		GLogSys->log("UiFormId =  ， Failed Prefab");
	}
}

// 代码资源加载完成处理
void UiMgr::onCodeloadedByRes(ClassAssetInsRes* res)
{
	UiFormId formId = this->mUiAttrSystem->GetFormIDByPath(res->GetPath(), ePathCodePath);  // 获取 FormId
	UtilMap::Remove(this->mId2CodeLoadingItemDic, formId);
	this->addFormNoReady(this->mId2FormDic[formId]);
	this->onCodeLoadedByForm(this->mId2FormDic[formId]);
}

void UiMgr::onCodeLoadedByForm(UForm* form)
{
	//if (null != Ctx.m_instance.m_cbUIEvent)
	//{
	//	Ctx.m_instance.m_cbUIEvent.onCodeFormLoaded(form);  // 资源加载完成
	//}
}

// 窗口控件资源加载完成处理
void UiMgr::onWidgetloadedByRes(ClassAssetInsRes* res)
{
	std::string path = res->GetPath();
	UiFormId formId = this->mUiAttrSystem->GetFormIDByPath(path, ePathComUI);  // 获取 FormId
	UtilMap::Remove(this->mId2WidgetLoadingItemDic, formId);

	UiAttrItem* attrItem = this->mUiAttrSystem->mId2AttrDic[formId];


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
	//mId2FormDic[formId]->mWinRender->mUiRoot = Cast<UUserWidget>(res->InstantiateObject(attrItem->mWidgetPath));
	//this->mId2FormDic[formId]->mWinRender->mUiRoot = Cast<UUMGWidget>(res->InstantiateObject(attrItem->mWidgetPath));

	this->mId2FormDic[formId]->mWinRender->mUiRoot = WidgetObject;

	//if (attrItem.m_bNeedLua)
	//{
	//	mId2FormDic[formId].luaCSBridgeForm.gameObject = mId2FormDic[formId].mWinRender.mUiRoot;
	//	mId2FormDic[formId].luaCSBridgeForm.init();
	//}

	// 设置位置
	//EngineApi::SetParent(mId2FormDic[formId]->mWinRender->mUiRoot.transform, mCanvasList[(int)(attrItem->mCanvasId)]->getLayerList()[(int)(attrItem->mLayerId)]->getLayerTrans(), false);

	// 先设置再设置缩放，否则无效
	//mId2FormDic[formId]->mWinRender->mUiRoot.transform.SetAsLastSibling();               // 放在最后
	EngineApi::SetActive(mId2FormDic[formId]->mWinRender->mUiRoot, false);      // 出发 onShow 事件
	//if (mId2FormDic[formId].hideOnCreate)
	//{
	//    UtilApi.SetActive(mId2FormDic[formId].mWinRender.mUiRoot, false);
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
	//GClassAssetInsMgr->unload(path, EventDispatchDelegate(this, &UiMgr::onWidgetLoadEventHandle));
}

void UiMgr::onWidgetAuxUIClassloadedByRes(IDispatchObject* dispObj)
{
	AuxMUIClassLoader* res = (AuxMUIClassLoader*)dispObj;

	std::string path = res->getLogicPath();
	UiFormId formId = this->mUiAttrSystem->GetFormIDByPath(path, ePathComUI);  // 获取 FormId
	UtilMap::Remove(this->mId2WidgetLoadingItemDic, formId);
	UiAttrItem* attrItem = this->mUiAttrSystem->mId2AttrDic[formId];

	UUMGWidget* WidgetObject = res->getWidgetObject();
	this->mId2FormDic[formId]->setIsLoadWidgetRes(true);
	this->mId2FormDic[formId]->mWinRender->mUiRoot = WidgetObject;
	EngineApi::SetActive(mId2FormDic[formId]->mWinRender->mUiRoot, false);      // 出发 onShow 事件

	if (this->mId2FormDic[formId]->isVisible())
	{
		this->showFormInternal(formId);   // 如果 onShow 中调用 exit 函数，就会清掉 mId2FormDic 中的内容。如果设置了 exitMode = false，就不会清掉 mId2FormDic ，就不会有问题
	}

	// 卸载资源
	//GClassAssetInsMgr->unload(path, EventDispatchDelegate(this, &UiMgr::onWidgetLoadEventHandle));
}

// 大小发生变化后，调用此函数
void UiMgr::onResize(int viewWidth, int viewHeight)
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
void UiMgr::exitAllWin()
{
	for(std::pair<UiFormId, UForm*> keyValue : this->mId2FormDic)
	{
		this->mTmpList.Add(keyValue.first);
	}

	for(UiFormId formId : this->mTmpList.getList())
	{
		this->exitForm(formId);
	}
	this->mTmpList.Clear();
}

void UiMgr::findSceneUIRootGo()
{
	//mSceneUIRootGo = UtilApi.GoFindChildByPObjAndName("SceneUIRootGo");
}

// 根据场景类型卸载 UI，强制卸载
//void UiMgr::unloadUIBySceneType(UISceneType unloadSceneType, UISceneType loadSceneTpe)
//{
//	foreach(UiFormId id in mId2FormDic.Keys)
//	{
//		if (mUiAttrSystem.mId2AttrDic[id].canUnloadUIBySceneType(unloadSceneType, loadSceneTpe))
//		{
//			mTmpList.Add(id);
//		}
//	}
//
//	foreach(UiFormId id in mTmpList)
//	{
//		exitForm(id, true);
//	}
//	mTmpList.Clear();
//}