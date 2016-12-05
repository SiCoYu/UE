//Copyleft under the creative commons license
//For details see http://creativecommons.org/licenses/by-sa/4.0/

#include "MyProject.h"
#include "CreateObjectFromBlueprint.h"


UObject* UCreateObjectFromBlueprint::NewObjectFromBlueprint(UObject* WorldContextObject, UClass* UC)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	UObject* tempObject = NewObject<UObject>(UC);

	return tempObject;
}