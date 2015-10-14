#include "MyProject.h"
#include "UIMgr.h"
#include "FormBase.h"
#include "UIAttrSystem.h"
#include "UICanvas.h"
#include "UIFormID.h"

UIMgr::UIMgr()
{
	m_UIAttrs = new UIAttrSystem();
	createCanvas();
}

void UIMgr::createCanvas()
{
	int idx = 0;
	for (idx = 0; idx < (int)UICanvasID::eCanvas_Total; ++idx)
	{
		m_canvasList.push_back(new UICanvas((UICanvasID)idx));
	}

	m_canvasList[(int)UICanvasID.eCanvas_50].goName = NotDestroyPath.ND_CV_UICanvas_50;
	m_canvasList[(int)UICanvasID.eCanvas_100].goName = NotDestroyPath.ND_CV_UICanvas_100;
}

// 关联每一层的对象
void UIMgr::findCanvasGO()
{
	int idx = 0;
	for (idx = 0; idx < (int)UICanvasID::eCanvas_Total; ++idx)
	{
		m_canvasList[idx].findCanvasGO();
	}
}

void UIMgr::loadAndShow(UIFormID::UIFormID ID)
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
void UIMgr::showForm(UIFormID::UIFormID ID)
{
	if (hasForm(ID))
	{
		showFormInternal(ID);
	}
}

void UIMgr::showFormInternal(UIFormID::UIFormID ID)
{
	Form win = getForm(ID);
	if (win != null)
	{
		if (!win.bReady)
		{
			win.onReady();
		}
		if (!win.IsVisible())
		{
			UtilApi.SetActive(win.m_GUIWin.m_uiRoot, true);
			win.onShow();
		}
	}
}

// 隐藏一个 UI
void UIMgr::hideFormInternal(UIFormID::UIFormID ID)
{
	Form win = getForm(ID);
	if (win != null)
	{
		if (win.IsVisible())
		{
			UtilApi.SetActive(win.m_GUIWin.m_uiRoot, false);
			win.onHide();
		}
	}
}

// 退出一个 UI
void UIMgr::exitForm(UIFormID::UIFormID ID, bool bForce = false)
{
	Form win = getForm(ID);

	if (win != null)
	{
		if (win.exitMode || bForce)
		{
			exitFormInternal(ID);
		}
		else
		{
			hideFormInternal(ID);
		}
	}
}

void UIMgr::exitFormInternal(UIFormID::UIFormID ID)
{
	Form win = getForm(ID);

	if (win != null)
	{
		// 清理列表
		UILayer layer = win.uiLayer;
		layer.winDic.Remove(ID);
		// 释放界面资源
		win.onExit();
		UtilApi.Destroy(win.m_GUIWin.m_uiRoot);
		win.m_GUIWin.m_uiRoot = null;
		// 释放加载的资源
		//string path = m_UIAttrs.getPath(ID);
		//if (path != null)
		//{
		//    Ctx.m_instance.m_resLoadMgr.unload(path);
		//}
		UtilApi.UnloadUnusedAssets();       // 异步卸载共用资源
		m_dicForm.Remove(ID);
		win = null;
	}
}

void UIMgr::addForm(Form form)
{
	addFormNoReady(form);
	form.onInit();
}

UILayer UIMgr::getLayer(UICanvasID::UICanvasID canvasID, UILayerID::UILayerID layerID)
{
	UILayer layer = null;

	if (UICanvasID.eCanvas_50 <= canvasID && canvasID <= UICanvasID.eCanvas_100)
	{
		if (UILayerID.eBtmLayer <= layerID && layerID <= UILayerID.eTopLayer)
		{
			layer = m_canvasList[(int)canvasID].layerList[(int)layerID];
		}
	}

	return layer;
}

// 内部接口
void UIMgr::addFormNoReady(Form form)
{
	UILayer layer = getLayer(m_UIAttrs.m_dicAttr[form.id].m_canvasID, m_UIAttrs.m_dicAttr[form.id].m_LayerID);
	form.uiLayer = layer;
	layer.addForm(form);

	m_dicForm[form.id] = form;
	form.init();        // 初始化
}

Form UIMgr::getForm(UIFormID::UIFormID ID)
{
	if (m_dicForm.ContainsKey(ID))
	{
		return m_dicForm[ID];
	}
	else
	{
		return null;
	}
}

bool UIMgr::hasForm(UIFormID::UIFormID ID)
{
	return (m_dicForm.ContainsKey(ID));
}

// 这个事加载界面需要的代码
void UIMgr::loadForm(UIFormID::UIFormID ID)
{
	UIAttrItem attrItem = m_UIAttrs.m_dicAttr[ID];
	Form window = getForm(ID);

	if (window != null)     // 本地已经创建了这个窗口，
	{
		if (window.IsResReady)      // 如果资源也已经加载进来了
		{
			if (null != Ctx.m_instance.m_cbUIEvent)
			{
				Ctx.m_instance.m_cbUIEvent.onCodeFormLoaded(window);  // 资源加载完成
			}
		}
	}
	else if (!m_ID2CodeLoadingItemDic.ContainsKey(ID))                       // 如果什么都没有创建，第一次加载
	{
		// 创建窗口
		Form form = null;
		if (attrItem.m_bNeedLua)
		{
			form = new Form();
		}
		else
		{
			form = Ctx.m_instance.m_scriptDynLoad.getScriptObject(attrItem.m_scriptTypeName) as Form;
		}

		if (form != null)                   // 如果代码已经在本地
		{
			(form as Form).id = ID;
			if (attrItem.m_bNeedLua)
			{
				form.luaCSBridgeForm = new LuaCSBridgeForm(attrItem.m_luaScriptTableName, form);
				form.luaCSBridgeForm.DoFile(attrItem.m_luaScriptPath);
			}

			addFormNoReady(form);           // 仅仅是创建数据，资源还没有加载完成
			onCodeLoadedByForm(form);
		}

		// 这个地方应该抛出异常
		if (null == form)    // 本地没有代码
		{
			m_ID2CodeLoadingItemDic[ID] = new UILoadingItem();
			m_ID2CodeLoadingItemDic[ID].m_ID = ID;

			loadFromFile(attrItem.m_codePath, onCodeLoadEventHandle);
		}
	}
}

// 加载窗口控件资源，窗口资源都是从文件加载
void UIMgr::loadWidgetRes(UIFormID::UIFormID ID)
{
	UIAttrItem attrItem = m_UIAttrs.m_dicAttr[ID];
	if (!m_ID2WidgetLoadingItemDic.ContainsKey(ID))                       // 如果什么都没有创建，第一次加载
	{
		m_ID2WidgetLoadingItemDic[ID] = new UILoadingItem();
		m_ID2WidgetLoadingItemDic[ID].m_ID = ID;

		loadFromFile(attrItem.m_widgetPath, onWidgetLoadEventHandle);
	}
}

// 从本地磁盘或者网络加载资源
void UIMgr::loadFromFile(string reaPath, Action<IDispatchObject> onLoadEventHandle)
{
	LoadParam param = Ctx.m_instance.m_poolSys.newObject<LoadParam>();
	LocalFileSys.modifyLoadParam(reaPath, param);
	param.m_loadNeedCoroutine = false;
	param.m_resNeedCoroutine = false;
	param.m_loadEventHandle = onLoadEventHandle;
	Ctx.m_instance.m_uiPrefabMgr.load<UIPrefabRes>(param);
	Ctx.m_instance.m_poolSys.deleteObj(param);
}

// 代码资源加载处理
void UIMgr::onCodeLoadEventHandle(IDispatchObject dispObj)
{
	UIPrefabRes res = dispObj as UIPrefabRes;
	if (res.refCountResLoadResultNotify.resLoadState.hasSuccessLoaded())
	{
		onCodeloadedByRes(res);
	}
	else if (res.refCountResLoadResultNotify.resLoadState.hasFailed())
	{
		UIFormID ID = m_UIAttrs.GetFormIDByPath(res.GetPath(), ResPathType.ePathCodePath);  // 获取 FormID
		m_ID2CodeLoadingItemDic.Remove(ID);
	}
}

// 窗口控件资源加载处理
void UIMgr::onWidgetLoadEventHandle(IDispatchObject dispObj)
{
	UIPrefabRes res = dispObj as UIPrefabRes;
	if (res.refCountResLoadResultNotify.resLoadState.hasSuccessLoaded())
	{
		onWidgetloadedByRes(res);
	}
	else if (res.refCountResLoadResultNotify.resLoadState.hasFailed())
	{
		UIFormID ID = m_UIAttrs.GetFormIDByPath(res.GetPath(), ResPathType.ePathComUI);  // 获取 FormID
		m_ID2WidgetLoadingItemDic.Remove(ID);
		Ctx.m_instance.m_logSys.log("UIFormID =  ， Failed Prefab");
	}
}

// 代码资源加载完成处理
void UIMgr::onCodeloadedByRes(UIPrefabRes res)
{
	UIFormID ID = m_UIAttrs.GetFormIDByPath(res.GetPath(), ResPathType.ePathCodePath);  // 获取 FormID
	m_ID2CodeLoadingItemDic.Remove(ID);
	addFormNoReady(m_dicForm[ID]);
	onCodeLoadedByForm(m_dicForm[ID]);
}

void UIMgr::onCodeLoadedByForm(Form form)
{
	if (null != Ctx.m_instance.m_cbUIEvent)
	{
		Ctx.m_instance.m_cbUIEvent.onCodeFormLoaded(form);  // 资源加载完成
	}
}

// 窗口控件资源加载完成处理
void onWidgetloadedByRes(UIPrefabRes res)
{
	string path = res.GetPath();
	UIFormID ID = m_UIAttrs.GetFormIDByPath(path, ResPathType.ePathComUI);  // 获取 FormID
	m_ID2WidgetLoadingItemDic.Remove(ID);

	UIAttrItem attrItem = m_UIAttrs.m_dicAttr[ID];
	m_dicForm[ID].bLoadWidgetRes = true;
	m_dicForm[ID].m_GUIWin.m_uiRoot = res.InstantiateObject(attrItem.m_widgetPath);
	if (attrItem.m_bNeedLua)
	{
		m_dicForm[ID].luaCSBridgeForm.gameObject = m_dicForm[ID].m_GUIWin.m_uiRoot;
		m_dicForm[ID].luaCSBridgeForm.init();
	}

	// 设置位置
	UtilApi.SetParent(m_dicForm[ID].m_GUIWin.m_uiRoot.transform, m_canvasList[(int)attrItem.m_canvasID].layerList[(int)attrItem.m_LayerID].layerTrans, false);

	// 先设置再设置缩放，否则无效
	m_dicForm[ID].m_GUIWin.m_uiRoot.transform.SetAsLastSibling();               // 放在最后
	UtilApi.SetActive(m_dicForm[ID].m_GUIWin.m_uiRoot, false);      // 出发 onShow 事件
	//if (m_dicForm[ID].hideOnCreate)
	//{
	//    UtilApi.SetActive(m_dicForm[ID].m_GUIWin.m_uiRoot, false);
	//}
	if (!m_dicForm[ID].hideOnCreate)
	{
		showFormInternal(ID);   // 如果 onShow 中调用 exit 函数，就会清掉 m_dicForm 中的内容。如果设置了 exitMode = false，就不会清掉 m_dicForm ，就不会有问题
	}

	if (null != Ctx.m_instance.m_cbUIEvent)
	{
		if (m_dicForm.ContainsKey(ID))      // 如果 onShow 中调用 exit 函数，并且没有设置 exitMode = false ，就会清除 m_dicForm， 这个时候再调用这个函数，就会有问题，是不是添加延迟卸载
		{
			Ctx.m_instance.m_cbUIEvent.onWidgetLoaded(m_dicForm[ID]);  // 资源加载完成
		}
	}

	// 卸载资源
	Ctx.m_instance.m_uiPrefabMgr.unload(path, onWidgetLoadEventHandle);
}

// 大小发生变化后，调用此函数
void UIMgr::onResize(int viewWidth, int viewHeight)
{
	int canvasIdx = 0;
	int layerIdx = 0;
	for (canvasIdx = 0; canvasIdx < (int)UICanvasID.eeCanvas_Total; ++canvasIdx)
	{
		for (layerIdx = 0; layerIdx <= (int)UILayerID.eMaxLayer; ++layerIdx)
		{
			m_canvasList[canvasIdx].layerList[layerIdx].onStageReSize();
		}
	}
}

// 关闭所有显示的窗口
void UIMgr::exitAllWin()
{
	foreach(UIFormID id in m_dicForm.Keys)
	{
		m_tmpList.Add(id);
	}

	foreach(UIFormID id in m_tmpList)
	{
		exitForm(id);
	}
	m_tmpList.Clear();
}

void UIMgr::findSceneUIRootGo()
{
	m_sceneUIRootGo = UtilApi.GoFindChildByPObjAndName("SceneUIRootGo");
}

// 根据场景类型卸载 UI，强制卸载
void UIMgr::unloadUIBySceneType(UISceneType unloadSceneType, UISceneType loadSceneTpe)
{
	foreach(UIFormID id in m_dicForm.Keys)
	{
		if (m_UIAttrs.m_dicAttr[id].canUnloadUIBySceneType(unloadSceneType, loadSceneTpe))
		{
			m_tmpList.Add(id);
		}
	}

	foreach(UIFormID id in m_tmpList)
	{
		exitForm(id, true);
	}
	m_tmpList.Clear();
}