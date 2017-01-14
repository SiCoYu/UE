#pragma once

class FLatentActionManager;

class MyLatentActionManager
{
protected:
	FLatentActionManager* mLatentActionManager;

public:
	void init();
	void dispose();
};