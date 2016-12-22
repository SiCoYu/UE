template <class T>
UForm* UIMgr::loadForm(UIFormId formID)
{
	if (mId2FormDic[formID] == nullptr)
	{
		// warning C4996: 'StaticConstructObject': StaticConstructObject is deprecated, please use NewObject instead. For internal CoreUObject module usage, please use StaticConstructObject_Internal. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile
		//m_id2Form[formID] = Cast<UFormBase>(StaticConstructObject(T::StaticClass()));
		mId2FormDic[formID] = Cast<UForm>(NewObject<T>());
	}
	mId2FormDic[formID]->onReady();
	return mId2FormDic[formID];
}

template <class T>
T* UIMgr::getForm(UIFormId formID)
{
	return (T*)mId2FormDic[formID];
}