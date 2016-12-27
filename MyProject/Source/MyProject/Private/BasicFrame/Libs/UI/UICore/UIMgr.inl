#include "EngineApi.h"
#include "ClassAssetInsRes.h"
#include "Common.h"

//template <class T>
//T* UIMgr::loadForm(UIFormId formID)
//{
//	if (nullptr == this->mId2FormDic[formID])
//	{
//		// warning C4996: 'StaticConstructObject': StaticConstructObject is deprecated, please use NewObject instead. For internal CoreUObject module usage, please use StaticConstructObject_Internal. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile
//		//m_id2Form[formID] = Cast<UFormBase>(StaticConstructObject(T::StaticClass()));
//		//mId2FormDic[formID] = Cast<UForm>(NewObject<T>());
//
//		this->mId2FormDic[formID] = EngineApi::MNewObject<T>();
//	}
//
//	this->mId2FormDic[formID]->onReady();
//
//	return Cast<T>(this->mId2FormDic[formID]);
//}

// ����¼��ؽ�����Ҫ�Ĵ���
template <class T>
T* UIMgr::loadForm(UIFormId formId)
{
	UIAttrItem* attrItem = mUiAttrSystem->mId2AttrDic[formId];
	UForm* form = getForm<UForm>(formId);

	if (nullptr != form)     // �����Ѿ�������������ڣ�
	{
		if (form->getIsResReady())      // �����ԴҲ�Ѿ����ؽ�����
		{
			//if (nullptr != Ctx.m_instance.m_cbUIEvent)
			//{
			//	Ctx.m_instance.m_cbUIEvent.onCodeFormLoaded(window);  // ��Դ�������
			//}
		}
	}
	else if (!UtilMap::ContainsKey(mId2CodeLoadingItemDic, formId))                       // ���ʲô��û�д�������һ�μ���
	{
		//if (attrItem.m_bNeedLua)
		//{
		//	form = new Form();
		//}
		//else
		//{
		//	form = Ctx.m_instance.m_scriptDynLoad.getScriptObject(attrItem.m_scriptTypeName) as Form;
		//}

		//TSubclassOf<UUMGWidget> WidgetClass = EngineApi::FindClass<UUMGWidget>(*UtilStr::ConvStdStr2FString(attrItem->mWidgetPath));
		//UClass* WidgetClass = EngineApi::MLoadClass<UUMGWidget>(nullptr, *UtilStr::ConvStdStr2FString(attrItem->mWidgetPath));
		//UClass* WidgetClass = GMyStreamableManager->SynchronousLoadType<UClass>(attrItem->mWidgetPath);

		//this->loadFromFile("WidgetBlueprint'/Game/MyAsset/Blueprints/Umg/UITestUMG/NewWidgetBlueprint2.NewWidgetBlueprint2_C'", EventDispatchDelegate(this, &UIMgr::onWidgetLoadEventHandle));

		ClassAssetInsRes* asset = GClassAssetInsMgr->getAndSyncLoadClass(attrItem->mWidgetPath);
		UClass* WidgetClass = asset->getObject();

		UUMGWidget* WidgetObject = nullptr;

		if (NSFormType::eWorld == attrItem->mUMGOuterType)
		{

		}
		else if (NSFormType::ePlayerController == attrItem->mUMGOuterType)
		{
			WidgetObject = EngineApi::MCreateWidget<UUMGWidget>(GEngineData->getMainPlayerController(), WidgetClass);
		}
		else if (NSFormType::eGameInstance == attrItem->mUMGOuterType)
		{

		}

		WidgetObject->AddToViewport();
		form = EngineApi::MNewObject<T>();

		if (nullptr != form)                   // ��������Ѿ��ڱ���
		{
			form->setId(formId);
			//if (attrItem.m_bNeedLua)
			//{
			//	form.luaCSBridgeForm = new LuaCSBridgeForm(attrItem.m_luaScriptTableName, form);
			//	form.luaCSBridgeForm.DoFile(attrItem.m_luaScriptPath);
			//}

			form->mGuiWin->mUiRoot = WidgetObject;

			addFormNoReady(form);           // �����Ǵ������ݣ���Դ��û�м������
			//onCodeLoadedByForm(form);
		}
	}

	return Cast<T>(form);
}

template <class T>
T* UIMgr::getForm(UIFormId formId)
{
	if (UtilMap::ContainsKey(mId2FormDic, formId))
	{
		return Cast<T>(mId2FormDic[formId]);
	}
	else
	{
		return nullptr;
	}
}

template <class T>
T*  UIMgr::loadAndShow(UIFormId formId)
{
	T* retForm = nullptr;

	if (this->hasForm(formId))
	{
		this->showFormInternal(formId);
		retForm = this->getForm<T>(formId);
	}
	else
	{
		retForm = this->loadForm<T>(formId);
		this->showForm(formId);
	}

	return retForm;
}