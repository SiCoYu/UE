#pragma once 

#include <string>
#include "EventDispatchDelegate.h"
#include "BaseClassDef.h"
#include "InsResMgrBase.h"
#include "ResLoadPriority.h"

class TextureInsRes;

class TextureInsResMgr : public InsResMgrBase
{
	M_DECLARE_SUPER_KW(InsResMgrBase);

public:
	TextureInsResMgr();

public:
	TextureInsRes* getAndSyncLoadRes(
		std::string path, 
		EventDispatchDelegate handle, 
		EventDispatchDelegate progressHandle = nullptr, 
		ResLoadPriority priority = ResLoadPriority::eRLP_Middle_1000
	);
	TextureInsRes* getAndAsyncLoadRes(
		std::string path, 
		EventDispatchDelegate handle,
		EventDispatchDelegate progressHandle = nullptr,
		ResLoadPriority priority = ResLoadPriority::eRLP_Middle_1000
	);
};