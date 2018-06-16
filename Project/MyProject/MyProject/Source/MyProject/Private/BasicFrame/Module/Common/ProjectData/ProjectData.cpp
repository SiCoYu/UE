#include "MyProject.h"
#include "ProjectData.h"
#include "PlayerMgr.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(ProjectData, GObject)

ProjectData::ProjectData()
{
	this->mPlayerMgr = MySharedPtr<PlayerMgr>(MY_NEW PlayerMgr());
}

void ProjectData::init()
{
	this->mPlayerMgr->init();
}

void ProjectData::dispose()
{
	this->mPlayerMgr->dispose();

	this->mPlayerMgr.setNull();
}

MySharedPtr<PlayerMgr> ProjectData::getPlayerMgr()
{
	return this->mPlayerMgr;
}

void ProjectData::setPlayerMgr(MySharedPtr<PlayerMgr>& value)
{
	this->mPlayerMgr = value;
}

MY_END_NAMESPACE