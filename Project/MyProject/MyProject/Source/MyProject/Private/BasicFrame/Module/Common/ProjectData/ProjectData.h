#pragma once

#include "GObject.h"
#include "MySharedPointer.h"
#include "MClassInfo.h"
#include "MClassMacros.h"

MY_BEGIN_NAMESPACE(MyNS)

class PlayerMgr;

/**
 * @brief �����������Լ�������
 */
class ProjectData : public GObject
{
	M_DECLARE_CLASS(ProjectData, GObject)

protected:
	MySharedPtr<PlayerMgr> mPlayerMgr;

public:
	ProjectData();

	void init();
	void dispose();

	MySharedPtr<PlayerMgr>& getPlayerMgr();
	void setPlayerMgr(MySharedPtr<PlayerMgr>& value);
};

MY_END_NAMESPACE