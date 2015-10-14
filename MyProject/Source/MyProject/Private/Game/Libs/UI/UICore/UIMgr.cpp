#include "MyProject.h"
#include "UIMgr.h"
#include "FormBase.h"

UIMgr::UIMgr()
{
	
}

		public UIMgr()
		{
			m_dicForm = new Dictionary<UIFormID, Form>();
			m_UIAttrs = new UIAttrSystem();
			m_ID2CodeLoadingItemDic = new Dictionary<UIFormID, UILoadingItem>();
			m_ID2WidgetLoadingItemDic = new Dictionary<UIFormID, UILoadingItem>();

			createCanvas();
		}

		protected void createCanvas()
		{
			m_canvasList = new List<UICanvas>();
			int idx = 0;
			for (idx = 0; idx < (int)UICanvasID.eeCanvas_Total; ++idx)
			{
				m_canvasList.Add(new UICanvas((UICanvasID)idx));
			}

			m_canvasList[(int)UICanvasID.eCanvas_50].goName = NotDestroyPath.ND_CV_UICanvas_50;
			m_canvasList[(int)UICanvasID.eCanvas_100].goName = NotDestroyPath.ND_CV_UICanvas_100;
		}

		// ����ÿһ��Ķ���
		public void findCanvasGO()
		{
			int idx = 0;
			for (idx = 0; idx < (int)UICanvasID.eeCanvas_Total; ++idx)
			{
				m_canvasList[idx].findCanvasGO();
			}
		}

		//public void loadAndShow<T>(UIFormID ID) where T : Form, new()
		public void loadAndShow(UIFormID ID)
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
		public void showForm(UIFormID ID)
		{
			if (hasForm(ID))
			{
				showFormInternal(ID);
			}
		}

		public void showFormInternal(UIFormID ID)
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

		// ����һ�� UI
		private void hideFormInternal(UIFormID ID)
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

		// �˳�һ�� UI
		public void exitForm(UIFormID ID, bool bForce = false)
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

		protected void exitFormInternal(UIFormID ID)
		{
			Form win = getForm(ID);

			if (win != null)
			{
				// �����б�
				UILayer layer = win.uiLayer;
				layer.winDic.Remove(ID);
				// �ͷŽ�����Դ
				win.onExit();
				UtilApi.Destroy(win.m_GUIWin.m_uiRoot);
				win.m_GUIWin.m_uiRoot = null;
				// �ͷż��ص���Դ
				//string path = m_UIAttrs.getPath(ID);
				//if (path != null)
				//{
				//    Ctx.m_instance.m_resLoadMgr.unload(path);
				//}
				UtilApi.UnloadUnusedAssets();       // �첽ж�ع�����Դ
				m_dicForm.Remove(ID);
				win = null;
			}
		}

		public void addForm(Form form)
		{
			addFormNoReady(form);
			form.onInit();
		}

		public UILayer getLayer(UICanvasID canvasID, UILayerID layerID)
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

		// �ڲ��ӿ�
		private void addFormNoReady(Form form)
		{
			UILayer layer = getLayer(m_UIAttrs.m_dicAttr[form.id].m_canvasID, m_UIAttrs.m_dicAttr[form.id].m_LayerID);
			form.uiLayer = layer;
			layer.addForm(form);

			m_dicForm[form.id] = form;
			form.init();        // ��ʼ��
		}

		//public T getForm<T>(UIFormID ID) where T : Form
		public Form getForm(UIFormID ID)
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

		public bool hasForm(UIFormID ID)
		{
			return (m_dicForm.ContainsKey(ID));
		}

		// ����¼��ؽ�����Ҫ�Ĵ���
		//public void loadForm<T>(UIFormID ID) where T : Form, new()
		public void loadForm(UIFormID ID)
		{
			UIAttrItem attrItem = m_UIAttrs.m_dicAttr[ID];
			Form window = getForm(ID);

			if (window != null)     // �����Ѿ�������������ڣ�
			{
				if (window.IsResReady)      // �����ԴҲ�Ѿ����ؽ�����
				{
					if (null != Ctx.m_instance.m_cbUIEvent)
					{
						Ctx.m_instance.m_cbUIEvent.onCodeFormLoaded(window);  // ��Դ�������
					}
				}
			}
			else if (!m_ID2CodeLoadingItemDic.ContainsKey(ID))                       // ���ʲô��û�д�������һ�μ���
			{
				// ��������
				Form form = null;
				if (attrItem.m_bNeedLua)
				{
					form = new Form();
				}
				else
				{
					form = Ctx.m_instance.m_scriptDynLoad.getScriptObject(attrItem.m_scriptTypeName) as Form;
				}

				if (form != null)                   // ��������Ѿ��ڱ���
				{
					(form as Form).id = ID;
					if (attrItem.m_bNeedLua)
					{
						form.luaCSBridgeForm = new LuaCSBridgeForm(attrItem.m_luaScriptTableName, form);
						form.luaCSBridgeForm.DoFile(attrItem.m_luaScriptPath);
					}

					addFormNoReady(form);           // �����Ǵ������ݣ���Դ��û�м������
					onCodeLoadedByForm(form);
				}

				// ����ط�Ӧ���׳��쳣
				if (null == form)    // ����û�д���
				{
					m_ID2CodeLoadingItemDic[ID] = new UILoadingItem();
					m_ID2CodeLoadingItemDic[ID].m_ID = ID;

					loadFromFile(attrItem.m_codePath, onCodeLoadEventHandle);
				}
			}
		}

		// ���ش��ڿؼ���Դ��������Դ���Ǵ��ļ�����
		public void loadWidgetRes(UIFormID ID)
		{
			UIAttrItem attrItem = m_UIAttrs.m_dicAttr[ID];
			if (!m_ID2WidgetLoadingItemDic.ContainsKey(ID))                       // ���ʲô��û�д�������һ�μ���
			{
				m_ID2WidgetLoadingItemDic[ID] = new UILoadingItem();
				m_ID2WidgetLoadingItemDic[ID].m_ID = ID;

				loadFromFile(attrItem.m_widgetPath, onWidgetLoadEventHandle);
			}
		}

		// �ӱ��ش��̻������������Դ
		protected void loadFromFile(string reaPath, Action<IDispatchObject> onLoadEventHandle)
		{
			LoadParam param = Ctx.m_instance.m_poolSys.newObject<LoadParam>();
			LocalFileSys.modifyLoadParam(reaPath, param);
			param.m_loadNeedCoroutine = false;
			param.m_resNeedCoroutine = false;
			param.m_loadEventHandle = onLoadEventHandle;
			Ctx.m_instance.m_uiPrefabMgr.load<UIPrefabRes>(param);
			Ctx.m_instance.m_poolSys.deleteObj(param);
		}

		// ������Դ���ش���
		public void onCodeLoadEventHandle(IDispatchObject dispObj)
		{
			UIPrefabRes res = dispObj as UIPrefabRes;
			if (res.refCountResLoadResultNotify.resLoadState.hasSuccessLoaded())
			{
				onCodeloadedByRes(res);
			}
			else if (res.refCountResLoadResultNotify.resLoadState.hasFailed())
			{
				UIFormID ID = m_UIAttrs.GetFormIDByPath(res.GetPath(), ResPathType.ePathCodePath);  // ��ȡ FormID
				m_ID2CodeLoadingItemDic.Remove(ID);
			}
		}

		// ���ڿؼ���Դ���ش���
		public void onWidgetLoadEventHandle(IDispatchObject dispObj)
		{
			UIPrefabRes res = dispObj as UIPrefabRes;
			if (res.refCountResLoadResultNotify.resLoadState.hasSuccessLoaded())
			{
				onWidgetloadedByRes(res);
			}
			else if (res.refCountResLoadResultNotify.resLoadState.hasFailed())
			{
				UIFormID ID = m_UIAttrs.GetFormIDByPath(res.GetPath(), ResPathType.ePathComUI);  // ��ȡ FormID
				m_ID2WidgetLoadingItemDic.Remove(ID);
				Ctx.m_instance.m_logSys.log("UIFormID =  �� Failed Prefab");
			}
		}

		// ������Դ������ɴ���
		public void onCodeloadedByRes(UIPrefabRes res)
		{
			UIFormID ID = m_UIAttrs.GetFormIDByPath(res.GetPath(), ResPathType.ePathCodePath);  // ��ȡ FormID
			m_ID2CodeLoadingItemDic.Remove(ID);
			addFormNoReady(m_dicForm[ID]);
			onCodeLoadedByForm(m_dicForm[ID]);
		}

		protected void onCodeLoadedByForm(Form form)
		{
			if (null != Ctx.m_instance.m_cbUIEvent)
			{
				Ctx.m_instance.m_cbUIEvent.onCodeFormLoaded(form);  // ��Դ�������
			}
		}

		// ���ڿؼ���Դ������ɴ���
		public void onWidgetloadedByRes(UIPrefabRes res)
		{
			string path = res.GetPath();
			UIFormID ID = m_UIAttrs.GetFormIDByPath(path, ResPathType.ePathComUI);  // ��ȡ FormID
			m_ID2WidgetLoadingItemDic.Remove(ID);

			UIAttrItem attrItem = m_UIAttrs.m_dicAttr[ID];
			m_dicForm[ID].bLoadWidgetRes = true;
			m_dicForm[ID].m_GUIWin.m_uiRoot = res.InstantiateObject(attrItem.m_widgetPath);
			if (attrItem.m_bNeedLua)
			{
				m_dicForm[ID].luaCSBridgeForm.gameObject = m_dicForm[ID].m_GUIWin.m_uiRoot;
				m_dicForm[ID].luaCSBridgeForm.init();
			}

			// ����λ��
			UtilApi.SetParent(m_dicForm[ID].m_GUIWin.m_uiRoot.transform, m_canvasList[(int)attrItem.m_canvasID].layerList[(int)attrItem.m_LayerID].layerTrans, false);

			// ���������������ţ�������Ч
			m_dicForm[ID].m_GUIWin.m_uiRoot.transform.SetAsLastSibling();               // �������
			UtilApi.SetActive(m_dicForm[ID].m_GUIWin.m_uiRoot, false);      // ���� onShow �¼�
			//if (m_dicForm[ID].hideOnCreate)
			//{
			//    UtilApi.SetActive(m_dicForm[ID].m_GUIWin.m_uiRoot, false);
			//}
			if (!m_dicForm[ID].hideOnCreate)
			{
				showFormInternal(ID);   // ��� onShow �е��� exit �������ͻ���� m_dicForm �е����ݡ���������� exitMode = false���Ͳ������ m_dicForm ���Ͳ���������
			}

			if (null != Ctx.m_instance.m_cbUIEvent)
			{
				if (m_dicForm.ContainsKey(ID))      // ��� onShow �е��� exit ����������û������ exitMode = false ���ͻ���� m_dicForm�� ���ʱ���ٵ�������������ͻ������⣬�ǲ�������ӳ�ж��
				{
					Ctx.m_instance.m_cbUIEvent.onWidgetLoaded(m_dicForm[ID]);  // ��Դ�������
				}
			}

			// ж����Դ
			Ctx.m_instance.m_uiPrefabMgr.unload(path, onWidgetLoadEventHandle);
		}

		// ��С�����仯�󣬵��ô˺���
		public void onResize(int viewWidth, int viewHeight)
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

		// �ر�������ʾ�Ĵ���
		public void exitAllWin()
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

		public void findSceneUIRootGo()
		{
			m_sceneUIRootGo = UtilApi.GoFindChildByPObjAndName("SceneUIRootGo");
		}

		// ���ݳ�������ж�� UI��ǿ��ж��
		public void unloadUIBySceneType(UISceneType unloadSceneType, UISceneType loadSceneTpe)
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
	}