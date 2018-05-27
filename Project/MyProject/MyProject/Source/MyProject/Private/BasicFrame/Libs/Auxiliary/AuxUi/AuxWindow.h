#pragma once

#include "GObject.h"

namespace MyNS
{
	class AuxWindow : public GObject
	{
		M_DECLARE_CLASS(AuxWindow, GObject)

	public:
		virtual void init();
		virtual void dispose();
	};
}