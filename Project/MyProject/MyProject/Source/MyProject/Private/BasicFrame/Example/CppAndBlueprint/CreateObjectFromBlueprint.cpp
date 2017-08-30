//Copyleft under the creative commons license
//For details see http://creativecommons.org/licenses/by-sa/4.0/

#include "MyProject.h"
#include "CreateObjectFromBlueprint.h"

UObject* UCreateObjectFromBlueprint::NewObjectFromBlueprint(UObject* WorldContextObject, UClass* UC)
{
	// UE4 4.17 warning C4996: 'UEngine::GetWorldFromContextObject': GetWorldFromContextObject(Object) and GetWorldFromContextObject(Object, boolean) are replaced by GetWorldFromContextObject(Object, Enum) or GetWorldFromContextObjectChecked(Object) Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject);
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	UObject* tempObject = NewObject<UObject>(UC);

	return tempObject;
}