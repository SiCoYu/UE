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

// ����ÿһ��Ķ���
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

// ��ʾһ�� UI
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

// ����һ�� UI
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

// �˳�һ�� UI
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
		// �����б�
		UILayer* layer = win->getUiLayer();
		UtilMap::Remove(layer->getWinDic(), ID);
		// �ͷŽ�����Դ
		win->onExit();
		EngineApi::Destroy(win->m_GUIWin->m_uiRoot);
		win->m_GUIWin->m_uiRoot = nullptr;
		// �ͷż��ص���Դ
		//string path = m_UIAttrs.getPath(ID);
		//if (path != null)
		//{
		//    Ctx.m_instance.mResLoadMgr.unload(path);
		//}
		EngineApi::UnloadUnusedAssets();       // �첽ж�ع�����Դ
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

// �ڲ��ӿ�
void UIMgr::addFormNoReady(UForm* form)
{
	UILayer* layer = getLayer(m_UIAttrs->m_id2AttrDic[form->getID()]->m_canvasID, m_UIAttrs->m_id2AttrDic[form->getID()]->m_LayerID);
	form->setUiLayer(layer);
	layer->addForm(form);

	m_id2FormDic[form->getID()] = form;
	form->init();        // ��ʼ��
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

// ����¼��ؽ�����Ҫ�Ĵ���
void UIMgr::loadForm(UIFormID ID)
{
	UIAttrItem* attrItem = m_UIAttrs->m_id2AttrDic[ID];
	UForm* window = getForm(ID);

	if (window != nullptr)     // �����Ѿ�������������ڣ�
	{
		if (window->getIsResReady())      // �����ԴҲ�Ѿ����ؽ�����
		{
			//if (nullptr != Ctx.m_instance.m_cbUIEvent)
			//{
			//	Ctx.m_instance.m_cbUIEvent.onCodeFormLoaded(window);  // ��Դ�������
			//}
		}
	}
	else if (!UtilMap::ContainsKey(m_ID2CodeLoadingItemDic, ID))                       // ���ʲô��û�д�������һ�μ���
	{
		// ��������
		UForm* form = nullptr;
		//if (attrItem.m_bNeedLua)
		//{
		//	form = new Form();
		//}
		//else
		//{
		//	form = Ctx.m_instance.m_scriptDynLoad.getScriptObject(attrItem.m_scriptTypeName) as Form;
		//}

		if (form != nullptr)                   // ��������Ѿ��ڱ���
		{
			form->setID(ID);
			//if (attrItem.m_bNeedLua)
			//{
			//	form.luaCSBridgeForm = new LuaCSBridgeForm(attrItem.m_luaScriptTableName, form);
			//	form.luaCSBridgeForm.DoFile(attrItem.m_luaScriptPath);
			//}

			addFormNoReady(form);           // �����Ǵ������ݣ���Դ��û�м������
			onCodeLoadedByForm(form);
		}

		// ����ط�Ӧ���׳��쳣
		if (nullptr == form)    // ����û�д���
		{
			m_ID2CodeLoadingItemDic[ID] = new UILoadingItem();
			m_ID2CodeLoadingItemDic[ID]->m_ID = ID;

			loadFromFile(attrItem->m_codePath, EventDispatchDelegate(this, &UIMgr::onCodeLoadEventHandle));
		}
	}
}

// ���ش��ڿؼ���Դ��������Դ���Ǵ��ļ�����
void UIMgr::loadWidgetRes(UIFormID ID)
{
	UIAttrItem* attrItem = m_UIAttrs->m_id2AttrDic[ID];
	if (!UtilMap::ContainsKey(m_ID2WidgetLoadingItemDic, ID))                       // ���ʲô��û�д�������һ�μ���
	{
		m_ID2WidgetLoadingItemDic[ID] = new UILoadingItem();
		m_ID2WidgetLoadingItemDic[ID]->m_ID = ID;

		loadFromFile(attrItem->m_widgetPath, EventDispatchDelegate(this, &UIMgr::onWidgetLoadEventHandle));
	}
}

// �ӱ��ش��̻������������Դ
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

// ������Դ���ش���
void UIMgr::onCodeLoadEventHandle(IDispatchObject* dispObj)
{
	UIAssetRes* res = (UIAssetRes*)dispObj;
	if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
	{
		onCodeloadedByRes(res);
	}
	else if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasFailed())
	{
		UIFormID ID = m_UIAttrs->GetFormIDByPath(res->GetPath(), ePathCodePath);  // ��ȡ FormID
		UtilMap::Remove(m_ID2CodeLoadingItemDic, ID);
	}
}

// ���ڿؼ���Դ���ش���
void UIMgr::onWidgetLoadEventHandle(IDispatchObject* dispObj)
{
	UIAssetRes* res = (UIAssetRes*)dispObj;
	if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasSuccessLoaded())
	{
		onWidgetloadedByRes(res);
	}
	else if (res->getRefCountResLoadResultNotify()->getResLoadState()->hasFailed())
	{
		UIFormID ID = m_UIAttrs->GetFormIDByPath(res->GetPath(), ePathComUI);  // ��ȡ FormID
		UtilMap::Remove(m_ID2WidgetLoadingItemDic, ID);
		GLogSys->log("UIFormID =  �� Failed Prefab");
	}
}

// ������Դ������ɴ���
void UIMgr::onCodeloadedByRes(UIAssetRes* res)
{
	UIFormID ID = m_UIAttrs->GetFormIDByPath(res->GetPath(), ePathCodePath);  // ��ȡ FormID
	UtilMap::Remove(m_ID2CodeLoadingItemDic, ID);
	addFormNoReady(m_id2FormDic[ID]);
	onCodeLoadedByForm(m_id2FormDic[ID]);
}

void UIMgr::onCodeLoadedByForm(UForm* form)
{
	//if (null != Ctx.m_instance.m_cbUIEvent)
	//{
	//	Ctx.m_instance.m_cbUIEvent.onCodeFormLoaded(form);  // ��Դ�������
	//}
}

// ���ڿؼ���Դ������ɴ���
void UIMgr::onWidgetloadedByRes(UIAssetRes* res)
{
	std::string path = res->GetPath();
	UIFormID ID = m_UIAttrs->GetFormIDByPath(path, ePathComUI);  // ��ȡ FormID
	UtilMap::Remove(m_ID2WidgetLoadingItemDic, ID);

	UIAttrItem* attrItem = m_UIAttrs->m_id2AttrDic[ID];
	m_id2FormDic[ID]->setIsLoadWidgetRes(true);
	m_id2FormDic[ID]->m_GUIWin->m_uiRoot = Cast<UUserWidget>(res->InstantiateObject(attrItem->m_widgetPath));
	//if (attrItem.m_bNeedLua)
	//{
	//	m_id2FormDic[ID].luaCSBridgeForm.gameObject = m_id2FormDic[ID].m_GUIWin.m_uiRoot;
	//	m_id2FormDic[ID].luaCSBridgeForm.init();
	//}

	// ����λ��
	//EngineApi::SetParent(m_id2FormDic[ID]->m_GUIWin->m_uiRoot.transform, m_canvasList[(int)(attrItem->m_canvasID)]->getLayerList()[(int)(attrItem->m_LayerID)]->getLayerTrans(), false);

	// ���������������ţ�������Ч
	//m_id2FormDic[ID]->m_GUIWin->m_uiRoot.transform.SetAsLastSibling();               // �������
	EngineApi::SetActive(m_id2FormDic[ID]->m_GUIWin->m_uiRoot, false);      // ���� onShow �¼�
	//if (m_id2FormDic[ID].hideOnCreate)
	//{
	//    UtilApi.SetActive(m_id2FormDic[ID].m_GUIWin.m_uiRoot, false);
	//}
	if (!m_id2FormDic[ID]->getHideOnCreate())
	{
		showFormInternal(ID);   // ��� onShow �е��� exit �������ͻ���� m_id2FormDic �е����ݡ���������� exitMode = false���Ͳ������ m_id2FormDic ���Ͳ���������
	}

	//if (null != Ctx.m_instance.m_cbUIEvent)
	//{
	//	if (m_id2FormDic.ContainsKey(ID))      // ��� onShow �е��� exit ����������û������ exitMode = false ���ͻ���� m_id2FormDic�� ���ʱ���ٵ�������������ͻ������⣬�ǲ�������ӳ�ж��
	//	{
	//		Ctx.m_instance.m_cbUIEvent.onWidgetLoaded(m_id2FormDic[ID]);  // ��Դ�������
	//	}
	//}

	// ж����Դ
	GUiAssetMgr->unload(path, EventDispatchDelegate(this, &UIMgr::onWidgetLoadEventHandle));
}

// ��С�����仯�󣬵��ô˺���
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

// �ر�������ʾ�Ĵ���
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

// ���ݳ�������ж�� UI��ǿ��ж��
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