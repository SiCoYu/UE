#include "MyProject.h"
#include "MyPawnBase.h"
#include "Common.h"

AMyPawnBase::AMyPawnBase()
{

}

void AMyPawnBase::BeginPlay()
{
	Super::BeginPlay();

	GEngineData->setMainActor(this);

	// 赋值控制 Player ，逻辑开始运行
	GCtx->beginPlay();
}