#include "MyProject.h"
#include "MsgRouteBase.h"

MsgRouteBase::MsgRouteBase()
{

}

MsgRouteBase::MsgRouteBase(MsgRouteID id)
{
	this->mMsgType = eMRT_BASIC;
	this->mMsgId = id;
}

void MsgRouteBase::resetDefault()
{

}