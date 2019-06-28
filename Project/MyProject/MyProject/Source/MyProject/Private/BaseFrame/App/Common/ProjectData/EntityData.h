#pragma once

#include "GObject.h"
#include "MySharedPointer.h"
#include "MClassInfo.h"
#include "MClassMacros.h"

MY_BEGIN_NAMESPACE(MyNS)

DLL_EXPORT_TEMPLATE_CLASS(MySharedPtr<PlayerMgr>);

class PlayerMgr;

/**
 * @brief 一个场景的数据，与主角基本没什么关系
 */
class MYPROJECT_API EntityData : public GObject
{
	M_DECLARE_CLASS(EntityData, GObject)

protected:
	MySharedPtr<PlayerMgr> mPlayerMgr;

public:
	EntityData();

	void init();
	void dispose();

	MySharedPtr<PlayerMgr> getPlayerMgr();
	void setPlayerMgr(MySharedPtr<PlayerMgr>& value);
};

MY_END_NAMESPACE