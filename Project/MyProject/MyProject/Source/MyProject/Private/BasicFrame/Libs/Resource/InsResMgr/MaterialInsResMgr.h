#pragma once 

#include <string>
#include "EventDispatchDelegate.h"
#include "BaseClassDef.h"
#include "InsResMgrBase.h"

class MaterialInsRes;

class MaterialInsResMgr : public InsResMgrBase
{
	M_DECLARE_SUPER_KW(InsResMgrBase);

public:
	MaterialInsResMgr();

public:
	MaterialInsRes* getAndSyncLoadRes(std::string path, EventDispatchDelegate handle);
	MaterialInsRes* getAndAsyncLoadRes(std::string path, EventDispatchDelegate handle);
};