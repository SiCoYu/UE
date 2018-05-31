#include "MyProject.h"
#include "MsgRouteBase.h"

MY_BEGIN_NAMESPACE(MyNS)

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

MY_END_NAMESPACE