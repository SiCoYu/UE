#ifndef __UiMgr_H
#error "UiMgr.inl file can only include in UiMgr.h"
#endif

#include "UtilEngineWrap.h"
#include "ClassAssetInsRes.h"
#include "Prequisites.h"

MY_BEGIN_NAMESPACE(MyNS)

//template <class T>
//T* UiMgr::loadForm(enum UiFormId formId)
//{
//	if (nullptr == this->mId2FormDic[formId])
//	{
//		// warning C4996: 'StaticConstructObject': StaticConstructObject is deprecated, please use NewObject instead. For internal CoreUObject module usage, please use StaticConstructObject_Internal. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile
//		//m_id2Form[formId] = Cast<UFormBase>(StaticConstructObject(T::StaticClass()));
//		//mId2FormDic[formId] = Cast<UForm>(NewObject<T>());
//
//		this->mId2FormDic[formId] = UtilEngineWrap::MNewObject<T>();
//	}
//
//	this->mId2FormDic[formId]->onReady();
//
//	return Cast<T>(this->mId2FormDic[formId]);
//}

// ����¼��ؽ�����Ҫ�Ĵ���
template <class T>
T* UiMgr::loadForm(UiFormId formId)
{
	//UiAttrItem* attrItem = this->mUiAttrSystem->mId2AttrDic[formId];

	//if (attrItem.m_bNeedLua)
	//{
	//	form = new Form();
	//}
	//else
	//{
	//	form = Ctx.m_instance.m_scriptDynLoad.getScriptObject(attrItem.m_scriptTypeName) as Form;
	//}

	//TSubclassOf<UUMGWidget> WidgetClass = UtilEngineWrap::FindClass<UUMGWidget>(*UtilStr::ConvStdStr2FString(attrItem->mWidgetPath));
	//UClass* WidgetClass = UtilEngineWrap::MLoadClass<UUMGWidget>(nullptr, *UtilStr::ConvStdStr2FString(attrItem->mWidgetPath));
	//UClass* WidgetClass = GMyStreamableManager->SynchronousLoadType<UClass>(attrItem->mWidgetPath);

	//this->loadFromFile("WidgetBlueprint'/Game/MyAsset/Blueprints/Umg/UITestUMG/UITestUMG2.UITestUMG2_C'", MakeEventDispatchDelegate(this, &UiMgr::onWidgetLoadEventHandle));

	//ClassAssetInsRes* asset = GClassAssetInsMgr->getAndSyncLoadClass(attrItem->mWidgetPath);
	//UClass* WidgetClass = asset->getClass();

	//UUMGWidget* WidgetObject = nullptr;

	//if (UMGOuterType::eWorld == attrItem->mUMGOuterType)
	//{

	//}
	//else if (UMGOuterType::ePlayerController == attrItem->mUMGOuterType)
	//{
	//	WidgetObject = UtilEngineWrap::CreateWidget<UUMGWidget>(GEngineData->getMainPlayerController(), WidgetClass);
	//}
	//else if (UMGOuterType::eGameInstance == attrItem->mUMGOuterType)
	//{

	//}

	//WidgetObject->AddToViewport();

	UForm* form = NULL;

	form = UtilEngineWrap::NewObject<T>();

	if (nullptr != form)                   // ��������Ѿ��ڱ���
	{
		form->setId(formId);

		//if (attrItem.m_bNeedLua)
		//{
		//	form.luaCSBridgeForm = new LuaCSBridgeForm(attrItem.m_luaScriptTableName, form);
		//	form.luaCSBridgeForm.DoFile(attrItem.m_luaScriptPath);
		//}

		//form->mWinRender->mUiRoot = WidgetObject;

		this->addFormNoReady(form);           // �����Ǵ������ݣ���Դ��û�м������
		//onCodeLoadedByForm(form);

		// Ĭ�ϻ����������Դ
		this->loadWidgetRes(formId);
	}

	return Cast<T>(form);
}

template <class T>
T* UiMgr::getForm(UiFormId formId)
{
	// T* ret = nullptr;
	T* ret = NULL;

	if (this->mId2FormDic.containsKey(formId))
	{
		// Error
		// Engine\Source\Runtime\CoreUObject\Private\UObject\UObjectBaseUtility.cpp
		// bool UObjectBaseUtility::IsA( const UClass* SomeBase ) const
		// Cast<T>(0); ������崻���ע��
		UForm* form = this->mId2FormDic[formId];

		MY_ASSERT(form->IsA(UForm::GetClass()));

		ret = Cast<T>(form);
	}

	return ret;
}

template <class T>
T*  UiMgr::loadAndShow(UiFormId formId)
{
	T* retForm = nullptr;

	if (this->hasForm(formId))
	{
		this->_showFormInternal(formId);
		retForm = this->getForm<T>(formId);
	}
	else
	{
		retForm = this->loadForm<T>(formId);
		this->showForm(formId);
	}

	return retForm;
}

MY_END_NAMESPACE