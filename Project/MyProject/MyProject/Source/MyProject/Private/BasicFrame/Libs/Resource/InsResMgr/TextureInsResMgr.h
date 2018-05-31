#pragma once 

#include <string>
#include "EventDispatchDelegate.h"
#include "BaseClassDef.h"
#include "ResInsMgrBase.h"
#include "ResLoadPriority.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class TextureInsRes;

class TextureInsResMgr : public ResInsMgrBase
{
	M_DECLARE_SUPER_KW(ResInsMgrBase);

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

MY_END_NAMESPACE