#ifndef __UIFACTOREY_H
#define __UIFACTOREY_H

#include "FormID.h"

class UFormBase;

class UIFactory
{
public:
	UFormBase* createForm(FormID formID);
};

#endif				// __UIFACTOREY_H