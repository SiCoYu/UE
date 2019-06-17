#include "MyProject.h"
#include "SocketOpenedMR.h"
#include "MsgRouteId.h"

MY_BEGIN_NAMESPACE(MyNS)

SocketOpenedMR::SocketOpenedMR()
	: MsgRouteBase(MsgRouteId::eMRID_SocketOpened)
{

}

MY_END_NAMESPACE