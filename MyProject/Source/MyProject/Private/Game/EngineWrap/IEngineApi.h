#ifndef __IENGINEAPI_H
#define __IENGINEAPI_H

class UGameInstance;

class IEngineApi
{
public:
	virtual ~IEngineApi(){};
	virtual UGameInstance* getGameInstance() = 0;
};

#endif				// __IENGINEAPI_H