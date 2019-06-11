#pragma once

#include "GameFramework/Actor.h"	// AActor

#include "PhysicsEngine/PhysicsConstraintActor.h"
#include "PhysicsEngine/ConstraintInstance.h"	// FConstraintInstance
#include "Engine/EngineTypes.h"	// ELinearConstraintMotion
#include "PhysicsEngine/PhysicsConstraintComponent.h"	// UPhysicsConstraintComponent
#include "Containers/UnrealString.h"	// FString
#include "Components/TimelineComponent.h"	// TimelineComponent
#include "Curves/CurveFloat.h"	// CurveFloat
#include "Curves/CurveVector.h"	// CurveVector
// UE 4.19.1 warning : TAssetPtr has been renamed to TSoftObjectPtr, change to #include "UObject/SoftObjectPtr.h" and rename references
//#include "UObject/AssetPtr.h"	// TAssetPtr
#include "UObject/SoftObjectPtr.h"	// TAssetPtr
#include "MyActor.generated.h"

UCLASS(config = Game)
class AMyActor : public AActor
{
	GENERATED_BODY()

public:
	AMyActor(const FObjectInitializer& PCIP);

	// https://wiki.unrealengine.com/Static_Const,_Make_Const_Versions_of_UE4_Types
public:
	static const FLinearColor Red;
	static const FName HeadSocket;

	// https://wiki.unrealengine.com/Physics_Constraints,_Create_New_Constraints_Dynamically_During_Runtime
	void CreateNewPhysicsConstraintBetween(AStaticMeshActor* RootSMA, AStaticMeshActor* TargetSMA);

	static FORCEINLINE void SetLinearLimits(
		FConstraintInstance& Constraint,
		bool bDisableCollision,
		const uint8 XLim, const uint8 YLim, const uint8 ZLim,
		const float Size,
		bool SoftLimit = true,
		const float SoftStiffness = 0,
		const float SoftDampening = 0
		);

	static FORCEINLINE void SetAngularLimits(
		FConstraintInstance& Constraint,
		const uint8 S1Lim, const uint8 S2Lim, const uint8 TLim,
		const float Swing1LimitAngle,
		const float Swing2LimitAngle,
		const float TwistLimitAngle,

		bool SoftSwingLimit = true, bool SoftTwistLimit = true,
		const float SwingStiff = 0, const float SwingDamp = 0,
		const float TwistStiff = 0, const float TwistDamp = 0
		);

	// https://wiki.unrealengine.com/TAssetPtr_and_Asynchronous_Asset_Loading
public:
	// UE 4.19.1 warning : TAssetPtr has been renamed to TSoftObjectPtr, change to #include "UObject/SoftObjectPtr.h" and rename references
	/** Define the Asset Pointer. Don't forget to set a UPROPERTY */
	UPROPERTY(EditAnywhere)
	//TAssetPtr<AActor> MyAssetPointer;
	TSoftObjectPtr<AActor> MyAssetPointer;

	/** Define a subclass version. This will only allow you to select subclasses of the defined type. */
	UPROPERTY(EditAnywhere)
	TAssetSubclassOf<AActor> MyAssetSubclassOfPointer;

	void LoadAsset();

	// SimpleAsyncLoad which allows you to load a single asset that is strongly referenced. This means it will never be garbage collected until you unload it manually using Unload. 
	TAssetPtr<AActor> MyItem;
	FStreamableManager AssetLoader;

	void StrongReferenceLoadAsset();
	void StrongReferenceUnloadAsset();

	// RequestAsyncLoad loads an array of objects and fires a delegate when completed. This will Unload all the assets once the delegate is called, to ensure garbage collection takes place. 

	//TArray< TAssetPtr<ABaseItem> > MyItems;
	TArray< TAssetPtr<AActor> > MyItems;
	void StrongReferenceLoadAllAsset();
	void StrongReferenceUnloadAllAsset();

	void MyFunctionToBeCalledAfterAssetsAreLoaded();

	// After all this your asset(s) are ready to use.Don't forget to Get() them!
	// MyItem.Get(); // returns a pointer to the LIVE UObject

	// https://wiki.unrealengine.com/Third_Person_Camera_Zoom_C%2B%2B
protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	void CameraZoomIn();
	void CameraZoomOut();
	float CameraZoom_v;

protected:
	// APawn interface, AActor 没有这个接口
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponentParam) override;

	// https://wiki.unrealengine.com/Timeline_in_c%2B%2B
public:
	UPROPERTY()
	UTimelineComponent* ScoreTimeline;

	UPROPERTY()
	UCurveFloat* fCurve;
	UCurveVector* fCurveVector;

	//FOnTimelineFloat InterpFunction{};
	FOnTimelineFloat InterpFunction{};

	UFUNCTION()
	void TimelineFloatReturn(float val);

	void BeginPlay() override;

	float GetFloatValue();
	FVector GetVectorValue();

	// https://wiki.unrealengine.com/Timer_Macros
protected:
	UFUNCTION()
	void SomeFunction();
	void SetTimer();

public:
	// Engine\Source\Runtime\Engine\Private\GameViewportClient.cpp
	// FStringClassReference 延迟加载类
	UPROPERTY(config, EditAnywhere, Category = "Cursors", meta = (MetaClass = "UserWidget", ToolTip = "Widget to use when the Default Cursor is requested."))
	FStringClassReference DelayLoadClass;

	void DelayLoadClassHandle();
};

void AMyActor::SetLinearLimits(
	FConstraintInstance& Constraint,
	bool bDisableCollision,
	const uint8 XLim, const uint8 YLim, const uint8 ZLim,
	const float Size,
	bool SoftLimit,
	const float SoftStiffness,
	const float SoftDampening
	)
{
	Constraint.SetDisableCollision(bDisableCollision);

	switch (XLim)
	{
	case 0: 
	{
		Constraint.SetLinearXMotion(ELinearConstraintMotion::LCM_Free);
		break;
	}
	case 1: 
	{
		Constraint.SetLinearXMotion(ELinearConstraintMotion::LCM_Limited);
		break;
	}
	case 2: 
	{
		Constraint.SetLinearXMotion(ELinearConstraintMotion::LCM_Locked);
		break;
	}
	}
	switch (YLim)
	{
	case 0: 
	{
		Constraint.SetLinearYMotion(ELinearConstraintMotion::LCM_Free);
		break;
	}
	case 1: 
	{
		Constraint.SetLinearYMotion(ELinearConstraintMotion::LCM_Limited);
		break;
	}
	case 2: 
	{
		Constraint.SetLinearYMotion(ELinearConstraintMotion::LCM_Locked);
		break;
	}
	}
	switch (ZLim)
	{
	case 0: 
	{
		Constraint.SetLinearZMotion(ELinearConstraintMotion::LCM_Free);
		break;
	}
	case 1: 
	{
		Constraint.SetLinearZMotion(ELinearConstraintMotion::LCM_Limited);
		break;
	}
	case 2: 
	{
		Constraint.SetLinearZMotion(ELinearConstraintMotion::LCM_Locked);
		break;
	}
	}

	Constraint.SetLinearLimitSize(Size);

	if (SoftLimit)
	{
		//Constraint.bLinearLimitSoft_DEPRECATED = 1;
		Constraint.ProfileInstance.LinearLimit.bSoftConstraint = 1;
	}
	else
	{
		//Constraint.bLinearLimitSoft_DEPRECATED = 0;
		Constraint.ProfileInstance.LinearLimit.bSoftConstraint = 1;
	}

	//Constraint.LinearLimitStiffness_DEPRECATED = SoftStiffness;
	//Constraint.LinearLimitDamping_DEPRECATED = SoftDampening;
	Constraint.ProfileInstance.LinearLimit.Stiffness = 1;
	Constraint.ProfileInstance.LinearLimit.Damping = 1;
}
 
void AMyActor::SetAngularLimits(
	FConstraintInstance& Constraint,
	const uint8 S1Lim, const uint8 S2Lim, const uint8 TLim,
	const float Swing1LimitAngle,
	const float Swing2LimitAngle,
	const float TwistLimitAngle,

	bool SoftSwingLimit, bool SoftTwistLimit,
	const float SwingStiff, const float SwingDamp,
	const float TwistStiff, const float TwistDamp
	)
{
	switch (S1Lim)
	{
	case 0: 
	{
		Constraint.SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Free, Swing1LimitAngle);
		break;
	}
	case 1: 
	{
		Constraint.SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Limited, Swing1LimitAngle);
		break;
	}
	case 2: 
	{
		Constraint.SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, Swing1LimitAngle);
		break;
	}
	}
	switch (S2Lim)
	{
	case 0: 
	{
		Constraint.SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Free, Swing2LimitAngle);
		break;
	}
	case 1: 
	{
		Constraint.SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Limited, Swing2LimitAngle);
		break;
	}
	case 2: 
	{
		Constraint.SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, Swing2LimitAngle);
		break;
	}
	}
	switch (TLim)
	{
	case 0: 
	{
		Constraint.SetAngularTwistLimit(EAngularConstraintMotion::ACM_Free, TwistLimitAngle);
		break;
	}
	case 1: 
	{
		Constraint.SetAngularTwistLimit(EAngularConstraintMotion::ACM_Limited, TwistLimitAngle);
		break;
	}
	case 2: 
	{
		Constraint.SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, TwistLimitAngle);
		break;
	}
	}

	if (SoftSwingLimit)
	{
		//Constraint.bSwingLimitSoft_DEPRECATED = 1;
		Constraint.ProfileInstance.ConeLimit.Swing1Motion = ACM_Limited;
	}
	else
	{
		//Constraint.bSwingLimitSoft_DEPRECATED = 0;
		Constraint.ProfileInstance.ConeLimit.Swing1Motion = ACM_Free;
	}

	if (SoftTwistLimit)
	{
		//Constraint.bTwistLimitSoft_DEPRECATED = 1;
		Constraint.ProfileInstance.TwistLimit.bSoftConstraint = 1;
	}
	else
	{
		//Constraint.bTwistLimitSoft_DEPRECATED = 0;
		Constraint.ProfileInstance.TwistLimit.bSoftConstraint = 0;
	}

	//Constraint.SwingLimitStiffness_DEPRECATED = SwingStiff;
	//Constraint.SwingLimitDamping_DEPRECATED = SwingDamp;
	//Constraint.TwistLimitStiffness_DEPRECATED = TwistStiff;
	//Constraint.TwistLimitDamping_DEPRECATED = TwistDamp;
	Constraint.ProfileInstance.ConeLimit.Stiffness = SwingStiff;
	Constraint.ProfileInstance.ConeLimit.Damping = SwingDamp;
	Constraint.ProfileInstance.TwistLimit.Stiffness = TwistStiff;
	Constraint.ProfileInstance.TwistLimit.Damping = TwistDamp;
}