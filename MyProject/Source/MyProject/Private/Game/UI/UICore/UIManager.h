#ifndef __UIMANAGER_H
#define __UIMANAGER_H

#include <map>
#include "FormID.h"

class UFormBase;

class UIManager
{
protected:
	std::map<FormID, UFormBase*> m_id2Form;

public:
	UIManager();
	template <class T>
	UFormBase* loadForm(FormID formID);
};

template <class T>
UFormBase* UIManager::loadForm(FormID formID)
{
	if (m_id2Form[formID] == nullptr)
	{
		m_id2Form[formID] = Cast<UFormBase>(StaticConstructObject(T::StaticClass()));
	}
	m_id2Form[formID]->onReady();
	return m_id2Form[formID];
}

#endif				// __UIMANAGER_H