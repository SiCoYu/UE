#ifndef __ENGINEAPI_H
#define __ENGINEAPI_H

#include "IEngineApi.h"

class UGameInstance;

class EngineApi : public IEngineApi
{
public:
	virtual UGameInstance* getGameInstance();
};

#endif				// __ENGINEAPI_H