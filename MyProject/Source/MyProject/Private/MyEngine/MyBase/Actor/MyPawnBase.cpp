#include "MyProject.h"
#include "MyPawnBase.h"

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