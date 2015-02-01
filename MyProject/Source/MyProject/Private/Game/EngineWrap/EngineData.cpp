#include "MyProject.h"
#include "EngineData.h"

void EngineData::setMainActor(UObject* actor)
{
	m_mainActor = actor;
}

void EngineData::getMainActor()
{
	return m_mainActor;
}