#ifndef __UIMANAGER_H
#define __UIMANAGER_H

#include <map>
#include "FormID.h"
#include "IUIManager.h"

class UFormBase;
class UIFactory;

class UIManager : public IUIManager
{
protected:
	std::map<FormID, UFormBase*> m_id2Form;
	UIFactory* m_uiFactory;

public:
	UIManager();
	virtual UFormBase* loadForm(FormID formID);
};

#endif				// __UIMANAGER_H