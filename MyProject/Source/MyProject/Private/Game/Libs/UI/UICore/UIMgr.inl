template <class T>
UForm* UIMgr::loadForm(UIFormID formID)
{
	if (m_id2FormDic[formID] == nullptr)
	{
		// warning C4996: 'StaticConstructObject': StaticConstructObject is deprecated, please use NewObject instead. For internal CoreUObject module usage, please use StaticConstructObject_Internal. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile
		//m_id2Form[formID] = Cast<UFormBase>(StaticConstructObject(T::StaticClass()));
		m_id2FormDic[formID] = Cast<UForm>(NewObject<T>());
	}
	m_id2FormDic[formID]->onReady();
	return m_id2FormDic[formID];
}

template <class T>
T* UIMgr::getForm(UIFormID formID)
{
	return (T*)m_id2FormDic[formID];
}