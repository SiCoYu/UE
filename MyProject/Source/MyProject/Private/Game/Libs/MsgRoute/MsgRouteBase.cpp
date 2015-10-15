#include "MyProject.h"
#include "MsgRouteBase.h"

MsgRouteBase::MsgRouteBase(MsgRouteID id)
{
	m_msgType = eMRT_BASIC;
	m_msgID = id;
}

void MsgRouteBase::resetDefault()
{

}