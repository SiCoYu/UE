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

	// ��ֵ���� Player ���߼���ʼ����
	GCtx->beginPlay();
}