#pragma once 

#include <string>
#include "EventDispatchDelegate.h"
#include "InsResMgrBase.h"

class MatInsRes;

class MatInsResMgr : public InsResMgrBase
{
	typedef InsResMgrBase Super;

public:
	MatInsResMgr();

public:
	MatInsRes* getAndSyncLoadRes(std::string path, EventDispatchDelegate handle);
	MatInsRes* getAndAsyncLoadRes(std::string path, EventDispatchDelegate handle);
};