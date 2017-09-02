#ifndef __MyProjectEditor_H
#define __MyProjectEditor_H

#include "EngineMinimal.h"

class FMyProjectEditor : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void StartupModule_GAAttribute();
	void ShutdownModule_GAAttribute();
};

#endif // __MyProjectEditor_H