#pragma once 

#include <string>
#include "EventDispatchDelegate.h"
#include "BaseClassDef.h"
#include "InsResMgrBase.h"

class MatInsRes;

class MatInsResMgr : public InsResMgrBase
{
	M_DECLARE_SUPER_KW(InsResMgrBase);

public:
	MatInsResMgr();

public:
	MatInsRes* getAndSyncLoadRes(std::string path, EventDispatchDelegate handle);
	MatInsRes* getAndAsyncLoadRes(std::string path, EventDispatchDelegate handle);
};