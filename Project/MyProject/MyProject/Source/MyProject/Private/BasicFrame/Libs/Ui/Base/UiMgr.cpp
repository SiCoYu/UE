#include "MyProject.h"
#include "UiMgr.h"
#include "Form.h"
#include "UiAttrSystem.h"
#include "LayerPath.h"
#include "UtilEngineWrap.h"
#include "UiLoadingItem.h"
#include "Prequisites.h"
#include "LoadParam.h"
#include "UiAttrItem.h"
#include "RefCountResLoadResultNotify.h"
#include "ResLoadState.h"
#include "Templates/SubclassOf.h"	// TSubclassOf
#include "UMGWidget.h"				// UUMGWidget
#include "UtilStr.h"				// UtilStr
#include "UMGWidget.h"				// UUMGWidget
#include "ClassAssetInsRes.h"
#include "AuxMUiClassLoader.h"
#include "SafePointer.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(UiMgr, GObject)

UiMgr::UiMgr()
{
	this->mUiAttrSystem = MY_NEW UiAttrSystem();
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
	this->exitAllForm();

	MY_SAFE_DISPOSE(this->mUiAttrSystem);

	int index = 0;
	UiCanvas* uiCanvas = nullptr;

	while (index < (int)UiCanvasId::eCanvas_Total)
	{
		uiCanvas = this->mCanvasList.get(index);
		MY_SAFE_DISPOSE(uiCanvas);

		index += 1;
	}

	this->mCanvasList.clear();
}

void UiMgr::createCanvas()
{
	int idx = 0;
	UiCanvas* uiCanvas = nullptr;

	for (idx = 0; idx < (int)UiCanvasId::eCanvas_Total; ++idx)
	{
		uiCanvas = MY_NEW UiCanvas((UiCanvasId)idx);
		this->mCanvasList.add(uiCanvas);
		uiCanvas->init();
	}

	this->mCanvasList[(int)UiCanvasId::eCanvas_50]->setActorName(LayerPath::ND_CV_UICanvas_50);
	this->mCanvasList[(int)UiCanvasId::eCanvas_100]->setActorName(LayerPath::ND_CV_UICanvas_100);
}

// 关联每一层的对象
void UiMgr::findCanvasActor()
{
	int idx = 0;

	for (idx = 0; idx < (int)UiCanvasId::eCanvas_Total; ++idx)
	{
		this->mCanvasList[idx]->findCanvasActor();
	}
}

// 显示一个 UI
void UiMgr::showForm(UiFormId formId)
{
	if (this->hasForm(formId))
	{
		this->_showFormInternal(formId);
	}
}

void UiMgr::_showFormInternal(UiFormId formId)
{
	UForm* form = this->getForm<UForm>(formId);

	if (form != nullptr)
	{
		if (!form->isReady())
		{
			form->onReady();
		}
		if (!form->IsVisible())
		{
			UtilEngineWrap::SetActive(form->mWinRender->mUiRoot, true);
			form->onShow();
		}
		else
		{
			UtilEngineWrap::SetActive(form->mWinRender->mUiRoot, true);
		}
	}
}

// 隐藏一个 UI
void UiMgr::_hideFormInternal(UiFormId formId)
{
	UForm* form = this->getForm<UForm>(formId);

	if (form != nullptr)
	{
		if (form->IsVisible())
		{
			UtilEngineWrap::SetActive(form->mWinRender->mUiRoot, false);
			form->onHide();
		}
	}
}

// 退出一个 UI
void UiMgr::exitForm(UiFormId formId, bool bForce)
{
	UForm* form = this->getForm<UForm>(formId);

	if (form != nullptr)
	{
		if (form->getExitMode() || bForce)
		{
			this->_exitFormInternal(formId);
		}
		else
		{
			this->_hideFormInternal(formId);
		}
	}
}

void UiMgr::_exitFormInternal(UiFormId formId)
{
	UForm* form = this->getForm<UForm>(formId);

	if (form != nullptr)
	{
		GNativeObjectReferencer->removeObjectReference(form);

		// 清理列表
		UiLayer* layer = form->getUiLayer();
		layer->getWinDic().remove(formId);

		SSlateWidget* uiRoot_S = form->mWinRender->mUiRoot_S;
		UUMGWidget* uiRoot = form->mWinRender->mUiRoot;

		// 释放界面资源
		form->onExit();
		//UtilEngineWrap::Destroy(form->mWinRender->mUiRoot);
		//form->mWinRender->mUiRoot = nullptr;
		UtilEngineWrap::Destroy(uiRoot);

		// 释放加载的资源
		//string path = mUiAttrSystem.getPath(formId);
		//if (path != nullptr)
		//{
		//    Ctx.m_instance.mResLoadMgr.unload(path);
		//}
		UtilEngineWrap::UnloadUnusedAssets();       // 异步卸载共用资源
		this->mId2FormDic.remove(formId);
		form = nullptr;
	}
}

void UiMgr::addForm(UForm* form)
{
	this->addFormNoReady(form);
	form->onInit();
}

UiLayer* UiMgr::getLayer(UiCanvasId canvasId, UiLayerId layerId)
{
	UiLayer* layer = nullptr;

	if (canvasId >= UiCanvasId::eCanvas_50 &&
		canvasId <= UiCanvasId::eCanvas_100)
	{
		if (layerId >= UiLayerId::eBtmLayer &&
			layerId <= UiLayerId::eTopLayer)
		{
			layer = this->mCanvasList[(int)canvasId]->getLayerList()[(int)layerId];
		}
	}

	return layer;
}

// 内部接口
void UiMgr::addFormNoReady(UForm* form)
{
	GNativeObjectReferencer->addObjectReference(form);

	UiFormId formId = form->getId();

	UiLayer* layer = this->getLayer(
		this->mUiAttrSystem->mId2AttrDic[formId]->mCanvasId,
		this->mUiAttrSystem->mId2AttrDic[formId]->mLayerId
	);

	form->setUiLayer(layer);
	layer->addForm(form);

	this->mId2FormDic.add(formId, form);
	form->init();        // 初始化
}

bool UiMgr::hasForm(UiFormId formId)
{
	return this->mId2FormDic.containsKey(formId);
}

// 加载窗口控件资源，窗口资源都是从文件加载
void UiMgr::loadWidgetRes(UiFormId formId)
{
	UiAttrItem* attrItem = this->mUiAttrSystem->mId2AttrDic[formId];

	if (!this->mId2WidgetLoadingItemDic.containsKey(formId))                       // 如果什么都没有创建，第一次加载
	{
		this->mId2WidgetLoadingItemDic[formId] = MY_NEW UiLoadingItem();
		this->mId2WidgetLoadingItemDic[formId]->mId = formId;

		//this->loadFromFile(attrItem->mWidgetPath, MakeEventDispatchDelegate(this, &UiMgr::onWidgetLoadEventHandle));

		AuxMUiClassLoader* uiLoader = MY_NEW AuxMUiClassLoader();
		uiLoader->setDestroySelf(false);

		UForm* form = this->getForm<UForm>(formId);
		form->setAuxMUIClassLoader(uiLoader);

		uiLoader->setUMGOuterType(attrItem->mUMGOuterType);
		uiLoader->asyncLoad(
			attrItem->mWidgetPath, 
			MakeEventDispatchDelegate(
				this, 
				&UiMgr::onWidgetAuxUIClassloadedByRes, 
				0
			)
		);
	}
}

// 从本地磁盘或者网络加载资源
void UiMgr::loadFromFile(
	std::string resPath, 
	EventDispatchDelegate onLoadEventHandle
)
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
void UiMgr::onCodeLoadEventHandle(IDispatchObject* dispObj, uint eventId)
{
	ClassAssetInsRes* res = (ClassAssetInsRes*)dispObj;

	if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
	{
		this->onCodeloadedByRes(res);
	}
	else if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasFailed())
	{
		UiFormId formId = mUiAttrSystem->GetFormIDByPath(
			res->getPath(), 
			ResPathType::ePathCodePath
		);  // 获取 FormId

		this->mId2CodeLoadingItemDic.remove(formId);
	}
}

// 窗口控件资源加载处理
void UiMgr::onWidgetLoadEventHandle(IDispatchObject* dispObj, uint eventId)
{
	ClassAssetInsRes* res = (ClassAssetInsRes*)dispObj;

	if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
	{
		this->onWidgetloadedByRes(res);
	}
	else if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasFailed())
	{
		UiFormId formId = this->mUiAttrSystem->GetFormIDByPath(res->getPath(), ResPathType::ePathComUI);  // 获取 FormId
		this->mId2WidgetLoadingItemDic.remove(formId);
		GLogSys->log("UiFormId =  ， Failed Prefab");
	}
}

// 代码资源加载完成处理
void UiMgr::onCodeloadedByRes(ClassAssetInsRes* res)
{
	UiFormId formId = this->mUiAttrSystem->GetFormIDByPath(res->getPath(), ResPathType::ePathCodePath);  // 获取 FormId
	this->mId2CodeLoadingItemDic.remove(formId);
	this->addFormNoReady(this->mId2FormDic[formId]);
	this->onCodeLoadedByForm(this->mId2FormDic[formId]);
}

void UiMgr::onCodeLoadedByForm(UForm* form)
{
	//if (nullptr != Ctx.m_instance.m_cbUIEvent)
	//{
	//	Ctx.m_instance.m_cbUIEvent.onCodeFormLoaded(form);  // 资源加载完成
	//}
}

// 窗口控件资源加载完成处理
void UiMgr::onWidgetloadedByRes(ClassAssetInsRes* res)
{
	std::string path = res->getPath();
	UiFormId formId = this->mUiAttrSystem->GetFormIDByPath(path, ResPathType::ePathComUI);  // 获取 FormId
	this->mId2WidgetLoadingItemDic.remove(formId);
	UiAttrItem* attrItem = this->mUiAttrSystem->mId2AttrDic[formId];

	UClass* WidgetClass = res->getClass();
	UUMGWidget* WidgetObject = nullptr;

	if (UMGOuterType::eWorld == attrItem->mUMGOuterType)
	{

	}
	else if (UMGOuterType::ePlayerController == attrItem->mUMGOuterType)
	{
		WidgetObject = UtilEngineWrap::CreateWidget<UUMGWidget>(GEngineData->getMainPlayerController(), WidgetClass);
	}
	else if (UMGOuterType::eGameInstance == attrItem->mUMGOuterType)
	{

	}

	WidgetObject->AddToViewport();

	//mId2FormDic[formId]->mWinRender->mUiRoot = Cast<UUserWidget>(res->InstantiateObject(attrItem->mWidgetPath));
	//this->mId2FormDic[formId]->mWinRender->mUiRoot = Cast<UUMGWidget>(res->InstantiateObject(attrItem->mWidgetPath));

	this->mId2FormDic[formId]->mWinRender->mUiRoot = WidgetObject;

	//if (attrItem.m_bNeedLua)
	//{
	//	mId2FormDic[formId].luaCSBridgeForm.gameObject = mId2FormDic[formId].mWinRender.mUiRoot;
	//	mId2FormDic[formId].luaCSBridgeForm.init();
	//}

	// 设置位置
	//UtilEngineWrap::SetParent(mId2FormDic[formId]->mWinRender->mUiRoot.transform, mCanvasList[(int)(attrItem->mCanvasId)]->getLayerList()[(int)(attrItem->mLayerId)]->getLayerTrans(), false);

	// 先设置再设置缩放，否则无效
	//mId2FormDic[formId]->mWinRender->mUiRoot.transform.SetAsLastSibling();               // 放在最后
	UtilEngineWrap::SetActive(
		mId2FormDic[formId]->mWinRender->mUiRoot, 
		false
	);      // 出发 onShow 事件
	//if (mId2FormDic[formId].hideOnCreate)
	//{
	//    UtilSysLibWrap.SetActive(mId2FormDic[formId].mWinRender.mUiRoot, false);
	//}
	//if (!this->mId2FormDic[formId]->getHideOnCreate())
	if(this->mId2FormDic[formId]->isVisible())
	{
		this->_showFormInternal(formId);   // 如果 onShow 中调用 exit 函数，就会清掉 mId2FormDic 中的内容。如果设置了 exitMode = false，就不会清掉 mId2FormDic ，就不会有问题
	}
	else
	{
		this->_hideFormInternal(formId);
	}

	//if (nullptr != Ctx.m_instance.m_cbUIEvent)
	//{
	//	if (mId2FormDic.ContainsKey(formId))      // 如果 onShow 中调用 exit 函数，并且没有设置 exitMode = false ，就会清除 mId2FormDic， 这个时候再调用这个函数，就会有问题，是不是添加延迟卸载
	//	{
	//		Ctx.m_instance.m_cbUIEvent.onWidgetLoaded(mId2FormDic[formId]);  // 资源加载完成
	//	}
	//}

	// 卸载资源
	//GClassAssetInsMgr->unload(path, MakeEventDispatchDelegate(this, &UiMgr::onWidgetLoadEventHandle));
}

void UiMgr::onWidgetAuxUIClassloadedByRes(IDispatchObject* dispObj, uint eventId)
{
	AuxMUiClassLoader* res = (AuxMUiClassLoader*)dispObj;

	std::string path = res->getOrigPath();
	UiFormId formId = this->mUiAttrSystem->GetFormIDByPath(path, ResPathType::ePathComUI);  // 获取 FormId
	this->mId2WidgetLoadingItemDic.remove(formId);
	UiAttrItem* attrItem = this->mUiAttrSystem->mId2AttrDic[formId];

	UUMGWidget* WidgetObject = res->getWidgetObject();

	this->mId2FormDic[formId]->mWinRender->mUiRoot = WidgetObject;
	UtilEngineWrap::SetActive(mId2FormDic[formId]->mWinRender->mUiRoot, false);      // 出发 onShow 事件

	if (this->mId2FormDic[formId]->isVisible())
	{
		this->_showFormInternal(formId);   // 如果 onShow 中调用 exit 函数，就会清掉 mId2FormDic 中的内容。如果设置了 exitMode = false，就不会清掉 mId2FormDic ，就不会有问题
	}

	// 卸载资源
	//GClassAssetInsMgr->unload(path, MakeEventDispatchDelegate(this, &UiMgr::onWidgetLoadEventHandle));
}

// 大小发生变化后，调用此函数
void UiMgr::onResize(int viewWidth, int viewHeight)
{
	int canvasIdx = 0;
	int layerIdx = 0;

	for (canvasIdx = 0; canvasIdx < (int)UiCanvasId::eCanvas_Total; ++canvasIdx)
	{
		for (layerIdx = 0; layerIdx <= (int)UiLayerId::eMaxLayer; ++layerIdx)
		{
			this->mCanvasList[canvasIdx]->getLayerList()[layerIdx]->onStageReSize();
		}
	}
}

// 关闭所有显示的窗口
void UiMgr::exitAllForm()
{
	for(std::pair<UiFormId, UForm*> keyValue : this->mId2FormDic.getData())
	{
		this->mTmpList.add(keyValue.first);
	}

	for(UiFormId formId : this->mTmpList.getList())
	{
		this->exitForm(formId);
	}

	this->mTmpList.clear();
}

void UiMgr::findSceneUIRootActor()
{
	//mSceneUIRootGo = UtilSysLibWrap.GoFindChildByPObjAndName("SceneUIRootGo");
}

// 根据场景类型卸载 UI，强制卸载
//void UiMgr::unloadUIBySceneType(UISceneType unloadSceneType, UISceneType loadSceneTpe)
//{
//	foreach(enum UiFormId id in mId2FormDic.Keys)
//	{
//		if (mUiAttrSystem.mId2AttrDic[id].canUnloadUIBySceneType(unloadSceneType, loadSceneTpe))
//		{
//			mTmpList.Add(id);
//		}
//	}
//
//	foreach(enum UiFormId id in mTmpList)
//	{
//		exitForm(id, true);
//	}
//	mTmpList.Clear();
//}

MY_END_NAMESPACE