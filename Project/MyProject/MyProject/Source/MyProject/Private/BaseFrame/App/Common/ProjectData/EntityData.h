#pragma once

#include "GObject.h"
#include "MySharedPointer.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
// Windows 下导出 dll 符号，模板类参数必须有完整的声明，而不是仅仅是前置声明，否则会报错误
// error C4150: deletion of pointer to incomplete type 'MyNS::PlayerMgr'; no destructor called
#include "PlayerMgr.h"

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