#ifndef __UIMANAGER_H
#define __UIMANAGER_H

#include <map>
#include "UIFormID.h"

class UFormBase;

class UIManager
{
protected:
	std::map<UIFormID, UFormBase*> m_id2Form;

public:
	UIManager();
	template <class T>
	UFormBase* loadForm(UIFormID formID);

	template <class T>
	T* getForm(UIFormID formID);
};

template <class T>
UFormBase* UIManager::loadForm(UIFormID formID)
{
	if (m_id2Form[formID] == nullptr)
	{
		m_id2Form[formID] = Cast<UFormBase>(StaticConstructObject(T::StaticClass()));
	}
	m_id2Form[formID]->onReady();
	return m_id2Form[formID];
}

template <class T>
T* UIManager::getForm(UIFormID formID)
{
	return (T*)m_id2Form[formID];
}

#endif				// __UIMANAGER_H