#pragma once 

#include <string>
#include "EventDispatchDelegate.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "ResInsMgrBase.h"
#include "ResLoadPriority.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MaterialInsRes;

class MaterialInsResMgr : public ResInsMgrBase
{
	M_DECLARE_CLASS(MaterialInsResMgr, ResInsMgrBase);

public:
	MaterialInsResMgr();

public:
	MaterialInsRes* getAndSyncLoadRes(
		std::string path, 
		EventDispatchDelegate handle,
		EventDispatchDelegate progressHandle = nullptr,
		ResLoadPriority priority = ResLoadPriority::eRLP_Middle_1000
	);
	MaterialInsRes* getAndAsyncLoadRes(
		std::string path, 
		EventDispatchDelegate handle,
		EventDispatchDelegate progressHandle = nullptr,
		ResLoadPriority priority = ResLoadPriority::eRLP_Middle_1000
	);
};

MY_END_NAMESPACE