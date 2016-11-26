#include "MyProject.h"
#include "DeferAttachToSocketActor.h"

ADeferAttachToSocketActor::ADeferAttachToSocketActor(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	//Asset, Reference Obtained Via Right Click in Editor
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshOb_AW2(TEXT("StaticMesh'/Game/VictoryGoals/Mechs/JoyControl/JoyControl_WindTurtle.JoyControl_WindTurtle'"));

	AssetSM_JoyControl = StaticMeshOb_AW2.Object;

	//Create
	JoyfulControl = ObjectInitializer.CreateDefaultSubobject < UStaticMeshComponent >(this, TEXT("JoyfulControlYay"));

	//Set Mesh
	JoyfulControl->SetStaticMesh(AssetSM_JoyControl);

	//Setup (see .h)
	SetupSMComponentsWithCollision(JoyfulControl);

	//Deferred Attachment (Ty Nick W.! Actual attach gets done after blueprint stuff)
	JoyfulControl->AttachParent = Mesh;
	JoyfulControl->AttachSocketName = "JoyControl";
}