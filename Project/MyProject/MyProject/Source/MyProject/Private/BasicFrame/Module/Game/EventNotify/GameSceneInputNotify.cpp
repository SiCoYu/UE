#include "MyProject.h"
#include "GameSceneInputNotify.h"
#include "InputMgr.h"
#include "InputKey.h"
#include "InputEventId.h"
#include "Math/Vector.h"	// FVector
#include "EventDispatchDelegate.h"

#include "Ctx.h"
#include "CtxExt.h"
#include "EntityData.h"
#include "PlayerMgr.h"
#include "PlayerMain.h"
#include "BeingEntityMovement.h"

MY_BEGIN_NAMESPACE(MyNS)

GameSceneInputNotify::GameSceneInputNotify()
{
            
}

void GameSceneInputNotify::init()
{
	GInputMgr->addKeyListener(
		InputKey::A,
		InputEventId::KEYUP_EVENT,
		MakeEventDispatchDelegate(
			this,
			&GameSceneInputNotify::onAKeyUp,
			(uint)0
		)
	);
	GInputMgr->addKeyListener(
		InputKey::S,
		InputEventId::KEYUP_EVENT,
		MakeEventDispatchDelegate(
			this,
			&GameSceneInputNotify::onSKeyUp,
			(uint)0
		)
	);
	GInputMgr->addKeyListener(
		InputKey::D,
		InputEventId::KEYUP_EVENT,
		MakeEventDispatchDelegate(
			this,
			&GameSceneInputNotify::onDKeyUp,
			(uint)0
		)
	);
	GInputMgr->addKeyListener(
		InputKey::F,
		InputEventId::KEYUP_EVENT,
		MakeEventDispatchDelegate(
			this,
			&GameSceneInputNotify::onFKeyUp,
			(uint)0
		)
	);
}

void GameSceneInputNotify::dispose()
{
	GInputMgr->removeKeyListener(
		InputKey::A,
		InputEventId::KEYUP_EVENT,
		MakeEventDispatchDelegate(
			this,
			&GameSceneInputNotify::onAKeyUp,
			(uint)0
		)
	);
	GInputMgr->removeKeyListener(
		InputKey::S,
		InputEventId::KEYUP_EVENT,
		MakeEventDispatchDelegate(
			this,
			&GameSceneInputNotify::onSKeyUp,
			(uint)0
		)
	);
	GInputMgr->removeKeyListener(
		InputKey::D,
		InputEventId::KEYUP_EVENT,
		MakeEventDispatchDelegate(
			this,
			&GameSceneInputNotify::onDKeyUp,
			(uint)0
		)
	);
	GInputMgr->removeKeyListener(
		InputKey::F,
		InputEventId::KEYUP_EVENT,
		MakeEventDispatchDelegate(
			this,
			&GameSceneInputNotify::onFKeyUp,
			(uint)0
		)
	);
}

void GameSceneInputNotify::onAKeyUp(uint eventId, IDispatchObject* dispObj)
{
	InputKey* keyCode = (InputKey*)dispObj;

	GPlayerMgr->getHero()->getMovement()->addActorLocalOffset(
		FVector(0, 0, 2)
	);
}

void GameSceneInputNotify::onSKeyUp(uint eventId, IDispatchObject* dispObj)
{
	InputKey* keyCode = (InputKey*)dispObj;

	GPlayerMgr->getHero()->getMovement()->addActorLocalOffset(
		FVector(0, 0, 2)
	);
}

void GameSceneInputNotify::onDKeyUp(uint eventId, IDispatchObject* dispObj)
{
	InputKey* keyCode = (InputKey*)dispObj;

	GPlayerMgr->getHero()->getMovement()->addActorLocalOffset(
		FVector(0, 0, 2)
	);
}

void GameSceneInputNotify::onFKeyUp(uint eventId, IDispatchObject* dispObj)
{
	InputKey* keyCode = (InputKey*)dispObj;

	GPlayerMgr->getHero()->getMovement()->addActorLocalOffset(
		FVector(0, 0, 2)
	);
}

void GameSceneInputNotify::onMouseDown()
{
            
}

void GameSceneInputNotify::onMouseUp()
{
            
}

MY_END_NAMESPACE