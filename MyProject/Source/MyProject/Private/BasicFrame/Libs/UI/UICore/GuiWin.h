#ifndef __GuiWin_H
#define __GuiWin_H

//#include "UMG.h"
#include "SlateWidget.h"
#include "UMGWidget.h"

class GuiWin
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