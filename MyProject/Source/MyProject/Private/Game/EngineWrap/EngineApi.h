#ifndef __ENGINEAPI_H
#define __ENGINEAPI_H

class UGameInstance;

class EngineApi
{
public:
	virtual UGameInstance* getGameInstance();
	virtual UWorld* getWorld();
	virtual void showCursor();

	static void addEventHandle(UButton* pBtn, UObject* pFuncObj, FName funcName);
};

#endif				// __ENGINEAPI_H