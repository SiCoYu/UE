#include "EngineApi.h"

template <class T>
T* UIMgr::loadForm(UIFormId formID)
{
	if (nullptr == this->mId2FormDic[formID])
	{
		// warning C4996: 'StaticConstructObject': StaticConstructObject is deprecated, please use NewObject instead. For internal CoreUObject module usage, please use StaticConstructObject_Internal. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile
		//m_id2Form[formID] = Cast<UFormBase>(StaticConstructObject(T::StaticClass()));
		//mId2FormDic[formID] = Cast<UForm>(NewObject<T>());

		this->mId2FormDic[formID] = EngineApi::MNewObject<T>();
	}

	this->mId2FormDic[formID]->onReady();

	return Cast<T>(this->mId2FormDic[formID]);
}

template <class T>
T* UIMgr::getForm(UIFormId formID)
{
	return (T*)this->mId2FormDic[formID];
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
	}

	return retForm;
}