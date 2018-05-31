#pragma once

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class Form;

class IUiEventNotify
{
public:
    virtual void onCodeFormLoaded(Form* form) = 0;
	virtual void onWidgetLoaded(Form* form) = 0;
};

MY_END_NAMESPACE