#ifndef __ENGINEAPI_H
#define __ENGINEAPI_H

class UGameInstance;

class EngineApi
{
public:
	virtual UGameInstance* getGameInstance();
	virtual UWorld* getWorld();
	virtual void showCursor();
};

#endif				// __ENGINEAPI_H