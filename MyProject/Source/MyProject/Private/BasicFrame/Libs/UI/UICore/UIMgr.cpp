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
	mUiAttrs = new UIAttrSystem();
	createCanvas();
}

void UIMgr::createCanvas()
{
	int idx = 0;
	for (idx = 0; idx < (int)eCanvas_Total; ++idx)
	{
		mCanvasList.push_back(new UICanvas((UICanvasID)idx));
	}

	mCanvasList[(int)eCanvas_50]->setGoName(NotDestroyPath::ND_CV_UICanvas_50);
	mCanvasList[(int)eCanvas_100]->setGoName(NotDestroyPath::ND_CV_UICanvas_100);
}

// ����ÿһ��Ķ���
void UIMgr::findCanvasGO()
{
	int idx = 0;
	for (idx = 0; idx < (int)eCanvas_Total; ++idx)
	{
		mCanvasList[idx]->findCanvasGO();
	}
}

void UIMgr::loadAndShow(UIFormId ID)
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
void UIMgr::showForm(UIFormId ID)
{
	if (hasForm(ID))
	{
		showFormInternal(ID);
	}
}

void UIMgr::showFormInternal(UIFormId ID)
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
			EngineApi::SetActive(win->mGuiWin->mUiRoot, true);
			win->onShow();
		}
	}
}

// ����һ�� UI
void UIMgr::hideFormInternal(UIFormId ID)
{
	UForm* win = getForm(ID);
	if (win != nullptr)
	{
		if (win->IsVisible())
		{
			EngineApi::SetActive(win->mGuiWin->mUiRoot, false);
			win->onHide();
		}
	}
}

// �˳�һ�� UI
void UIMgr::exitForm(UIFormId ID, bool bForce)
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

void UIMgr::exitFormInternal(UIFormId ID)
{
	UForm* win = getForm(ID);

	if (win != nullptr)
	{
		// �����б�
		UILayer* layer = win->getUiLayer();
		UtilMap::Remove(layer->getWinDic(), ID);
		// �ͷŽ�����Դ
		win->onExit();
		EngineApi::Destroy(win->mGuiWin->mUiRoot);
		win->mGuiWin->mUiRoot = nullptr;
		// �ͷż��ص���Դ
		//string path = mUiAttrs.getPath(ID);
		//if (path != null)
		//{
		//    Ctx.m_instance.mResLoadMgr.unload(path);
		//}
		EngineApi::UnloadUnusedAssets();       // �첽ж�ع�����Դ
		UtilMap::Remove(mId2FormDic, ID);
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
			layer = mCanvasList[(int)canvasID]->getLayerList()[(int)layerID];
		}
	}

	return layer;
}

// �ڲ��ӿ�
void UIMgr::addFormNoReady(UForm* form)
{
	UILayer* layer = getLayer(mUiAttrs->mId2AttrDic[form->getID()]->mCanvasId, mUiAttrs->mId2AttrDic[form->getID()]->mLayerId);
	form->setUiLayer(layer);
	layer->addForm(form);

	mId2FormDic[form->getID()] = form;
	form->init();        // ��ʼ��
}

UForm* UIMgr::getForm(UIFormId ID)
{
	if (UtilMap::ContainsKey(mId2FormDic, ID))
	{
		return mId2FormDic[ID];
	}
	else
	{
		return nullptr;
	}
}

bool UIMgr::hasForm(UIFormId ID)
{
	return UtilMap::ContainsKey(mId2FormDic, ID);
}

// ����¼��ؽ�����Ҫ�Ĵ���
void UIMgr::loadForm(UIFormId ID)
{
	UIAttrItem* attrItem = mUiAttrs->mId2AttrDic[ID];
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
	else if (!UtilMap::ContainsKey(mId2CodeLoadingItemDic, ID))                       // ���ʲô��û�д�������һ�μ���
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
			mId2CodeLoadingItemDic[ID] = new UILoadingItem();
			mId2CodeLoadingItemDic[ID]->mId = ID;

			loadFromFile(attrItem->mCodePath, EventDispatchDelegate(this, &UIMgr::onCodeLoadEventHandle));
		}
	}
}

// ���ش��ڿؼ���Դ��������Դ���Ǵ��ļ�����
void UIMgr::loadWidgetRes(UIFormId ID)
{
	UIAttrItem* attrItem = mUiAttrs->mId2AttrDic[ID];
	if (!UtilMap::ContainsKey(mId2WidgetLoadingItemDic, ID))                       // ���ʲô��û�д�������һ�μ���
	{
		mId2WidgetLoadingItemDic[ID] = new UILoadingItem();
		mId2WidgetLoadingItemDic[ID]->mId = ID;

		loadFromFile(attrItem->mWidgetPath, EventDispatchDelegate(this, &UIMgr::onWidgetLoadEventHandle));
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
		UIFormId ID = mUiAttrs->GetFormIDByPath(res->GetPath(), ePathCodePath);  // ��ȡ FormID
		UtilMap::Remove(mId2CodeLoadingItemDic, ID);
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
		UIFormId ID = mUiAttrs->GetFormIDByPath(res->GetPath(), ePathComUI);  // ��ȡ FormID
		UtilMap::Remove(mId2WidgetLoadingItemDic, ID);
		GLogSys->log("UIFormId =  �� Failed Prefab");
	}
}

// ������Դ������ɴ���
void UIMgr::onCodeloadedByRes(UIAssetRes* res)
{
	UIFormId ID = mUiAttrs->GetFormIDByPath(res->GetPath(), ePathCodePath);  // ��ȡ FormID
	UtilMap::Remove(mId2CodeLoadingItemDic, ID);
	addFormNoReady(mId2FormDic[ID]);
	onCodeLoadedByForm(mId2FormDic[ID]);
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
	UIFormId ID = mUiAttrs->GetFormIDByPath(path, ePathComUI);  // ��ȡ FormID
	UtilMap::Remove(mId2WidgetLoadingItemDic, ID);

	UIAttrItem* attrItem = mUiAttrs->mId2AttrDic[ID];
	mId2FormDic[ID]->setIsLoadWidgetRes(true);
	mId2FormDic[ID]->mGuiWin->mUiRoot = Cast<UUserWidget>(res->InstantiateObject(attrItem->mWidgetPath));
	//if (attrItem.m_bNeedLua)
	//{
	//	mId2FormDic[ID].luaCSBridgeForm.gameObject = mId2FormDic[ID].mGuiWin.mUiRoot;
	//	mId2FormDic[ID].luaCSBridgeForm.init();
	//}

	// ����λ��
	//EngineApi::SetParent(mId2FormDic[ID]->mGuiWin->mUiRoot.transform, mCanvasList[(int)(attrItem->mCanvasId)]->getLayerList()[(int)(attrItem->mLayerId)]->getLayerTrans(), false);

	// ���������������ţ�������Ч
	//mId2FormDic[ID]->mGuiWin->mUiRoot.transform.SetAsLastSibling();               // �������
	EngineApi::SetActive(mId2FormDic[ID]->mGuiWin->mUiRoot, false);      // ���� onShow �¼�
	//if (mId2FormDic[ID].hideOnCreate)
	//{
	//    UtilApi.SetActive(mId2FormDic[ID].mGuiWin.mUiRoot, false);
	//}
	if (!mId2FormDic[ID]->getHideOnCreate())
	{
		showFormInternal(ID);   // ��� onShow �е��� exit �������ͻ���� mId2FormDic �е����ݡ���������� exitMode = false���Ͳ������ mId2FormDic ���Ͳ���������
	}

	//if (null != Ctx.m_instance.m_cbUIEvent)
	//{
	//	if (mId2FormDic.ContainsKey(ID))      // ��� onShow �е��� exit ����������û������ exitMode = false ���ͻ���� mId2FormDic�� ���ʱ���ٵ�������������ͻ������⣬�ǲ�������ӳ�ж��
	//	{
	//		Ctx.m_instance.m_cbUIEvent.onWidgetLoaded(mId2FormDic[ID]);  // ��Դ�������
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
			mCanvasList[canvasIdx]->getLayerList()[layerIdx]->onStageReSize();
		}
	}
}

// �ر�������ʾ�Ĵ���
void UIMgr::exitAllWin()
{
	for(std::pair<UIFormId, UForm*> keyValue : mId2FormDic)
	{
		mTmpList.Add(keyValue.first);
	}

	for(UIFormId id : mTmpList.getList())
	{
		exitForm(id);
	}
	mTmpList.Clear();
}

void UIMgr::findSceneUIRootGo()
{
	//mSceneUIRootGo = UtilApi.GoFindChildByPObjAndName("SceneUIRootGo");
}

// ���ݳ�������ж�� UI��ǿ��ж��
//void UIMgr::unloadUIBySceneType(UISceneType unloadSceneType, UISceneType loadSceneTpe)
//{
//	foreach(UIFormId id in mId2FormDic.Keys)
//	{
//		if (mUiAttrs.mId2AttrDic[id].canUnloadUIBySceneType(unloadSceneType, loadSceneTpe))
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