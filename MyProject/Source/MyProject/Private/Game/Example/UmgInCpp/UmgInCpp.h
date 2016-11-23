#pragma once

#include "MyProject.h"
#include "UmgInCpp.generated.h"

/**
 * @brief https://wiki.unrealengine.com/UMG,_Referencing_UMG_Widgets_in_Code
 */
UCLASS(config=Game)
class UUmgInCpp : public UObject
{
	GENERATED_BODY()


	// Note: that am using forward declaration Because am not including the
	// widget in the header and to prevent circular dependency.
	// you dont need to do that if you include the Widget Class in the .h
	// forward declaration is just putting "class" before the class name so the compiler know its a
	// class but its not included in the header and don't freak out. Ex. ¡°class UUserWidget¡±

	// Reference UMG Asset in the Editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> wMainMenu;

	// Variable to hold the widget After Creating it.
	UUserWidget* MyMainMenu;

public:
	UUmgInCpp(const FObjectInitializer& ObjectInitializer);
	void showMenu();
};