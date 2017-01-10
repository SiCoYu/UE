#pragma once

#include "GameFramework/Character.h"
#include "TestPluginCharacter.generated.h"

/**
 * @url http://blog.csdn.net/yangxuan0261/article/details/52098104
 */

UCLASS()
class ATestPluginCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character\'s properties
	ATestPluginCharacter();

	UPROPERTY(EditAnywhere, Category = "Test Char")
	int32           mAge;
	UPROPERTY(EditAnywhere, Category = "Test Char")
	FString         mName;
};