#include "MyProject.h"

// #include "Welcome/to/bobsmagic.h"

// https://wiki.unrealengine.com/Linking_Static_Libraries_Using_The_Build_System
class FMyProjectGameModule : public FDefaultGameModuleImpl
{
	//BobsMagic::MagicalBob *PointerToBobsMagic;

	/**
	* Called right after the module DLL has been loaded and the module object has been created
	*/
	virtual void StartupModule() override
	{
		//PointerToBobsMagic = new BobsMagic::MagicalBob();
		//PointerToBobsMagic->ThankEveryoneForReading();
	}

	/**
	* Called before the module is unloaded, right before the module object is destroyed.
	*/
	virtual void ShutdownModule()
	{
		//PointerToBobsMagic->Dispose();
		//PointerToBobsMagic = NULL;
	}
};

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, MyProject, "MyProject" );
 