#include "MyProject.h"
#include "MsgRouteBase.h"

MsgRouteBase::MsgRouteBase()
{

}

MsgRouteBase::~MsgRouteBase()
{

}

MsgRouteBase::MsgRouteBase(MsgRouteId id)
{
	this->mMsgType = MsgRouteType::eMRT_BASIC;
	this->mMsgId = id;
}

void MsgRouteBase::resetDefault()
{

}