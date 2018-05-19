#include "MyProject.h"
#include "SocketOpenedMR.h"
#include "MsgRouteId.h"

SocketOpenedMR::SocketOpenedMR()
	: MsgRouteBase(MsgRouteId::eMRID_SocketOpened)
{

}