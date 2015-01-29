#ifndef __UMGFORM_H
#define __UMGFORM_H

#include "MyProject.h"
#include "FormBase.h"

class UUserWidget;

class UMGForm : public FormBase
{
protected:
	UUserWidget* m_umgWidget;

protected:
	void loadUWidget(const TCHAR* name);
};

#endif				// __UMGFORM_H