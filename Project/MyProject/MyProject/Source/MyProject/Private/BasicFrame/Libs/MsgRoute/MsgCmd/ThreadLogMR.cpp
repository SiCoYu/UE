#include "MyProject.h"
#include "ThreadLogMR.h"
#include "MsgRouteId.h"

MY_BEGIN_NAMESPACE(MyNS)

ThreadLogMR::ThreadLogMR()
	: MsgRouteBase(MsgRouteId::eMRID_ThreadLog)
{

}

ThreadLogMR::~ThreadLogMR()
{

}

MY_END_NAMESPACE