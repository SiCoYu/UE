#pragma once

#include "MyCharacterBase.h"
#include "MyTPCharacter.generated.h"

/**
 AMyCharacter 这个必须保存，基本所有全局对象都是根据 AMyCharacter 从 UGameplayStatics 中获取的
 @brief 如果在 Blueprint 中已经使用 AMyCharacter 作为 Parent 类，这时候重新将 AMyCharacter 类命名为 AMyTPCharacter ，需要在 MyProject\Config\DefaultEngine.ini 文件中添加
 +ActiveClassRedirects=(OldClassName="MyCharacter",NewClassName="MyTPCharacter")
 */

class UMyAnimInstanceBase;

//UCLASS(config=Game, Abstract)
UCLASS(config=Game)
class AMyTPCharacter : public AMyCharacterBase
{
	GENERATED_BODY()

	///** Camera boom positioning the camera behind the character */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class USpringArmComponent* CameraBoom;

	///** Follow camera */
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	//class UCameraComponent* FollowCamera;
public:
	AMyTPCharacter(const FObjectInitializer& ObjectInitializer);

//	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
//	float BaseTurnRate;
//
//	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
//	float BaseLookUpRate;
//
//private:
//	void TestUI();
//
//protected:
//	/** Called for forwards/backward input */
//	void MoveForward(float Value);
//
//	/** Called for side to side input */
//	void MoveRight(float Value);
//
//	/** 
//	 * Called via input to turn at a given rate. 
//	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
//	 */
//	void TurnAtRate(float Rate);
//
//	/**
//	 * Called via input to turn look up/down at a given rate. 
//	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
//	 */
//	void LookUpAtRate(float Rate);
//
//	/** Handler for when a touch input begins. */
//	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
//
//	/** Handler for when a touch input stops. */
//	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);
//
//	virtual void BeginPlay();
//	virtual void Tick(float DeltaTime) override;
//
//protected:
//	// APawn interface
//	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponentParam) override;
//	// End of APawn interface
//
//public:
//	/** Returns CameraBoom subobject **/
//	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
//	/** Returns FollowCamera subobject **/
//	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
//
//public:
//	bool IsAlive();

	virtual const UMyAnimInstanceBase* const GetAnimInstance() override;
};