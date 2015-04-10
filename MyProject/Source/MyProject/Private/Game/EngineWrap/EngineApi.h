#ifndef __ENGINEAPI_H
#define __ENGINEAPI_H

class UGameInstance;
class UMyProjectEngine;
class UMyProjectGameInstance;

class EngineApi
{
public:
	virtual UGameInstance* getGameInstance();
	virtual UWorld* getWorld();
	virtual void showCursor();
	UMyProjectEngine* getEngine();
	UMyProjectGameInstance* getMyProjectGameInstanceByEngine();
	UWorld* getWorldByEngine();

	static void addEventHandle(UButton* pBtn, UObject* pFuncObj, FName funcName);
};

#endif				// __ENGINEAPI_H