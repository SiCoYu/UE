#include "MyProject.h"
#include "SocketClosedMR.h"
#include "MsgRouteId.h"

MY_BEGIN_NAMESPACE(MyNS)

SocketClosedMR::SocketClosedMR()
	: MsgRouteBase(MsgRouteId::eMRID_SocketClosed)
{

}

MY_END_NAMESPACE