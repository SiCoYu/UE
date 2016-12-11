#include "MyProject.h"
#include "EngineApi.h"
#include "MyActor.h"

const FName        AMyActor::HeadSocket = FName("Head");
const FLinearColor AMyActor::Red = FLinearColor(1, 0, 0, 1);

AMyActor::AMyActor(const class FObjectInitializer& PCIP)
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

void AMyActor::CreateNewPhysicsConstraintBetween(AStaticMeshActor* RootSMA, AStaticMeshActor* TargetSMA)
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

void AMyActor::LoadAsset()
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

void AMyActor::StrongReferenceLoadAsset()
{
	FStringAssetReference AssetToLoad;
	AssetToLoad = MyItem.ToStringReference();
	AssetLoader.SimpleAsyncLoad(AssetToLoad);
}

void AMyActor::StrongReferenceUnloadAsset()
{
	FStringAssetReference AssetToLoad;
	AssetToLoad = MyItem.ToStringReference();
	AssetLoader.Unload(AssetToLoad);
}

void AMyActor::StrongReferenceLoadAllAsset()
{
	TArray<FStringAssetReference> AssetsToLoad;
	//for (TAssetPtr<ABaseItem>& AssetPtr : MyItems) // C++11 ranged loop
	for (TAssetPtr<AActor>& AssetPtr : MyItems) // C++11 ranged loop
	{
		AssetsToLoad.AddUnique(AssetPtr.ToStringReference());
	}
	AssetLoader.RequestAsyncLoad(AssetsToLoad, FStreamableDelegate::CreateUObject(this, &AMyActor::MyFunctionToBeCalledAfterAssetsAreLoaded));
}

void AMyActor::StrongReferenceUnloadAllAsset()
{
	TArray<FStringAssetReference> AssetsToLoad;
	//for (TAssetPtr<ABaseItem>& AssetPtr : MyItems) // C++11 ranged loop
	for (TAssetPtr<AActor>& AssetPtr : MyItems) // C++11 ranged loop
	{
		AssetLoader.Unload(AssetPtr.ToStringReference());
	}
}

void AMyActor::MyFunctionToBeCalledAfterAssetsAreLoaded()
{

}

void AMyActor::CameraZoomIn()
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

void AMyActor::CameraZoomOut()
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

//void AMyActor::SetupPlayerInputComponent(class UInputComponent* InputComponentParam)
//{
//	Super::SetupPlayerInputComponent(InputComponentParam);
//
//	InputComponentParam->BindAction("ZoomIn", IE_Pressed, this, &AMyActor::CameraZoomIn);
//	InputComponentParam->BindAction("ZoomOut", IE_Pressed, this, &AMyActor::CameraZoomOut);
//}

//BeginPlay
void AMyActor::BeginPlay()
{
	//Add the float curve to the timeline and connect it to your timelines's interpolation function
	ScoreTimeline->AddInterpFloat(fCurve, InterpFunction, FName{ TEXT("Floaty") });

	// Start your Timeline or PlayFromStart() etc, can be called anywhere in this class
	ScoreTimeline->Play();
}


//Your Callback Function for the timeline float value
void AMyActor::TimelineFloatReturn(float val)
{
	//You
}

float AMyActor::GetFloatValue()
{
	return fCurve->GetFloatValue(ScoreTimeline->GetPlaybackPosition());
}

FVector AMyActor::GetVectorValue()
{
	return fCurveVector->GetVectorValue(ScoreTimeline->GetPlaybackPosition());
}

void AMyActor::SetTimer()
{
	SETTIMER(AMyActor::SomeFunction, 0.25f, false);
}

void AMyActor::SomeFunction()
{

}