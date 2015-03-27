#ifndef __IUIMANAGER_H
#define __IUIMANAGER_H

class UFormBase;
enum FormID;

class IUIManager
{
public:
	virtual UFormBase* loadForm(FormID formID) = 0;
};

#endif				// __IUIMANAGER_H