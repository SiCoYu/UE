#ifndef __UIFACTOREY_H
#define __UIFACTOREY_H

#include "FormID.h"

class FormBase;

class UIFactory
{
public:
	FormBase* createForm(FormID formID);
};

#endif				// __UIFACTOREY_H