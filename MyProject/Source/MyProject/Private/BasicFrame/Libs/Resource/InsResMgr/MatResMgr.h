#pragma once 

#include <string>
#include "EventDispatchDelegate.h"
#include "InsResMgrBase.h"

class MatRes;

class MatResMgr : InsResMgrBase
{
	typedef InsResMgrBase Super;

public:
	MatResMgr();

public:
	MatRes* getAndSyncLoadRes(std::string path, EventDispatchDelegate handle);
	MatRes* getAndAsyncLoadRes(std::string path, EventDispatchDelegate handle);
};