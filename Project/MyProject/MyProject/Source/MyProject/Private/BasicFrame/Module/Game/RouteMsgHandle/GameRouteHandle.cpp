#include "MyProject.h"
#include "GameRouteHandle.h"
#include "MsgRouteBase.h"
#include "EventDispatchDelegate.h"
#include "IDispatchObject.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(GameRouteHandle, MsgRouteHandleBase)

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
			&GameRouteHandle::threadLog, 
			0
		)
	);
    this->addMsgRouteHandle(
		MsgRouteId::eMRID_SocketOpened, 
		MakeEventDispatchDelegate(
			this, 
			&GameRouteHandle::onSocketOpened, 
			0
		)
	);
}

void GameRouteHandle::dispose()
{
    this->removeMsgRouteHandle(
		MsgRouteId::eMRID_ThreadLog, 
		MakeEventDispatchDelegate(
			this, 
			&GameRouteHandle::threadLog, 
			0
		)
	);
    this->removeMsgRouteHandle(
		MsgRouteId::eMRID_SocketOpened, 
		MakeEventDispatchDelegate(
			this,
			&GameRouteHandle::onSocketOpened, 
			0
		)
	);

	Super::dispose();
}

void GameRouteHandle::threadLog(IDispatchObject* dispObj, uint eventId)
{
    MsgRouteBase* msg = (MsgRouteBase*)dispObj;
}

void GameRouteHandle::onSocketOpened(IDispatchObject* dispObj, uint eventId)
{
    
}

MY_END_NAMESPACE