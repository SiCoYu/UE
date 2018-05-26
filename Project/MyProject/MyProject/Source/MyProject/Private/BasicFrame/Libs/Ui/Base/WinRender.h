#ifndef __WinRender_H
#define __WinRender_H

//#include "UMG.h"
#include "SlateWidget.h"
#include "UMGWidget.h"
#include "GObject.h"

class WinRender : public GObject
{
public:
	//UUserWidget* m_umgWidget;
	//UUserWidget* mUiRoot;      // ui 根节点
	union
	{
		SSlateWidget* mUiRoot_S;
		UUMGWidget* mUiRoot;
	};
};

#endif