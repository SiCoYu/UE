#include "MyProject.h"
#include "EngineData.h"

void EngineData::setMainActor(AActor* actor)
{
	m_mainActor = actor;
}

AActor* EngineData::getMainActor()
{
	return m_mainActor;
}