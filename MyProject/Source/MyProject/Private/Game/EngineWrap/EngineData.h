#ifndef __ENGINEDATA_H
#define __ENGINEDATA_H

class EngineData
{
protected:
	UObject* m_mainActor;

public:
	void getMainActor();
	void setMainActor(UObject* actor);
};

#endif				// __ENGINEDATA_H