#pragma once

#include "AuxWindow.h"

class AddOnceEventDispatch;
class UButton;

namespace MyNS
{
	class AuxButton : public AuxWindow
	{
	protected:
		UButton* mNativeButton;
		AddOnceEventDispatch* mClickEventDispatch;      // 点击事件分发
	};
}