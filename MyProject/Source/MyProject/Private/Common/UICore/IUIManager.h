#ifndef __IUIMANAGER_H
#define __IUIMANAGER_H

class FormBase;
enum FormID;

class IUIManager
{
public:
	virtual FormBase* loadForm(FormID formID) = 0;
};

#endif				// __IUIMANAGER_H