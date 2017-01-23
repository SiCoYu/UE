#include "MyProject.h"
#include "MyActorBase.h"
#include "LogCategoryDef.h"

AMyActorBase::AMyActorBase()
{
	
}

AMyActorBase::~AMyActorBase()
{

}

void AMyActorBase::SetInfo(FString name)
{
	this->mName = name;
}

void AMyActorBase::execInConsole()
{
	UE_LOG(ComWarning, Warning, TEXT("name:%s, Say hello"), *mName);
}