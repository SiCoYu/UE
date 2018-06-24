#pragma once

#include "IUiEventNotify.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class Form;

class GameUiEventNotify : public IUiEventNotify
{
public:
	GameUiEventNotify();

	void init();
	void dispose();

	virtual void onCodeFormLoaded(Form* form) override;
	virtual void onWidgetLoaded(Form* form) override;
};

MY_END_NAMESPACE