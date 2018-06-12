#include "MyProject.h"
#include "SceneEntityMovement.h"

MY_BEGIN_NAMESPACE(MyNS)

SceneEntityMovement(SceneEntityBase entity)
{
	mTypeId = "SceneEntityMovement";
	this.mEntity = entity;
}

virtual void init()
{

}

virtual void dispose()
{
	this.mEntity = null;
}

virtual void onTick(float delta, TickMode tickMode)
{

}
	
MY_END_NAMESPACE