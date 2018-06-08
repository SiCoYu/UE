#include "MyProject.h"
#include "MsgRouteBase.h"
#include "Prequisites.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(MsgRouteBase, GObject)

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