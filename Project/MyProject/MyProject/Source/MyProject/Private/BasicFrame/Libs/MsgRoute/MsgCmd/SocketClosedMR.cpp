#include "MyProject.h"
#include "SocketClosedMR.h"
#include "MsgRouteId.h"

SocketClosedMR::SocketClosedMR()
	: MsgRouteBase(MsgRouteId::eMRID_SocketClosed)
{

}