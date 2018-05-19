#pragma once

#include "IUiEventNotify.h"

class Form;

class GameUiEventNotify : IUiEventNotify
{
	virtual void onCodeFormLoaded(Form* form) override;
	virtual void onWidgetLoaded(Form* form) override;
};