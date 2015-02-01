#ifndef __IENGINEAPI_H
#define __IENGINEAPI_H

class UGameInstance;

class IEngineApi
{
public:
	virtual UGameInstance* getGameInstance();
};

#endif				// __IENGINEAPI_H