#include "MyProject.h"
#include "GameRouteHandle.h"
#include "MsgRouteBase.h"
#include "EventDispatchDelegate.h"
#include "IDispatchObject.h"

GameRouteHandle::GameRouteHandle()
{

}

void GameRouteHandle::init()
{
    Super::init();

    this->addMsgRouteHandle(
		MsgRouteId::eMRID_ThreadLog,
		MakeEventDispatchDelegate(
			this, 
			&GameRouteHandle::threadLog
		)
	);
    this->addMsgRouteHandle(
		MsgRouteId::eMRID_SocketOpened, 
		MakeEventDispatchDelegate(
			this, 
			&GameRouteHandle::onSocketOpened
		)
	);
}

void GameRouteHandle::dispose()
{
    this->removeMsgRouteHandle(
		MsgRouteId::eMRID_ThreadLog, 
		MakeEventDispatchDelegate(
			this, 
			&GameRouteHandle::threadLog
		)
	);
    this->removeMsgRouteHandle(
		MsgRouteId::eMRID_SocketOpened, 
		MakeEventDispatchDelegate(
			this,
			&GameRouteHandle::onSocketOpened
		)
	);

	Super::dispose();
}

void GameRouteHandle::threadLog(IDispatchObject* dispObj)
{
    MsgRouteBase* msg = (MsgRouteBase*)dispObj;
}

void GameRouteHandle::onSocketOpened(IDispatchObject* dispObj)
{
    
}