#ifndef __UIMANAGER_H
#define __UIMANAGER_H

#include <map>
#include "FormID.h"
#include "IUIManager.h"

class FormBase;
class UIFactory;

class UIManager : public IUIManager
{
protected:
	std::map<FormID, FormBase*> m_id2Form;
	UIFactory* m_uiFactory;

public:
	UIManager();
	virtual FormBase* loadForm(FormID formID);
};

#endif				// __UIMANAGER_H