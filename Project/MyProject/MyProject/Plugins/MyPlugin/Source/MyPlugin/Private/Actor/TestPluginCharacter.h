#pragma once

#include "GameFramework/Character.h"
//#include "MyProjectEditor/Private/BaseFrame/UnitTest/TestModuleReference/TestModuleReferenceSubDir/TestModuleReferenceSubDir.h"
#include "BaseFrame/UnitTest/TestModuleReference/TestModuleReferenceSubDir/TestModuleReferenceSubDir.h"
#include "TestPluginCharacter.generated.h"

/**
 * @url http://blog.csdn.net/yangxuan0261/article/details/52098104
 */

UCLASS()
class ATestPluginCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	TestModuleReferenceSubDir mTestModuleReferenceSubDir;

public:
	// Sets default values for this character\'s properties
	ATestPluginCharacter();

	UPROPERTY(EditAnywhere, Category = "Test Char")
	int32           mAge;
	UPROPERTY(EditAnywhere, Category = "Test Char")
	FString         mName;
};