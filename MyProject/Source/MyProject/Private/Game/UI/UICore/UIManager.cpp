#include "MyProject.h"
#include "UIManager.h"
#include "UIFactory.h"

UIManager::UIManager()
{
	m_uiFactory = new UIFactory();
}

UFormBase* UIManager::loadForm(FormID formID)
{
	if (m_id2Form[formID] == nullptr)
	{
		m_id2Form[formID] = m_uiFactory->createForm(formID);
	}

	return m_id2Form[formID];
}
