#include "MyProject.h"
#include "UIMgr.h"
#include "Form.h"
#include "UIAttrSystem.h"
#include "NotDestroyPath.h"
#include "EngineApi.h"
#include "UtilContainers.h"
#include "UILoadingItem.h"
#include "Common.h"
#include "LocalFileSys.h"
#include "LoadParam.h"
#include "UIAssetRes.h"
#include "UIAttrItem.h"
#include "RefCountResLoadResultNotify.h"
#include "ResLoadState.h"

UIMgr::UIMgr()
{
	m_UIAttrs = new UIAttrSystem();
	createCanvas();
}

void UIMgr::createCanvas()
{
	int idx = 0;
	for (idx = 0; idx < (int)eCanvas_Total; ++idx)
	{
		m_canvasList.push_back(new UICanvas((UICanvasID)idx));
	}

	m_canvasList[(int)eCanvas_50]->setGoName(NotDestroyPath::ND_CV_UICanvas_50);
	m_canvasList[(int)eCanvas_100]->setGoName(NotDestroyPath::ND_CV_UICanvas_100);
}

// 关联每一层的对象
void UIMgr::findCanvasGO()
{
	int idx = 0;
	for (idx = 0; idx < (int)eCanvas_Total; ++idx)
	{
		m_canvasList[idx]->findCanvasGO();
	}
}

void UIMgr::loadAndShow(UIFormID ID)
{
	if (hasForm(ID))
	{
		showFormInternal(ID);
	}
	else
	{
		loadForm(ID);
	}
}

// 显示一个 UI
void UIMgr::showForm(UIFormID ID)
{
	if (hasForm(ID))
	{
		showFormInternal(ID);
	}
}

void UIMgr::showFormInternal(UIFormID ID)
{
	UForm* win = getForm(ID);
	if (win != nullptr)
	{
		if (!win->getIsReady())
		{
			win->onReady();
		}
		if (!win->IsVisible())
		{
			EngineApi::SetActive(win->m_GUIWin->m_uiRoot, true);
			win->onShow();
		}
	}
}

// 隐藏一个 UI
void UIMgr::hideFormInternal(UIFormID ID)
{
	UForm* win = getForm(ID);
	if (win != nullptr)
	{
		if (win->IsVisible())
		{
			EngineApi::SetActive(win->m_GUIWin->m_uiRoot, false);
			win->onHide();
		}
	}
}

// 退出一个 UI
void UIMgr::exitForm(UIFormID ID, bool bForce)
{
	UForm* win = getForm(ID);

	if (win != nullptr)
	{
		if (win->getExitMode() || bForce)
		{
			exitFormInternal(ID);
		}
		else
		{
			hideFormInternal(ID);
		}
	}
}

void UIMgr::exitFormInternal(UIFormID ID)
{
	UForm* win = getForm(ID);

	if (win != nullptr)
	{
		// 清理列表
		UILayer* layer = win->getUiLayer();
		UtilMap::Remove(layer->getWinDic(), ID);
		// 释放界面资源
		win->onExit();
		EngineApi::Destroy(win->m_GUIWin->m_uiRoot);
		win->m_GUIWin->m_uiRoot = nullptr;
		// 释放加载的资源
		//string path = m_UIAttrs.getPath(ID);
		//if (path != null)
		//{
		//    Ctx.m_instance.mResLoadMgr.unload(path);
		//}
		EngineApi::UnloadUnusedAssets();       // 异步卸载共用资源
		UtilMap::Remove(m_id2FormDic, ID);
		win = nullptr;
	}
}

void UIMgr::addForm(UForm* form)
{
	addFormNoReady(form);
	form->onInit();
}

UILayer* UIMgr::getLayer(UICanvasID canvasID, UILayerID layerID)
{
	UILayer* layer = nullptr;

	if (eCanvas_50 <= canvasID && canvasID <= eCanvas_100)
	{
		if (eBtmLayer <= layerID && layerID <= eTopLayer)
		{
			layer = m_canvasList[(int)canvasID]->getLayerList()[(int)layerID];
		}
	}

	return layer;
}

// 内部接口
void UIMgr::addFormNoReady(UForm* form)
{
	UILayer* layer = getLayer(m_UIAttrs->m_id2AttrDic[form->getID()]->m_canvasID, m_UIAttrs->m_id2AttrDic[form->getID()]->m_LayerID);
	form->setUiLayer(layer);
	layer->addForm(form);

	m_id2FormDic[form->getID()] = form;
	form->init();        // 初始化
}

UForm* UIMgr::getForm(UIFormID ID)
{
	if (UtilMap::ContainsKey(m_id2FormDic, ID))
	{
		return m_id2FormDic[ID];
	}
	else
	{
		return nullptr;
	}
}

bool UIMgr::hasForm(UIFormID ID)
{
	return UtilMap::ContainsKey(m_id2FormDic, ID);
}

// 这个事加载界面需要的代码
void UIMgr::loadForm(UIFormID ID)
{
	UIAttrItem* attrItem = m_UIAttrs->m_id2AttrDic[ID];
	UForm* window = getForm(ID);

	if (window != nullptr)     // 本地已经创建了这个窗口，
	{
		if (window->getIsResReady())      // 如果资源也已经加载进来了
		{
			//if (nullptr != Ctx.m_instance.m_cbUIEvent)
			//{
			//	Ctx.m_instance.m_cbUIEvent.onCodeFormLoaded(window);  // 资源加载完成
			//}
		}
	}
	else if (!UtilMap::ContainsKey(m_ID2CodeLoadingItemDic, ID))                       // 如果什么都没有创建，第一次加载
	{
		// 创建窗口
		UForm* form = nullptr;
		//if (attrItem.m_bNeedLua)
		//{
		//	form = new Form();
		//}
		//else
		//{
		//	form = Ctx.m_instance.m_scriptDynLoad.getScriptObject(attrItem.m_scriptTypeName) as Form;
		//}

		if (form != nullptr)                   // 如果代码已经在本地
		{
			form->setID(ID);
			//if (attrItem.m_bNeedLua)
			//{
			//	form.luaCSBridgeForm = new LuaCSBridgeForm(attrItem.m_luaScriptTableName, form);
			//	form.luaCSBridgeForm.DoFile(attrItem.m_luaScriptPath);
			//}

			addFormNoReady(form);           // 仅仅是创建数据，资源还没有加载完成
			onCodeLoadedByForm(form);
		}

		// 这个地方应该抛出异常
		if (nullptr == form)    // 本地没有代码
		{
			m_ID2CodeLoadingItemDic[ID] = new UILoadingItem();
			m_ID2CodeLoadingItemDic[ID]->m_ID = ID;

			loadFromFile(attrItem->m_codePath, EventDispatchDelegate(this, &UIMgr::onCodeLoadEventHandle));
		}
	}
}

// 加载窗口控件资源，窗口资源都是从文件加载
void UIMgr::loadWidgetRes(UIFormID ID)
{
	UIAttrItem* attrItem = m_UIAttrs->m_id2AttrDic[ID];
	if (!UtilMap::ContainsKey(m_ID2WidgetLoadingItemDic, ID))                       // 如果什么都没有创建，第一次加载
	{
		m_ID2WidgetLoadingItemDic[ID] = new UILoadingItem();
		m_ID2WidgetLoadingItemDic[ID]->m_ID = ID;

		loadFromFile(attrItem->m_widgetPath, EventDispatchDelegate(this, &UIMgr::onWidgetLoadEventHandle));
	}
}

// 从本地磁盘或者网络加载资源
void UIMgr::loadFromFile(std::string reaPath, EventDispatchDelegate onLoadEventHandle)
{
	// TODO:
	LoadParam* param = GPoolSys->newObject<LoadParam>();
	LocalFileSys::modifyLoadParam(reaPath, param);
	param->mIsLoadNeedCoroutine = false;
	param->mIsResNeedCoroutine = false;
	param->mLoadEventHandle = onLoadEventHandle;
	GUiAssetMgr->load<UIAssetRes>(param);
	GPoolSys->deleteObj(param);
}

// 代码资源加载处理
void UIMgr::onCodeLoadEventHandle(IDispatchObject* dispObj)
{
	UIAssetRes* res = (UIAssetRes*)dispObj;
	if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
	{
		onCodeloadedByRes(res);
	}
	else if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasFailed())
	{
		UIFormID ID = m_UIAttrs->GetFormIDByPath(res->GetPath(), ePathCodePath);  // 获取 FormID
		UtilMap::Remove(m_ID2CodeLoadingItemDic, ID);
	}
}

// 窗口控件资源加载处理
void UIMgr::onWidgetLoadEventHandle(IDispatchObject* dispObj)
{
	UIAssetRes* res = (UIAssetRes*)dispObj;
	if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
	{
		onWidgetloadedByRes(res);
	}
	else if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasFailed())
	{
		UIFormID ID = m_UIAttrs->GetFormIDByPath(res->GetPath(), ePathComUI);  // 获取 FormID
		UtilMap::Remove(m_ID2WidgetLoadingItemDic, ID);
		GLogSys->log("UIFormID =  ， Failed Prefab");
	}
}

// 代码资源加载完成处理
void UIMgr::onCodeloadedByRes(UIAssetRes* res)
{
	UIFormID ID = m_UIAttrs->GetFormIDByPath(res->GetPath(), ePathCodePath);  // 获取 FormID
	UtilMap::Remove(m_ID2CodeLoadingItemDic, ID);
	addFormNoReady(m_id2FormDic[ID]);
	onCodeLoadedByForm(m_id2FormDic[ID]);
}

void UIMgr::onCodeLoadedByForm(UForm* form)
{
	//if (null != Ctx.m_instance.m_cbUIEvent)
	//{
	//	Ctx.m_instance.m_cbUIEvent.onCodeFormLoaded(form);  // 资源加载完成
	//}
}

// 窗口控件资源加载完成处理
void UIMgr::onWidgetloadedByRes(UIAssetRes* res)
{
	std::string path = res->GetPath();
	UIFormID ID = m_UIAttrs->GetFormIDByPath(path, ePathComUI);  // 获取 FormID
	UtilMap::Remove(m_ID2WidgetLoadingItemDic, ID);

	UIAttrItem* attrItem = m_UIAttrs->m_id2AttrDic[ID];
	m_id2FormDic[ID]->setIsLoadWidgetRes(true);
	m_id2FormDic[ID]->m_GUIWin->m_uiRoot = Cast<UUserWidget>(res->InstantiateObject(attrItem->m_widgetPath));
	//if (attrItem.m_bNeedLua)
	//{
	//	m_id2FormDic[ID].luaCSBridgeForm.gameObject = m_id2FormDic[ID].m_GUIWin.m_uiRoot;
	//	m_id2FormDic[ID].luaCSBridgeForm.init();
	//}

	// 设置位置
	//EngineApi::SetParent(m_id2FormDic[ID]->m_GUIWin->m_uiRoot.transform, m_canvasList[(int)(attrItem->m_canvasID)]->getLayerList()[(int)(attrItem->m_LayerID)]->getLayerTrans(), false);

	// 先设置再设置缩放，否则无效
	//m_id2FormDic[ID]->m_GUIWin->m_uiRoot.transform.SetAsLastSibling();               // 放在最后
	EngineApi::SetActive(m_id2FormDic[ID]->m_GUIWin->m_uiRoot, false);      // 出发 onShow 事件
	//if (m_id2FormDic[ID].hideOnCreate)
	//{
	//    UtilApi.SetActive(m_id2FormDic[ID].m_GUIWin.m_uiRoot, false);
	//}
	if (!m_id2FormDic[ID]->getHideOnCreate())
	{
		showFormInternal(ID);   // 如果 onShow 中调用 exit 函数，就会清掉 m_id2FormDic 中的内容。如果设置了 exitMode = false，就不会清掉 m_id2FormDic ，就不会有问题
	}

	//if (null != Ctx.m_instance.m_cbUIEvent)
	//{
	//	if (m_id2FormDic.ContainsKey(ID))      // 如果 onShow 中调用 exit 函数，并且没有设置 exitMode = false ，就会清除 m_id2FormDic， 这个时候再调用这个函数，就会有问题，是不是添加延迟卸载
	//	{
	//		Ctx.m_instance.m_cbUIEvent.onWidgetLoaded(m_id2FormDic[ID]);  // 资源加载完成
	//	}
	//}

	// 卸载资源
	GUiAssetMgr->unload(path, EventDispatchDelegate(this, &UIMgr::onWidgetLoadEventHandle));
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
			m_canvasList[canvasIdx]->getLayerList()[layerIdx]->onStageReSize();
		}
	}
}

// 关闭所有显示的窗口
void UIMgr::exitAllWin()
{
	for(std::pair<UIFormID, UForm*> keyValue : m_id2FormDic)
	{
		m_tmpList.Add(keyValue.first);
	}

	for(UIFormID id : m_tmpList.getList())
	{
		exitForm(id);
	}
	m_tmpList.Clear();
}

void UIMgr::findSceneUIRootGo()
{
	//m_sceneUIRootGo = UtilApi.GoFindChildByPObjAndName("SceneUIRootGo");
}

// 根据场景类型卸载 UI，强制卸载
//void UIMgr::unloadUIBySceneType(UISceneType unloadSceneType, UISceneType loadSceneTpe)
//{
//	foreach(UIFormID id in m_id2FormDic.Keys)
//	{
//		if (m_UIAttrs.m_id2AttrDic[id].canUnloadUIBySceneType(unloadSceneType, loadSceneTpe))
//		{
//			m_tmpList.Add(id);
//		}
//	}
//
//	foreach(UIFormID id in m_tmpList)
//	{
//		exitForm(id, true);
//	}
//	m_tmpList.Clear();
//}