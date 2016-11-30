#include "MyProject.h"
#include "DeferAttachToSocketActor.h"

ADeferAttachToSocketActor::ADeferAttachToSocketActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	//Asset, Reference Obtained Via Right Click in Editor
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshOb_AW2(TEXT("StaticMesh'/Game/VictoryGoals/Mechs/JoyControl/JoyControl_WindTurtle.JoyControl_WindTurtle'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshOb_AW2(TEXT("StaticMesh'/Game/ThirdPerson/Meshes/CubeMesh.CubeMesh'"));

	AssetSM_JoyControl = StaticMeshOb_AW2.Object;

	//Create
	//JoyfulControl = ObjectInitializer.CreateDefaultSubobject < UStaticMeshComponent >(this, TEXT("JoyfulControlYay"));
	JoyfulControl = PCIP.CreateDefaultSubobject < UStaticMeshComponent >(this, TEXT("JoyfulControlYay"));

	//Set Mesh
	JoyfulControl->SetStaticMesh(AssetSM_JoyControl);

	//Setup (see .h)
	SetupSMComponentsWithCollision(JoyfulControl);

	//Deferred Attachment (Ty Nick W.! Actual attach gets done after blueprint stuff)
	//JoyfulControl->AttachParent = Mesh;
	// ACharacter ╡есп class USkeletalMeshComponent* Mesh;
    // F:\File\opensource\UnrealEngine-4.0\UnrealEngine-git\Engine\Source\Runtime\Engine\Private\Components\SceneComponent.cpp
	// AttachToComponent when called from a constructor is only setting up attachment and will always be treated as KeepRelative. Consider calling SetupAttachment directly instead.
	//JoyfulControl->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::KeepWorldTransform, "JoyControl");
	//JoyfulControl->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "JoyControl");
	JoyfulControl->SetupAttachment(this->GetMesh(), "JoyControl");
	// SceneComponent.h  FName AttachSocketName;
	// JoyfulControl->AttachSocketName = "JoyControl";
}