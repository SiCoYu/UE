#include "MyProject.h"
#include "EngineApi.h"
#include "Common.h"
#include "EngineData.h"
#include "MyProjectEngine.h"
#include "MyProjectGameInstance.h"

UGameInstance* EngineApi::getGameInstance()
{
	return UGameplayStatics::GetGameInstance(g_pEngineData->getMainActor());
}

UWorld* EngineApi::GetWorld()
{
	UWorld* World = GEngine->GetWorldFromContextObject(g_pEngineData->getMainActor());
	return World;
}

void EngineApi::showCursor()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetFirstPlayerController()->bShowMouseCursor = true;
	}
	FSlateApplication::Get().GetPlatformApplication()->Cursor->Show(true);
}

void EngineApi::addEventHandle(UButton* pBtn, UObject* pFuncObj, FName funcName)
{
	TScriptDelegate<FWeakObjectPtr> ptrDelegate;
	ptrDelegate.BindUFunction(pFuncObj, funcName);
	pBtn->OnClicked.Add(ptrDelegate);
}

UMyProjectEngine* EngineApi::getEngine()
{
	return Cast<UMyProjectEngine>(GEngine);
}

UMyProjectGameInstance* EngineApi::getMyProjectGameInstanceByEngine()
{
	UMyProjectEngine* pUMyProjectEngine = Cast<UMyProjectEngine>(GEngine);
	UMyProjectGameInstance* const GI = Cast<UMyProjectGameInstance>(pUMyProjectEngine->GameInstance);
	return GI;
}

UWorld* EngineApi::getWorldByEngine()
{
	UMyProjectGameInstance* pUMyProjectGameInstance = getMyProjectGameInstanceByEngine();
	UWorld* const World = pUMyProjectGameInstance->GetWorld();
	return World;
}

static UMyProjectGameInstance* getMyProjectGameInstanceByController()
{
	return g_pEngineData->getMainPlayerController()->GetGameInstance();
}

ACharacter* EngineApi::getFirstCharacter()
{
	ACharacter* Character = nullptr;
	APlayerController* PC = nullptr;
	UWorld* World = GetWorld();
	if (World)
	{
		PC = World->GetFirstPlayerController();
		if (PC != nullptr)
		{
			Character = Cast<ACharacter>(PC->GetPawn());
		}
	}

	return Character;
}

float EngineApi::getUTCSec()
{
	//return g_pEngineApi->getWorld()->GetRealTimeSeconds();
	return EngineApi::GetWorld()->GetTimeSeconds();
}

float EngineApi::GetRealTimeSeconds()
{
	return EngineApi::GetWorld()->GetRealTimeSeconds();
}

void EngineApi::InsertMountPoint(const FString& RootPath, const FString& ContentPath)
{
	FPackageName::RegisterMountPoint(RootPath, ContentPath);
}

bool EngineApi::FileExists(const FString& InPath)
{
	return FPaths::FileExists(InPath);
}

bool EngineApi::PackageExists(const FString& InPackageFilename)
{
	//FString fileName = FPackageName::LongPackageNameToFilename(InPackageFilename);	// 转换包的名字到相对当前工作目录的目录
	//FString OutFilename;
	//return FPackageName::FindPackageFileWithoutExtension(fileName, OutFilename);
	return FPackageName::DoesPackageExist(InPackageFilename);
}

FString EngineApi::GameUserDir()
{
	return FPaths::GameUserDir();
}

void EngineApi::SetActive(UWidget* target, bool bshow)
{
	if (bshow)
	{
		target->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		target->SetVisibility(ESlateVisibility::Hidden);
	}
}

void EngineApi::Destroy(UWidget* obj)
{

}

void EngineApi::UnloadUnusedAssets()
{

}

void EngineApi::SetParent(UWidget*child, UPanelWidget* parent, bool worldPositionStays)
{
	parent->AddChild(child);
}

void EngineApi::SetContentForSlot(UUserWidget* userWidget, FName SlotName, UWidget* Content)
{
	userWidget->SetContentForSlot(SlotName, Content);
}

//void EngineApi::ConvertString(const FString& Source, icu::UnicodeString& Destination, const bool ShouldNullTerminate)
//{
//	ICUUtilities::ConvertString(Source, Destination, ShouldNullTerminate);
//}

bool EngineApi::LineTraceSingleByChannel(UWorld* World, struct FHitResult& OutHit, const FVector& Start, const FVector& End, ECollisionChannel TraceChannel, const FCollisionQueryParams& Params, const FCollisionResponseParams& ResponseParam)
{
	return World->LineTraceSingleByChannel(OutHit, Start, End, TraceChannel, Params, ResponseParam);
}

bool EngineApi::SweepTestByChannel(UWorld* World, const FVector& Start, const FVector& End, const FQuat& Rot, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params, const FCollisionResponseParams& ResponseParam)
{
	return World->SweepTestByChannel(Start, End, Rot, TraceChannel, CollisionShape, Params, ResponseParam);
}

bool EngineApi::OverlapBlockingTestByChannel(UWorld* World, const FVector& Pos, const FQuat& Rot, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params, const FCollisionResponseParams& ResponseParam)
{
	return World->OverlapBlockingTestByChannel(Pos, Rot, TraceChannel, CollisionShape, Params, ResponseParam);
}

float EngineApi::GetAxisValue(UInputComponent* pUInputComponent, const FName AxisName)
{
	return pUInputComponent->GetAxisValue(AxisName);
}

float EngineApi::GetInputAxisValue(AActor* pAActor, const FName InputAxisName)
{
	return pAActor->GetInputAxisValue(InputAxisName);
}

float EngineApi::GetInputAxisValue(const FName InputAxisName)
{
	return g_pEngineData->getMainActor()->GetInputAxisValue(InputAxisName);
}

FTransform& EngineApi::getTransform(USceneComponent* pUSceneComponent)
{
	return pUSceneComponent->ComponentToWorld;
}

void EngineApi::LaunchURL(FString url)
{
	FString TheURL = "http://www.google.com/";
	FPlatformProcess::LaunchURL(*TheURL, nullptr, nullptr);
}

bool EngineApi::isValid(UObject* pObj)
{
	if (pObj && pObj->IsValidLowLevel())
	{
		return true;
	}

	return false;
}

float EngineApi::DistanceOfActorToThisMeshSurface(UStaticMeshComponent* StaticMeshComponent, AActor* TestActor, FVector& ClosestSurfacePoint) const
{
	if (!TestActor) return 0;
	if (!TestActor->IsValidLowLevel()) return 0;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//Dist of Actor to Surface, retrieve closest Surface Point to Actor
	return StaticMeshComponent->GetDistanceToCollision(
		TestActor->GetActorLocation(), ClosestSurfacePoint
		);
}

void EngineApi::SetMassScale(UStaticMeshComponent* StaticMeshComponent, const float& NewScale)
{
	if (!StaticMeshComponent) return;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	FBodyInstance* BodyInst = StaticMeshComponent->GetBodyInstance();

	if (!BodyInst) return;
	//~~~~~~~~~~~~~~~~~~~~~~~~

	// New Scale 
	BodyInst->MassScale = NewScale;

	// Trigger Update! 
	BodyInst->UpdateMassProperties();
}

ALevelScriptActor* EngineApi::GetLevelScriptActor(class ULevel* OwnerLevel)
{
	return GetWorld()->GetLevelScriptActor(OwnerLevel);
}

void EngineApi::GetDisplayAdapterScreenResolutions(FScreenResolutionArray& Resolutions)
{
	if (RHIGetAvailableResolutions(Resolutions, false))
	{
		for (const FScreenResolutionRHI& EachResolution : Resolutions)
		{
			UE_LOG(YourLog, Warning, TEXT("DefaultAdapter - %4d x %4d @ %d"),
				EachResolution.Width, EachResolution.Height, EachResolution.RefreshRate);
		}
	}
	else
	{
		UE_LOG(YourLog, Error, TEXT("Screen Resolutions could not be obtained"));
	}
}

bool EngineApi::IsTextValid(FText MyText)
{
	if (MyText.IsEmpty())
	{
		return true;
	}
	return false;
}

void EngineApi::ClientMessage(FString str)
{
	g_pEngineData->getMainPlayerController()->ClientMessage(str);
}

void EngineApi::Format()
{
	//Set Formatted FTEXT from variable data.
	FFormatNamedArguments Args;
	Args.Add("DayCount", SaveDetails.DayCount);    	//int32 
	Args.Add("HP", SaveDetails.PlayerHealth); 	//int32

	//Get Formatted FText back!
	FText DayCount = FText::Format(NSLOCTEXT("Solus", "Day", "Day {DayCount}"), Args);
	FText Health = FText::Format(NSLOCTEXT("Solus", "HP", "HP {HP}"), Args);

	FFormatOrderedArguments Args;
	Args.Add(SaveDetails.DayCount);    	//int32 
	Args.Add(SaveDetails.PlayerHealth); 	//int32
	DayCount = FText::Format(NSLOCTEXT("Solus","Day","Day {0}"), Args);
	Health 	 = FText::Format(NSLOCTEXT("Solus","HP","HP {1}"),  Args);
}

FString EngineApi::GetWorldAssetPackageName(ULevelStreaming* StreamedLevel)
{
	return StreamedLevel->GetWorldAssetPackageName()
}

float EngineApi::GetTimeSeconds()
{
	return GetWorld()->GetTimeSeconds();
}

FTimerManager& EngineApi::GetWorldTimerManager()
{
	return GetWorld()->GetTimerManager();
}

void EngineApi::AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector)
{
	AActor::AddReferencedObjects(InThis, Collector);
}

ULevel* EngineApi::GetLevel(AActor* actor)
{ 
	return Cast<ULevel>(actor->GetOuter());
}