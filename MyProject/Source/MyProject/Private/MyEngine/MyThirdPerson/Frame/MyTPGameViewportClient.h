#pragma once

//#include "MyProject.h"
#include "MyGameViewportClientBase.h"
// TODO: 包含下面这两个文件导致编译不过
//#include "Misc/Optional.h"
//#include "Input/Events.h"
#include "MyTPGameViewportClient.generated.h"

// https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/Reference/Classes/Specifiers/Within/index.html
// https://docs.unrealengine.com/latest/INT/Programming/UnrealArchitecture/Reference/Classes/Specifiers/Config/index.html
UCLASS(Within=Engine, transient, config=Engine)
class UMyTPGameViewportClient : public UMyGameViewportClientBase
{
	GENERATED_UCLASS_BODY()

//public:
//	UMyViewportClient(const FObjectInitializer& ObjectInitializer)

public:
	// https://wiki.unrealengine.com/UMG_Disable_Focus_Outline
	// Always a widget acquired focus it will get a dotted outline that seams to be more for PC keyboard then a GamePad on a console. 
	// We will override this methos to only return false, this way we complete disable
	// the focus outline. Consider using your own logic here.
	//Now you just have to add the class into your DefaultEngine.ini file and you should be good to go.
	//[/ Script / Engine.Engine]
	//GameViewportClientClassName = / Script / MyGame.MyGameViewportClient
	//So that should be all you need to get rid or control the focus outline your own way.
	//Using the project settings
	//As stated by Nick Darnell in the forums, from 4.8 you can customize the behavior directly in the Project Settings.
	//Project Settings >> User Interface >> RenderFocusRule(Set To) Never
	virtual TOptional<bool> QueryShowFocus(const EFocusCause InFocusCause) const override;
};