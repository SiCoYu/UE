#pragma once

#include "MyProject.h"
#include "GameFramework/Actor.h"
#include "TestUseEnum.generated.h"

/**
 * @brief https://wiki.unrealengine.com/Enums_For_Both_C%2B%2B_and_BP
 */

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EVictoryEnum : uint8
{
	VE_Dance 	UMETA(DisplayName = "Dance"),
	VE_Rain 	UMETA(DisplayName = "Rain"),
	VE_Song	UMETA(DisplayName = "Song")
};

UCLASS()
class ATestUseEnum : public AActor
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Enum)
	EVictoryEnum VictoryEnum;

	//Rest of Class Code
public:
	void TestEnum(EVictoryEnum EnumValue);
	FString GetVictoryEnumAsString(EVictoryEnum EnumValue);

	template<typename TEnum>
	static FORCEINLINE FString GetEnumValueToString(const FString& Name, TEnum Value)
	{
		const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!enumPtr)
		{
			return FString("Invalid");
		}

		return enumPtr->GetEnumName((int32)Value);
	}

	// Example usage
	//GetEnumValueAsString<EVictoryEnum>("EVictoryEnum", VictoryEnum)));


	template <typename EnumType>
	static FORCEINLINE EnumType GetEnumValueFromString(const FString& EnumName, const FString& String)
	{
		UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
		if (!Enum)
		{
			return EnumType(0);
		}
		return (EnumType)Enum->FindEnumIndex(FName(*String));
	}

	//Sample Usage
	//FString ParseLine = GetEnumValueAsString<EChallenge>("EChallenge", VictoryEnumValue))); //To String
	//EChallenge Challenge = GetEnumValueFromString<EChallenge>("EChallenge", ParseLine);  //Back From String!
};