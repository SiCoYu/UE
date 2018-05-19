#include "MyProject.h"
#include "GameRouteHandle.h"
#include "MsgRouteId.h"
#include "EventDispatchDelegate.h"

GameRouteHandle::GameRouteHandle()
{

}

void GameRouteHandle::init()
{
    Super::init();

    this->addMsgRouteHandle(MsgRouteId.eMRID_ThreadLog, MakeEventDispatchDelegate(this, &GameRouteHandle::threadLog));
    this->addMsgRouteHandle(MsgRouteId.eMRID_SocketOpened, MakeEventDispatchDelegate(this, &GameRouteHandle::onSocketOpened));
}

void GameRouteHandle::dispose()
{
    this->removeMsgRouteHandle(MsgRouteId.eMRID_ThreadLog, threadLog);
    this->removeMsgRouteHandle(MsgRouteId.eMRID_SocketOpened, onSocketOpened);

	Super::dispose();
}

void GameRouteHandle::threadLog(IDispatchObject* dispObj, uint uniqueId)
{
    MsgRouteBase* msg = (MsgRouteBase*)dispObj;
}

void GameRouteHandle::onSocketOpened(IDispatchObject* dispObj, uint uniqueId)
{
    
}