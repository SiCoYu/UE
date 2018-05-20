#pragma once 

#include <string>
#include "EventDispatchDelegate.h"
#include "BaseClassDef.h"
#include "ResInsMgrBase.h"

class MaterialInsRes;

class MaterialInsResMgr : public ResInsMgrBase
{
	M_DECLARE_SUPER_KW(ResInsMgrBase);

public:
	MaterialInsResMgr();

public:
	MaterialInsRes* getAndSyncLoadRes(std::string path, EventDispatchDelegate handle);
	MaterialInsRes* getAndAsyncLoadRes(std::string path, EventDispatchDelegate handle);
};