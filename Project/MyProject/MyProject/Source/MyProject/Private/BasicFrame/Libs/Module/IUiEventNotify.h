#pragma once

class Form;

class IUiEventNotify
{
public:
    virtual void onCodeFormLoaded(Form* form) = 0;
	virtual void onWidgetLoaded(Form* form) = 0;
};