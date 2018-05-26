#pragma once

#include "GObject.h"

struct FLatentActionManager;

class MyLatentActionManager : public GObject
{
protected:
	FLatentActionManager* mLatentActionManager;

public:
	void init();
	void dispose();
};