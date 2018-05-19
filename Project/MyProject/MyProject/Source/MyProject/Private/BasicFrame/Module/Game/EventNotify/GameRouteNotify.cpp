#include "MyProject.h"
#include "GameRouteNotify.h"
#include "SafePointer.h"		// SAFE_NEW
#include "GameRouteHandle.h"
#include "MsgRouteBase.h"
#include "EventDispatchDelegate.h"

GameRouteNotify::GameRouteNotify()
{

}

void GameRouteNotify::init()
{
    this->mGameRouteHandle = SAFE_NEW GameRouteHandle();
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
				&GameRouteHandle::handleMsg
			)
		);
        this->mGameRouteHandle->dispose();
        this->mGameRouteHandle = nullptr;
    }
}