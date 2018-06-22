#pragma once

#include "GObject.h"
#include "MySharedPointer.h"
#include "MClassInfo.h"
#include "MClassMacros.h"

MY_BEGIN_NAMESPACE(MyNS)

class PlayerMgr;

/**
 * @brief һ�����������ݣ������ǻ���ûʲô��ϵ
 */
class EntityData : public GObject
{
	M_DECLARE_CLASS(PlayerData, GObject)

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