#include "MyProject.h"
#include "GameRouteNotify.h"
#include "SafePointer.h"		// SAFE_NEW
#include "GameRouteHandle.h"
#include "MsgRouteBase.h"
#include "EventDispatchDelegate.h"
#include "MsgRouteHandleBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "MClassFactory.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryAlloc.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(GameRouteNotify, MsgRouteDispatchHandle)

GameRouteNotify::GameRouteNotify()
{

}

void GameRouteNotify::init()
{
    this->mGameRouteHandle = MY_NEW GameRouteHandle();
    this->mGameRouteHandle->init();
}

void GameRouteNotify::dispose()
{
    if(nullptr != this->mGameRouteHandle)
    {
        this->removeRouteHandle(
			(int)MsgRouteType::eMRT_BASIC, 
			MakeEventDispatchDelegate(
				this->mGameRouteHandle, 
				&MsgRouteHandleBase::handleMsg
			)
		);

        this->mGameRouteHandle->dispose();
        this->mGameRouteHandle = nullptr;
    }
}

MY_END_NAMESPACE