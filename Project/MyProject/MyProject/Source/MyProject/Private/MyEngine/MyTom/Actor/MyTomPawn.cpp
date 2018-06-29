#include "MyProject.h"
#include "MyTomPawn.h"

AMyTomPawn::AMyTomPawn()
{
	this->mIsBindInput = false;

	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/MyAsset/MyFly/Flying/Meshes/UFO.UFO"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create static mesh component
	this->PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh0"));
	this->PlaneMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());
	this->RootComponent = this->PlaneMesh;

	// Create a spring arm component
	this->SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	this->SpringArm->SetupAttachment(RootComponent);
	this->SpringArm->TargetArmLength = 160.0f; // The camera follows at this distance behind the character	
	this->SpringArm->SocketOffset = FVector(0.f,0.f,60.f);
	this->SpringArm->bEnableCameraLag = false;
	this->SpringArm->CameraLagSpeed = 15.f;

	// Create camera component 
	this->Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	this->Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	this->Camera->bUsePawnControlRotation = false; // Don't rotate camera with controller

	// Set handling parameters
	this->Acceleration = 500.f;
	this->TurnSpeed = 50.f;
	this->MaxSpeed = 4000.f;
	this->MinSpeed = 500.f;
	this->CurrentForwardSpeed = 500.f;
}

void AMyTomPawn::Tick(float DeltaSeconds)
{
	const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaSeconds, 0.f, 0.f);

	// Move plan forwards (with sweep so we stop when we collide with things)
	this->AddActorLocalOffset(LocalMove, true);

	// Calculate change in rotation this frame
	FRotator DeltaRotation(0,0,0);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaSeconds;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaSeconds;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaSeconds;

	// Rotate plane
	this->AddActorLocalRotation(DeltaRotation);

	// Call any parent class Tick implementation
	Super::Tick(DeltaSeconds);
}

void AMyTomPawn::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// Deflect along the surface when we collide.
	// UE4 4.17: error C2660: 'AActor::GetActorRotation': function does not take 1 arguments
	//FRotator CurrentRotation = GetActorRotation(RootComponent);
	FRotator CurrentRotation = GetActorRotation();
	this->SetActorRotation(FQuat::Slerp(CurrentRotation.Quaternion(), HitNormal.ToOrientationQuat(), 0.025f));
}

void AMyTomPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (this->mIsBindInput)
	{
		check(PlayerInputComponent);

		// Bind our control axis' to callback functions
		PlayerInputComponent->BindAxis("Thrust", this, &AMyTomPawn::ThrustInput);
		PlayerInputComponent->BindAxis("MoveUp", this, &AMyTomPawn::MoveUpInput);
		PlayerInputComponent->BindAxis("MoveRight", this, &AMyTomPawn::MoveRightInput);
	}
}

void AMyTomPawn::ThrustInput(float Val)
{
	// Is there no input?
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	// If input is not held down, reduce speed
	float CurrentAcc = bHasInput ? (Val * this->Acceleration) : (-0.5f * this->Acceleration);
	// Calculate new speed
	float NewForwardSpeed = this->CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	// Clamp between MinSpeed and MaxSpeed
	this->CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, MaxSpeed);
}

void AMyTomPawn::MoveUpInput(float Val)
{
	// Target pitch speed is based in input
	float TargetPitchSpeed = (Val * TurnSpeed * -1.f);

	// When steering, we decrease pitch slightly
	TargetPitchSpeed += (FMath::Abs(CurrentYawSpeed) * -0.2f);

	// Smoothly interpolate to target pitch speed
	this->CurrentPitchSpeed = FMath::FInterpTo(this->CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void AMyTomPawn::MoveRightInput(float Val)
{
	// Target yaw speed is based on input
	float TargetYawSpeed = (Val * TurnSpeed);

	// Smoothly interpolate to target yaw speed
	this->CurrentYawSpeed = FMath::FInterpTo(this->CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);

	// Is there any left/right input?
	const bool bIsTurning = FMath::Abs(Val) > 0.2f;

	// If turning, yaw value is used to influence roll
	// If not turning, roll to reverse current roll value
	float TargetRollSpeed = bIsTurning ? (this->CurrentYawSpeed * 0.5f) : (GetActorRotation().Roll * -2.f);

	// Smoothly interpolate roll speed
	this->CurrentRollSpeed = FMath::FInterpTo(this->CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}