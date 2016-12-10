#include "MyProject.h"
#include "MyActorBase.h"

const FName        AMyActorBase::HeadSocket = FName("Head");
const FLinearColor AMyActorBase::Red = FLinearColor(1, 0, 0, 1);

AMyActorBase::AMyActorBase(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	CameraZoom_v = 300.0;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curvy(TEXT("Reference Path to your Float Curve"));
	if (Curvy.Object) {
		fCurve = Curvy.Object;
	}

	ScoreTimeline = PCIP.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("TimelineScore"));

	//Bind the Callbackfuntion for the float return value
	InterpFunction.BindUFunction(this, FName{ TEXT("TimelineFloatReturn") });
}

void AMyActorBase::CreateNewPhysicsConstraintBetween(AStaticMeshActor* RootSMA, AStaticMeshActor* TargetSMA)
{
	FConstraintInstance ConstraintInstance;

	//New Object
	UPhysicsConstraintComponent* ConstraintComp = NewObject<UPhysicsConstraintComponent>(RootSMA);
	if (!ConstraintComp)
	{
		return;
	}

	//Set Constraint Instance!
	ConstraintComp->ConstraintInstance = ConstraintInstance;

	//Set World Location
	ConstraintComp->SetWorldLocation(RootSMA->GetActorLocation());

	//Attach to Root!
	ConstraintComp->AttachToComponent(RootSMA->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform, NAME_None);

	//~~~ Init Constraint ~~~
	ConstraintComp->SetConstrainedComponents(RootSMA->GetStaticMeshComponent(), NAME_None, TargetSMA->GetStaticMeshComponent(), NAME_None);
}

void AMyActorBase::LoadAsset()
{
	// Call IsValid() to test if the asset pointer points to a live UObject
	MyAssetPointer.IsValid();

	// Call Get() to return a pointer to the UObject if one exists
	MyAssetPointer.Get();

	/** Special Note about TAssetSubclassOf Get() it returns a UClass pointer!!*/
	MyAssetSubclassOfPointer.Get();
	/** To properly use a UClass pointer you must use GetDefaultObject<T>() to get a pointer to the UObject or derived class there of */
	//MyAssetSubclassOfPointer.Get()->GetDefaultObject<MyBaseClass>();
	MyAssetSubclassOfPointer.Get()->GetDefaultObject<AActor>();

	// Call ToStringReference() to return the StringAssetReference of the asset you wish to load
	// More on this below
	MyAssetPointer.ToStringReference();
}

void AMyActorBase::StrongReferenceLoadAsset()
{
	FStringAssetReference AssetToLoad;
	AssetToLoad = MyItem.ToStringReference();
	AssetLoader.SimpleAsyncLoad(AssetToLoad);
}

void AMyActorBase::StrongReferenceUnloadAsset()
{
	FStringAssetReference AssetToLoad;
	AssetToLoad = MyItem.ToStringReference();
	AssetLoader.Unload(AssetToLoad);
}

void AMyActorBase::StrongReferenceLoadAllAsset()
{
	TArray<FStringAssetReference> AssetsToLoad;
	//for (TAssetPtr<ABaseItem>& AssetPtr : MyItems) // C++11 ranged loop
	for (TAssetPtr<AActor>& AssetPtr : MyItems) // C++11 ranged loop
	{
		AssetsToLoad.AddUnique(AssetPtr.ToStringReference());
	}
	AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &AMyActorBase::MyFunctionToBeCalledAfterAssetsAreLoaded));
}

void AMyActorBase::StrongReferenceUnloadAllAsset()
{
	TArray<FStringAssetReference> AssetsToLoad;
	//for (TAssetPtr<ABaseItem>& AssetPtr : MyItems) // C++11 ranged loop
	for (TAssetPtr<AActor>& AssetPtr : MyItems) // C++11 ranged loop
	{
		AssetLoader.Unload(AssetPtr.ToStringReference());
	}
}

void AMyActorBase::MyFunctionToBeCalledAfterAssetsAreLoaded()
{

}

void AMyActorBase::CameraZoomIn()
{
	float a = 25.0;
	CameraZoom_v = CameraZoom_v - 25.0;

	if (CameraZoom_v <= 75.0)
	{
		CameraBoom->TargetArmLength = 75.0;
		CameraZoom_v = 75.0;
	}
	else
	{
		CameraBoom->TargetArmLength = CameraZoom_v;
	}
}

void AMyActorBase::CameraZoomOut()
{
	float a = 25.0;
	CameraZoom_v = CameraZoom_v + 25.0;

	if (CameraZoom_v >= 300.0)
	{
		CameraBoom->TargetArmLength = 300.0;
		CameraZoom_v = 300.0;
	}
	else
	{
		CameraBoom->TargetArmLength = CameraZoom_v;
	}
}

//void AMyActorBase::SetupPlayerInputComponent(class UInputComponent* InputComponentParam)
//{
//	Super::SetupPlayerInputComponent(InputComponentParam);
//
//	InputComponentParam->BindAction("ZoomIn", IE_Pressed, this, &AMyActorBase::CameraZoomIn);
//	InputComponentParam->BindAction("ZoomOut", IE_Pressed, this, &AMyActorBase::CameraZoomOut);
//}

//BeginPlay
void AMyActorBase::BeginPlay()
{
	//Add the float curve to the timeline and connect it to your timelines's interpolation function
	ScoreTimeline->AddInterpFloat(fCurve, InterpFunction, FName{ TEXT("Floaty") });

	// Start your Timeline or PlayFromStart() etc, can be called anywhere in this class
	ScoreTimeline->Play();
}


//Your Callback Function for the timeline float value
void AMyActorBase::TimelineFloatReturn(float val)
{
	//You
}

float AMyActorBase::GetFloatValue()
{
	fCurve->GetFloatValue(ScoreTimeline->GetPlaybackPosition());
}

float AMyActorBase::GetVectorValue()
{
	fCurveVector->GetVectorValue(ScoreTimeline->GetPlaybackPosition());
}

void AMyActorBase::SetTimer()
{
	SETTIMER(AMyActorBase::SomeFunction, 0.25f, false);
}