#include "MyProject.h"
#include "MyStyle.h"
#include "MenuStyles.h" 

// #include "Welcome/to/bobsmagic.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FMyProject, MyProject, "MyProject");

/**
* Called right after the module DLL has been loaded and the module object has been created
*/
void  FMyProject::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();

	//PointerToBobsMagic = new BobsMagic::MagicalBob();
	//PointerToBobsMagic->ThankEveryoneForReading();

	/*Loads resources and registers them with Slate*/
	/*Do this before trying to use resources*/
	MyUIResources.Initialize();

	/*TODO: Anything else game module might need to do on load*/

	FSlateStyleRegistry::UnRegisterSlateStyle("PreloadStyle");
	FMyStyle::Initialize();

	this.StartupModule_SlateStyleSet();
}

/**
* Called before the module is unloaded, right before the module object is destroyed.
*/
void  FMyProject::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();

	//PointerToBobsMagic->Dispose();
	//PointerToBobsMagic = NULL;

	/*Unregister resources/styles with Slate, cleanup, free memory*/
	MyUIResources.Shutdown();

	/*Cleanup/free any resources here*/

	FMyStyle::Shutdown();

	this.ShutdownModule_SlateStyleSet();
}

/*First defined here, no need to call parent*/
/*Give caller a pointer to our FSlateGameResources*/
TSharedPtr<FSlateGameResources> FMyProject::GetSlateGameResources()
{
	/*Give caller a pointer to our FSlateGameResources*/
	/*Giving strong pointer, helps gurantee access to resources*/
	return MyUIResources.GetSlateGameResources();
}

void FMyProject::StartupModule_SlateStyleSet()
{
	//Hot reload hack
	FSlateStyleRegistry::UnRegisterSlateStyle(FMenuStyles::GetStyleSetName());
	FMenuStyles::Initialize();
}

void FMyProject::ShutdownModule_SlateStyleSet()
{
	FMenuStyles::Shutdown();
}