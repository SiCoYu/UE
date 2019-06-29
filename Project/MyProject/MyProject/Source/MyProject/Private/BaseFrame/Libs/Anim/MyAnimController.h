#pragma once

#include "PlatformDefine.h"

class AActor;
class UMyAnimInstanceBase;

MY_BEGIN_NAMESPACE(MyNS)

class MyAnimController
{
protected:
	AActor* mActorPtr;
	UMyAnimInstanceBase* mAnimInstancePtr;

public:
	void init();
	void dispose();

	void setActor(AActor* actor);
};

MY_END_NAMESPACE