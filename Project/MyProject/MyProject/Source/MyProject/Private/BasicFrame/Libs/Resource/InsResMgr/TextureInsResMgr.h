#pragma once 

#include <string>
#include "EventDispatchDelegate.h"
#include "BaseClassDef.h"
#include "InsResMgrBase.h"

class TextureInsRes;

class TextureInsResMgr : public InsResMgrBase
{
	M_DECLARE_SUPER_KW(InsResMgrBase);

public:
	TextureInsResMgr();

public:
	TextureInsRes* getAndSyncLoadRes(std::string path, EventDispatchDelegate handle);
	TextureInsRes* getAndAsyncLoadRes(std::string path, EventDispatchDelegate handle);
};