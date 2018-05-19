#include "MyProject.h"
#include "GameRouteHandle.h"
#include "MsgRouteId.h"

GameRouteHandle::GameRouteHandle()
{

}

void GameRouteHandle::init()
{
    Super::init();

    this->addMsgRouteHandle(MsgRouteId.eMRID_ThreadLog, threadLog);
    this->addMsgRouteHandle(MsgRouteId.eMRID_SocketOpened, onSocketOpened);
}

void GameRouteHandle::dispose()
{
    this->removeMsgRouteHandle(MsgRouteId.eMRID_ThreadLog, threadLog);
    this->removeMsgRouteHandle(MsgRouteId.eMRID_SocketOpened, onSocketOpened);

	Super::dispose();
}

protected void threadLog(IDispatchObject* dispObj, uint uniqueId)
{
    MsgRouteBase* msg = (MsgRouteBase*)dispObj;
}

protected void onSocketOpened(IDispatchObject* dispObj, uint uniqueId)
{
    
}