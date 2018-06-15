#include "MyProject.h"
#include "PlayerRender.h"
#include "SceneEntityBase.h"
#include "TickMode.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

PlayerRender::PlayerRender(SceneEntityBase* entity_)
	: base(entity_)
{
	
}

void PlayerRender::_onSelfChanged()
{
	Super::_onSelfChanged();
}

/**
 * @brief 释放基本数据
 */
void PlayerRender::dispose()
{
	base.dispose();
}

void PlayerRender::attachToParentNode(EntityRenderBase* render)
{
	if(this.isSelfValid() && render.isSelfValid())
	{
		UtilEngineWrap::SetParent(render.getSelfActor(), this.mSelfActor, false);
	}
}

void PlayerRender::onTick(float delta, TickMode tickMode)
{
	base.onTick(delta, tickMode);
}

MY_END_NAMESPACE