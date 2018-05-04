#pragma once

#include "MyProject.h"
#include "MyDataStorage.h"
#include "MyBluePrintToCppFunctionLibrary.generated.h"

class UMyBluePrintBase;

UCLASS()
class UMyBluePrintToCppFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UMyBluePrintToCppFunctionLibrary(const FObjectInitializer& ObjectInitializer);

	/**
	 * @def BlueprintPure BluePrint ���Ե���
	 * @def Category BluePrint �� Palette ����ʾ�ı�ǩ
	 */
	UFUNCTION(BlueprintPure, Category = "MyBluePrintToCppFunctionLibrary")
	static UMyBluePrintBase* getBPCtx();

	UFUNCTION(BlueprintPure, Category = "MyBluePrintToCppFunctionLibrary")
	static ACharacter* getFirstCharacter();	// ��ȡ��һ�� ACharacter �����������Լ�

	UFUNCTION(BlueprintPure, Category = "MyBluePrintToCppFunctionLibrary")
	static AMyPlayerControllerBase* GetPlayerController();
};