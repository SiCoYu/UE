#ifndef __MyProject_H__
#define __MyProject_H__

#include "EngineMinimal.h"
#include "UMG.h"
#include "MyUIResources.h"

/**
 * @URL https://wiki.unrealengine.com/Slate,_Loading_Styles_%26_Resources
 * @URL https://wiki.unrealengine.com/Linking_Static_Libraries_Using_The_Build_System
 */

class FSlateGameResources;

class FMyProject : public FDefaultGameModuleImpl
{
	//BobsMagic::MagicalBob *PointerToBobsMagic;

	/**
	* Called right after the module DLL has been loaded and the module object has been created
	*/
	virtual void StartupModule() override;

	/**
	* Called before the module is unloaded, right before the module object is destroyed.
	*/
	virtual void ShutdownModule();

	// https://wiki.unrealengine.com/Slate,_Loading_Styles_%26_Resources
public:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Give a handle to MyUIResources to anyone who asks
	TSharedPtr<class FSlateGameResources> GetSlateGameResources();

protected:
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Data Structure and Interface for maintaining SlateGameResources on Game to Game basis
	FMyUIResources MyUIResources;

protected:
	void StartupModule_SlateStyleSet();
	void ShutdownModule_SlateStyleSet();
};

#endif