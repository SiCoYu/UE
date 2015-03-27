#include "MyProject.h"
#include "UIManager.h"
#include "UIFactory.h"
#include "FormBase.h"

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
	m_id2Form[formID]->onReady();
	return m_id2Form[formID];
}
