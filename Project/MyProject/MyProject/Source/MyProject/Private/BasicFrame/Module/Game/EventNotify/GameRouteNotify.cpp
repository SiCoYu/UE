#include "MyProject.h"
#include "GameRouteNotify.h"
#include "SafePointer.h"		// SAFE_NEW

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
        this->removeRouteHandle((int)MsgRouteType.eMRT_BASIC, this->mGameRouteHandle, this.mGameRouteHandle->handleMsg, 0);
        this->mGameRouteHandle->dispose();
        this->mGameRouteHandle = nullptr;
    }
}