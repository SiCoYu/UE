#ifndef __UIMANAGER_H
#define __UIMANAGER_H

#include <map>
#include "FormID.h"

class UIFormBase;
class UIFactory;

class UIManager : public IUIManager
{
protected:
	std::map<FormID, FormBase*> m_id2Form;
	UIFactory* m_uiFactory;

public:
	UIManager();
	FormBase* loadForm(FormID formID);
};

#endif				// __UIMANAGER_H