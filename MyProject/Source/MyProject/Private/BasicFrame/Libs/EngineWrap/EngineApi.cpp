#include "MyProject.h"
#include "EngineApi.h"
#include "Common.h"
#include "EngineData.h"
#include "MyEngine.h"
#include "Internationalization/Text.h"	// FFormatOrderedArguments
#include "MyGameInstance.h"
#include "Blueprint/UserWidget.h"	// UUserWidget
#include "GenericPlatform/GenericPlatformMisc.h"	//	ClipboardCopy
#include "Widgets/SWindow.h"	// SWindow
#include "Framework/Application/SlateApplication.h"		// FSlateApplication
#include "Application/SlateWindowHelper.h"	// FSlateWindowHelper
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Engine/Engine.h"	// FWorldContext
#include "MyLocalPlayer.h"	// UMyLocalPlayer
#include "MyPlayerController.h"	// AMyPlayerController
#include "UObject/UObjectGlobals.h"	// NewObject
#include "MyViewportClient.h"

DEFINE_LOG_CATEGORY(MyLog);

UMyGameInstance* EngineApi::getGameInstance()
{
	return Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GEngineData->getMainActor()));
}

UWorld* EngineApi::GetWorld()
{
	UWorld* World = GEngine->GetWorldFromContextObject(GEngineData->getMainActor());
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

UMyEngine* EngineApi::getEngine()
{
	return Cast<UMyEngine>(GEngine);
}

UMyGameInstance* EngineApi::getMyGameInstanceByEngine()
{
	UMyEngine* pUMyEngine = Cast<UMyEngine>(GEngine);
	UMyGameInstance* const GI = Cast<UMyGameInstance>(pUMyEngine->GameInstance);
	return GI;
}

UWorld* EngineApi::getWorldByEngine()
{
	UMyGameInstance* pUMyProjectGameInstance = getMyGameInstanceByEngine();
	UWorld* const World = pUMyProjectGameInstance->GetWorld();
	return World;
}

UMyGameInstance* EngineApi::getMyGameInstanceByController()
{
	return Cast<UMyGameInstance>(GEngineData->getMainPlayerController()->GetGameInstance());
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

AMyPlayerController* EngineApi::GetPlayerController()
{
	AMyPlayerController* TargetPC = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(GEngineData->getMainActor(), 0));
	return TargetPC;
}

FWorldContext* EngineApi::GetWorldContextByGameInstance()
{
	UMyGameInstance* GameInstance = EngineApi::getGameInstance();
	FWorldContext* const PieWorldContext = GameInstance->GetWorldContext();
	return PieWorldContext;
}

UWorld* EngineApi::GetWorldByWorldContext()
{
	FWorldContext* PieWorldContext = EngineApi::GetWorldContextByGameInstance();
	UWorld* PlayWorld = PieWorldContext->World();
	return PlayWorld;
}

UMyGameInstance* EngineApi::GetGameInstanceByWorld()
{
	UWorld* NewWorld = EngineApi::GetWorld();
	UMyGameInstance* GameInstance = Cast<UMyGameInstance>(NewWorld->GetGameInstance());
	return GameInstance;
}

UMyLocalPlayer* EngineApi::GetLocalPlayerByPlayerController()
{
	AMyPlayerController* Controller = EngineApi::GetPlayerController();
	UMyLocalPlayer* Player = Cast<UMyLocalPlayer>(Controller->Player);
	return Player;
}

ULevel* EngineApi::getCurrentLevelFromWorld()
{
	UWorld* world = EngineApi::GetWorld();
	ULevel* currentLevel = world->GetCurrentLevel();
	return currentLevel;
}

ULevel* EngineApi::getPersistentLevelFromWorld()
{
	UWorld* world = EngineApi::GetWorld();
	//ULevel* persistentLevel = world->GetPersistentLevel();
	ULevel* persistentLevel = nullptr;
	return persistentLevel;
}

UGameInstance* EngineApi::getGameInstanceFromWorld()
{
	UWorld* world = EngineApi::GetWorld();
	UGameInstance* gameInstance = world->GetGameInstance();
	return gameInstance;
}

TArray<AActor*>& EngineApi::getActorArrayFromCurrentLevel()
{
	ULevel* currentLevel = EngineApi::getCurrentLevelFromWorld();
	TArray<AActor*>& actors = currentLevel->Actors;
	return actors;
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
	return GEngineData->getMainActor()->GetInputAxisValue(InputAxisName);
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

ALevelScriptActor* EngineApi::GetLevelScriptActor(ULevel* OwnerLevel) const
{
	return GetWorld()->GetLevelScriptActor(OwnerLevel);
}

void EngineApi::GetDisplayAdapterScreenResolutions(FScreenResolutionArray& Resolutions)
{
	if (RHIGetAvailableResolutions(Resolutions, false))
	{
		for (const FScreenResolutionRHI& EachResolution : Resolutions)
		{
			UE_LOG(MyLog, Warning, TEXT("DefaultAdapter - %4d x %4d @ %d"),
				EachResolution.Width, EachResolution.Height, EachResolution.RefreshRate);
		}
	}
	else
	{
		UE_LOG(MyLog, Error, TEXT("Screen Resolutions could not be obtained"));
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
	GEngineData->getMainPlayerController()->ClientMessage(str);
}

// FText::Format
void EngineApi::Format()
{
	// {key} 通过 key 查找值
	//Set Formatted FTEXT from variable data.
	FFormatNamedArguments Args;
	//Args.Add("DayCount", SaveDetails.DayCount);    	//int32 
	//Args.Add("HP", SaveDetails.PlayerHealth); 	//int32
	Args.Add("DayCount", 1);    	//int32 
	Args.Add("HP", 1); 	//int32

	//Get Formatted FText back!
	FText DayCount = FText::Format(NSLOCTEXT("Solus", "Day", "Day {DayCount}"), Args);
	FText Health = FText::Format(NSLOCTEXT("Solus", "HP", "HP {HP}"), Args);

	Args.Empty();
	Args.Add(TEXT("GameName"), FText::FromString(FString("aaaaa")));
	Args.Add(TEXT("PlatformBits"), FText::FromString(FString("bbbbb")));
	Args.Add(TEXT("RHIName"), FText::FromName(FName("fffff")));


	const FText ViewportName = FText::Format(NSLOCTEXT("UnrealEd", "PlayInEditor_RHI_F", "{GameName} Game Preview {NetMode} ({PlatformBits}-bit/{RHIName})"), Args);

	// {key} 通过 key 查找值
	FFormatOrderedArguments orderArgs;
	orderArgs.Empty();
	//Args.Add(SaveDetails.DayCount);    	//int32 
	//Args.Add(SaveDetails.PlayerHealth); 	//int32
	orderArgs.Add(1);    	//int32 
	orderArgs.Add(1); 	//int32
	const FText OrderDayCount = FText::Format(NSLOCTEXT("Solus","Day","Day {0}"), Args);
	const FText OrderHealth = FText::Format(NSLOCTEXT("Solus","HP","HP {1}"),  Args);
}

FString EngineApi::GetWorldAssetPackageName(ULevelStreaming* StreamedLevel)
{
	return StreamedLevel->GetWorldAssetPackageName();
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

void EngineApi::ExecuteConsoleCommand(const FString& Command)
{
	APlayerController* TargetPC = EngineApi::GetPlayerController();
	if (TargetPC)
	{
		TargetPC->ConsoleCommand(Command, true);
	}
}

void EngineApi::AddToViewport(UUserWidget* userWidget)
{
	if (nullptr != userWidget)
	{
		userWidget->AddToViewport();
	}
}

void EngineApi::ClipboardCopy(const TCHAR* Str)
{
	FPlatformMisc::ClipboardCopy(Str);
}

void EngineApi::ClipboardPaste(class FString& Dest)
{
	FPlatformMisc::ClipboardPaste(Dest);
}

TArray< TSharedRef<class SWindow> > EngineApi::GetInteractiveTopLevelWindows()
{
	return FSlateApplication::Get().GetInteractiveTopLevelWindows();
}

bool EngineApi::FindPathToWidget(TSharedRef<const SWidget> InWidget, FWidgetPath& OutWidgetPath, EVisibility VisibilityFilter)
{
	return FSlateApplication::Get().FindPathToWidget(InWidget, OutWidgetPath, VisibilityFilter);
}

bool EngineApi::FindPathToWidget(const TArray<TSharedRef<SWindow>>& WindowsToSearch, TSharedRef<const SWidget> InWidget, FWidgetPath& OutWidgetPath, EVisibility VisibilityFilter)
{
	return FSlateWindowHelper::FindPathToWidget(EngineApi::GetInteractiveTopLevelWindows(), InWidget, OutWidgetPath, VisibilityFilter);
}

bool EngineApi::SetKeyboardFocus(const TSharedPtr<SWidget>& OptionalWidgetToFocus, EFocusCause ReasonFocusIsChanging)
{
	return FSlateApplication::Get().SetKeyboardFocus(OptionalWidgetToFocus, ReasonFocusIsChanging);
}

void EngineApi::SetUserFocusToGameViewport(uint32 UserIndex, EFocusCause ReasonFocusIsChanging)
{
	FSlateApplication::Get().SetUserFocusToGameViewport(UserIndex, ReasonFocusIsChanging);
}

int32 EngineApi::GetUserIndexForKeyboard()
{
	return FSlateApplication::Get().GetUserIndexForKeyboard();
}

FString EngineApi::UrlEncode(const FString& UnencodedString)
{
	//return FPlatformHttp::UrlEncode(UnencodedString);
	return "";
}

//bool EngineApi::OpenLauncher(const FOpenLauncherOptions& Options)
//{
//	FString CrashedAppPathUri;
//	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
//	FOpenLauncherOptions OpenOptions(FString::Printf(TEXT("apps/%s"), *CrashedAppPathUri));
//	OpenOptions.bSilent = true;
//	DesktopPlatform->OpenLauncher(OpenOptions);
//}

FProcHandle EngineApi::CreateProc(const TCHAR* URL, const TCHAR* Parms, bool bLaunchDetached, bool bLaunchHidden, bool bLaunchReallyHidden, uint32* OutProcessID, int32 PriorityModifier, const TCHAR* OptionalWorkingDirectory, void* PipeWriteChild, void * PipeReadChild)
{
	return FPlatformProcess::CreateProc(URL, Parms, bLaunchDetached, bLaunchHidden, bLaunchReallyHidden, OutProcessID, PriorityModifier, OptionalWorkingDirectory, PipeWriteChild, PipeReadChild);
}

UObject* EngineApi::StaticLoadObject(UClass* Class, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename, uint32 LoadFlags, UPackageMap* Sandbox, bool bAllowObjectReconciliation)
{
	Class->GetDefaultObject(); // force the CDO to be created if it hasn't already
	UObject* ObjectPtr = ::StaticLoadObject(Class, InOuter, Name, Filename, LoadFlags, Sandbox, bAllowObjectReconciliation);
	if (ObjectPtr)
	{
		ObjectPtr->AddToRoot();
	}
	return ObjectPtr;
}

UClass* EngineApi::StaticLoadClass(UClass* BaseClass, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename, uint32 LoadFlags, UPackageMap* Sandbox)
{
	UClass* LoadedClass = ::StaticLoadClass(BaseClass, InOuter, Name, Filename, LoadFlags, Sandbox);
	if (LoadedClass)
	{
		LoadedClass->AddToRoot();
	}
	return LoadedClass;
}

FString EngineApi::GetPathName(const UObject* curObj, const UObject* StopOuter/*=NULL*/)
{
	FString Result;
	Result = curObj->GetPathName(StopOuter);
	return Result;
}

UMyViewportClient* const EngineApi::GetGameViewportClient()
{
	UMyGameInstance* GameInstance = EngineApi::getGameInstance();
	UMyViewportClient* const GameViewport = Cast<UMyViewportClient>(GameInstance->GetGameViewportClient());
	return GameViewport;
}

FViewport* const EngineApi::GetViewport()
{
	UMyGameInstance* GameInstance = EngineApi::getGameInstance();
	UGameViewportClient* const GameViewport = GameInstance->GetGameViewportClient();
	if (GameViewport != NULL && GameViewport->Viewport != NULL)
	{
		return GameViewport->Viewport;
	}

	return nullptr;
}

void EngineApi::EnableScreenSaver(bool bEnable)
{
	GEngine->EnableScreenSaver(bEnable);
}

int32 EngineApi::LoadPackageAsync(const FString& InName, FLoadPackageAsyncDelegate InCompletionDelegate, TAsyncLoadPriority InPackagePriority, EPackageFlags InPackageFlags)
{
	return ::LoadPackageAsync(InName, InCompletionDelegate, InPackagePriority, InPackageFlags);
}

void EngineApi::CancelAsyncLoading()
{
	::CancelAsyncLoading();
}

float EngineApi::GetAsyncLoadPercentage(const FName& PackageName)
{
	return ::GetAsyncLoadPercentage(PackageName);
}

bool EngineApi::IsGarbageCollecting()
{
	return ::IsGarbageCollecting();
}

void EngineApi::CollectGarbage(EObjectFlags KeepFlags, bool bPerformFullPurge)
{
	::CollectGarbage(KeepFlags, bPerformFullPurge);
}

bool EngineApi::TryCollectGarbage(EObjectFlags KeepFlags, bool bPerformFullPurge)
{
	return ::TryCollectGarbage(KeepFlags, bPerformFullPurge);
}

const FWorldContext* EngineApi::GetWorldContextFromGameViewport(const UGameViewportClient *InViewport)
{
	return GEngine->GetWorldContextFromGameViewport(InViewport);
}

void EngineApi::LoadStreamLevel(const UObject* WorldContextObject, FName LevelName, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, FLatentActionInfo LatentInfo)
{
	return UGameplayStatics::LoadStreamLevel(WorldContextObject, LevelName, bMakeVisibleAfterLoad, bShouldBlockOnLoad, LatentInfo);
}

APlayerController* EngineApi::GetPrimaryPlayerController()
{
	return EngineApi::getGameInstance()->GetPrimaryPlayerController();
}

void EngineApi::SetClientTravel(UWorld *InWorld, const TCHAR* NextURL, ETravelType InTravelType)
{
	GEngine->SetClientTravel(InWorld, NextURL, InTravelType);
}

static bool ServerTravel(const FString& InURL, bool bAbsolute, bool bShouldSkipGameNotify)
{
	EngineApi::GetWorld()->ServerTravel(InURL, bAbsolute, bShouldSkipGameNotify);
}