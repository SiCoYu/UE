#include "MyProject.h"
#include "MyStaticLibrary.h"

//////////////////////////////////////////////////////////////////////////
// MyStaticLibrary

UMyStaticLibrary::UMyStaticLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

int32 UMyStaticLibrary::ComplicatedGameDataAnalysis()
{
	//Do lots of stuff that requires the entire Game's compiled header source,
	//  involving lots of your custom project-specific classes,
	//    classes that have not been compiled in the .h of this library 
	//    since they depend on it.
	return 9000;
}