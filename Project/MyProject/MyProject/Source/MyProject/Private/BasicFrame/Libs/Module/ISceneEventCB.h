#pragma once

class ISceneEventCB
{
public:
    virtual void onLevelLoaded() = 0;
	virtual void init() = 0;
	virtual void dispose() = 0;
};