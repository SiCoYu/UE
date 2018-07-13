#include "MyProject.h"
#include "UtilEngineWrap.h"
#include "Prequisites.h"
#include "EngineData.h"
#include "MyGameEngineBase.h"
#include "Internationalization/Text.h"	// FFormatOrderedArguments
#include "MyGameInstanceBase.h"
#include "Blueprint/UserWidget.h"	// UUserWidget
// warning C4996: 'FGenericPlatformMisc::ClipboardPaste': FPlatformMisc::ClipboardPaste() has been superseded by FPlatformApplicationMisc::ClipboardPaste() Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
//#include "GenericPlatform/GenericPlatformMisc.h"	//	ClipboardCopy
#include "HAL/PlatformApplicationMisc.h"	//	ClipboardCopy
#include "Widgets/SWindow.h"	// SWindow
#include "Framework/Application/SlateApplication.h"		// FSlateApplication
#include "Application/SlateWindowHelper.h"	// FSlateWindowHelper
#include "GenericPlatform/GenericPlatformHttp.h"
#include "Engine/Engine.h"	// FWorldContext
#include "MyLocalPlayerBase.h"	// UMyLocalPlayer
#include "MyPlayerControllerBase.h"	// AMyPlayerController
#include "UObject/UObjectGlobals.h"	// NewObject
#include "MyGameViewportClientBase.h"
#include "Materials/MaterialInstance.h"	// UMaterialInstance
#include "Components/MeshComponent.h"	// UMeshComponent
#include "CoreGlobals.h"	// IsInAsyncLoadingThread
#include "Components/Widget.h"	// UWidget
#include "Components/PrimitiveComponent.h"		// UPrimitiveComponent

DEFINE_LOG_CATEGORY(MyLog);

UMyGameInstanceBase* UtilEngineWrap::GetGameInstance()
{
	return Cast<UMyGameInstanceBase>(UGameplayStatics::GetGameInstance(GEngineData->getMainActor()));
}

UWorld* UtilEngineWrap::GetWorld()
{
	// UE4 4.17
	// warning C4996: 'UEngine::GetWorldFromContextObject': GetWorldFromContextObject(Object) and GetWorldFromContextObject(Object, boolean) are replaced by GetWorldFromContextObject(Object, Enum) or GetWorldFromContextObjectChecked(Object) Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//UWorld* World = GEngine->GetWorldFromContextObject(GEngineData->getMainActor());
	UWorld* World = GEngine->GetWorldFromContextObject(GEngineData->getMainActor(), EGetWorldErrorMode::LogAndReturnNull);
	return World;
}

void UtilEngineWrap::showCursor()
{
	UWorld* World = GetWorld();

	if (World)
	{
		World->GetFirstPlayerController()->bShowMouseCursor = true;
	}

	FSlateApplication::Get().GetPlatformApplication()->Cursor->Show(true);
}

void UtilEngineWrap::addEventHandle(UButton* pBtn, UObject* pFuncObj, FName funcName)
{
	TScriptDelegate<FWeakObjectPtr> ptrDelegate;
	ptrDelegate.BindUFunction(pFuncObj, funcName);
	pBtn->OnClicked.Add(ptrDelegate);
}

UMyGameEngineBase* UtilEngineWrap::getEngine()
{
	return Cast<UMyGameEngineBase>(GEngine);
}

UMyGameInstanceBase* UtilEngineWrap::getMyGameInstanceByEngine()
{
	UMyGameEngineBase* pUMyEngine = Cast<UMyGameEngineBase>(GEngine);
	UMyGameInstanceBase* const GI = Cast<UMyGameInstanceBase>(pUMyEngine->GameInstance);
	return GI;
}

UWorld* UtilEngineWrap::getWorldByEngine()
{
	UMyGameInstanceBase* pUMyProjectGameInstance = getMyGameInstanceByEngine();
	UWorld* const World = pUMyProjectGameInstance->GetWorld();
	return World;
}

UMyGameInstanceBase* UtilEngineWrap::getMyGameInstanceByController()
{
	return Cast<UMyGameInstanceBase>(GEngineData->getMainPlayerController()->GetGameInstance());
}

APawn* UtilEngineWrap::getFirstCharacter()
{
	APawn* Character = nullptr;
	APlayerController* PC = nullptr;
	UWorld* World = GetWorld();

	if (World)
	{
		PC = World->GetFirstPlayerController();
		if (PC != nullptr)
		{
			Character = Cast<APawn>(PC->GetPawn());
		}
	}

	return Character;
}

AMyPlayerControllerBase* UtilEngineWrap::GetPlayerController()
{
	AMyPlayerControllerBase* TargetPC = Cast<AMyPlayerControllerBase>(UGameplayStatics::GetPlayerController(GEngineData->getMainActor(), 0));
	return TargetPC;
}

FWorldContext* UtilEngineWrap::GetWorldContextByGameInstance()
{
	UMyGameInstanceBase* GameInstance = UtilEngineWrap::GetGameInstance();
	FWorldContext* const PieWorldContext = GameInstance->GetWorldContext();
	return PieWorldContext;
}

UWorld* UtilEngineWrap::GetWorldByWorldContext()
{
	FWorldContext* PieWorldContext = UtilEngineWrap::GetWorldContextByGameInstance();
	UWorld* PlayWorld = PieWorldContext->World();
	return PlayWorld;
}

UMyGameInstanceBase* UtilEngineWrap::GetGameInstanceByWorld()
{
	UWorld* NewWorld = UtilEngineWrap::GetWorld();
	UMyGameInstanceBase* GameInstance = Cast<UMyGameInstanceBase>(NewWorld->GetGameInstance());
	return GameInstance;
}

UMyLocalPlayerBase* UtilEngineWrap::GetLocalPlayerByPlayerController()
{
	AMyPlayerControllerBase* Controller = UtilEngineWrap::GetPlayerController();
	UMyLocalPlayerBase* Player = Cast<UMyLocalPlayerBase>(Controller->Player);
	return Player;
}

ULevel* UtilEngineWrap::getCurrentLevelFromWorld()
{
	UWorld* world = UtilEngineWrap::GetWorld();
	ULevel* currentLevel = world->GetCurrentLevel();
	return currentLevel;
}

ULevel* UtilEngineWrap::getPersistentLevelFromWorld()
{
	UWorld* world = UtilEngineWrap::GetWorld();
	//ULevel* persistentLevel = world->GetPersistentLevel();
	ULevel* persistentLevel = nullptr;
	return persistentLevel;
}

UGameInstance* UtilEngineWrap::getGameInstanceFromWorld()
{
	UWorld* world = UtilEngineWrap::GetWorld();
	UGameInstance* gameInstance = world->GetGameInstance();
	return gameInstance;
}

TArray<AActor*>& UtilEngineWrap::getActorArrayFromCurrentLevel()
{
	ULevel* currentLevel = UtilEngineWrap::getCurrentLevelFromWorld();
	TArray<AActor*>& actors = currentLevel->Actors;
	return actors;
}

float UtilEngineWrap::getUTCSec()
{
	//return g_pEngineApi->getWorld()->GetRealTimeSeconds();
	return UtilEngineWrap::GetWorld()->GetTimeSeconds();
}

float UtilEngineWrap::GetRealTimeSeconds()
{
	return UtilEngineWrap::GetWorld()->GetRealTimeSeconds();
}

void UtilEngineWrap::InsertMountPoint(const FString& RootPath, const FString& ContentPath)
{
	FPackageName::RegisterMountPoint(RootPath, ContentPath);
}

bool UtilEngineWrap::FileExists(const FString& InPath)
{
	return FPaths::FileExists(InPath);
}

bool UtilEngineWrap::PackageExists(const FString& InPackageFilename)
{
	//FString fileName = FPackageName::LongPackageNameToFilename(InPackageFilename);	// 转换包的名字到相对当前工作目录的目录
	//FString OutFilename;
	//return FPackageName::FindPackageFileWithoutExtension(fileName, OutFilename);
	return FPackageName::DoesPackageExist(InPackageFilename);
}

FString UtilEngineWrap::GameUserDir()
{
	// warning C4996: 'FPaths::GameUserDir': FPaths::GameUserDir() has been superseded by FPaths::ProjectUserDir(). Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//return FPaths::GameUserDir();
	return FPaths::ProjectUserDir();
}

void UtilEngineWrap::SetActive(UWidget* target, bool bshow)
{
	if (nullptr != target)
	{
		if (bshow)
		{
			if (!target->IsVisible())
			{
				target->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else
		{
			if (target->IsVisible())
			{
				target->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void UtilEngineWrap::Destroy(UWidget* obj)
{

}

void UtilEngineWrap::UnloadUnusedAssets()
{

}

void UtilEngineWrap::SetParent(UWidget*child, UPanelWidget* parent, bool worldPositionStays)
{
	parent->AddChild(child);
}

void UtilEngineWrap::SetContentForSlot(UUserWidget* userWidget, FName SlotName, UWidget* Content)
{
	userWidget->SetContentForSlot(SlotName, Content);
}

//void UtilEngineWrap::ConvertString(const FString& Source, icu::UnicodeString& Destination, const bool ShouldNullTerminate)
//{
//	ICUUtilities::ConvertString(Source, Destination, ShouldNullTerminate);
//}

bool UtilEngineWrap::LineTraceSingleByChannel(UWorld* World, struct FHitResult& OutHit, const FVector& Start, const FVector& End, ECollisionChannel TraceChannel, const FCollisionQueryParams& Params, const FCollisionResponseParams& ResponseParam)
{
	return World->LineTraceSingleByChannel(OutHit, Start, End, TraceChannel, Params, ResponseParam);
}

bool UtilEngineWrap::SweepTestByChannel(UWorld* World, const FVector& Start, const FVector& End, const FQuat& Rot, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params, const FCollisionResponseParams& ResponseParam)
{
	return World->SweepTestByChannel(Start, End, Rot, TraceChannel, CollisionShape, Params, ResponseParam);
}

bool UtilEngineWrap::OverlapBlockingTestByChannel(UWorld* World, const FVector& Pos, const FQuat& Rot, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params, const FCollisionResponseParams& ResponseParam)
{
	return World->OverlapBlockingTestByChannel(Pos, Rot, TraceChannel, CollisionShape, Params, ResponseParam);
}

float UtilEngineWrap::GetAxisValue(UInputComponent* pUInputComponent, const FName AxisName)
{
	return pUInputComponent->GetAxisValue(AxisName);
}

float UtilEngineWrap::GetInputAxisValue(AActor* pAActor, const FName InputAxisName)
{
	return pAActor->GetInputAxisValue(InputAxisName);
}

float UtilEngineWrap::GetInputAxisValue(const FName InputAxisName)
{
	return GEngineData->getMainActor()->GetInputAxisValue(InputAxisName);
}

FTransform& UtilEngineWrap::getTransform(USceneComponent* pUSceneComponent)
{
	// UE4 4.17
	// warning C4996: 'USceneComponent::ComponentToWorld': ComponentToWorld will be made private, use GetComponentTransform() instead. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//return pUSceneComponent->ComponentToWorld;
	return (FTransform&)pUSceneComponent->GetComponentTransform();
}

void UtilEngineWrap::LaunchURL(FString url)
{
	FString TheURL = "http://www.google.com/";
	FPlatformProcess::LaunchURL(*TheURL, nullptr, nullptr);
}

bool UtilEngineWrap::isValid(UObject* pObj)
{
	bool ret = false;

	if (pObj && pObj->IsValidLowLevel())
	{
		ret = true;
	}

	return ret;
}

float UtilEngineWrap::DistanceOfActorToThisMeshSurface(UStaticMeshComponent* StaticMeshComponent, AActor* TestActor, FVector& ClosestSurfacePoint) const
{
	if (!TestActor) return 0;
	if (!TestActor->IsValidLowLevel()) return 0;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	//Dist of Actor to Surface, retrieve closest Surface Point to Actor
	return StaticMeshComponent->GetDistanceToCollision(
		TestActor->GetActorLocation(), ClosestSurfacePoint
		);
}

void UtilEngineWrap::SetMassScale(UStaticMeshComponent* StaticMeshComponent, const float& NewScale)
{
	if (!StaticMeshComponent)
	{
		return;
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	FBodyInstance* BodyInst = StaticMeshComponent->GetBodyInstance();

	if (!BodyInst)
	{
		return;
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~

	// New Scale 
	BodyInst->MassScale = NewScale;

	// Trigger Update! 
	BodyInst->UpdateMassProperties();
}

ALevelScriptActor* UtilEngineWrap::GetLevelScriptActor(ULevel* OwnerLevel) const
{
	return GetWorld()->GetLevelScriptActor(OwnerLevel);
}

void UtilEngineWrap::GetDisplayAdapterScreenResolutions(FScreenResolutionArray& Resolutions)
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

bool UtilEngineWrap::IsTextValid(FText MyText)
{
	bool ret = false;

	if (MyText.IsEmpty())
	{
		ret = true;
	}

	return ret;
}

void UtilEngineWrap::ClientMessage(FString str)
{
	GEngineData->getMainPlayerController()->ClientMessage(str);
}

// FText::Format
void UtilEngineWrap::Format()
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

FString UtilEngineWrap::GetWorldAssetPackageName(ULevelStreaming* StreamedLevel)
{
	return StreamedLevel->GetWorldAssetPackageName();
}

float UtilEngineWrap::GetTimeSeconds()
{
	return GetWorld()->GetTimeSeconds();
}

FTimerManager& UtilEngineWrap::GetWorldTimerManager()
{
	return GetWorld()->GetTimerManager();
}

void UtilEngineWrap::AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector)
{
	AActor::AddReferencedObjects(InThis, Collector);
}

void UtilEngineWrap::AddToRoot(UObject* InThis)
{
	if (nullptr != InThis)
	{
		InThis->AddToRoot();
	}
}

void UtilEngineWrap::RemoveFromRoot(UObject* InThis)
{
	if (nullptr != InThis)
	{
		InThis->RemoveFromRoot();
	}
}

ULevel* UtilEngineWrap::GetLevel(AActor* actor)
{ 
	return Cast<ULevel>(actor->GetOuter());
}

void UtilEngineWrap::ExecuteConsoleCommand(const FString& Command)
{
	APlayerController* TargetPC = UtilEngineWrap::GetPlayerController();

	if (TargetPC)
	{
		TargetPC->ConsoleCommand(Command, true);
	}
}

void UtilEngineWrap::AddToViewport(UUserWidget* userWidget)
{
	if (nullptr != userWidget)
	{
		userWidget->AddToViewport();
	}
}

void UtilEngineWrap::ClipboardCopy(const TCHAR* Str)
{
	// UE 4.19.1 warning C4996: 'FGenericPlatformMisc::ClipboardCopy': FPlatformMisc::ClipboardCopy() has been superseded by FPlatformApplicationMisc::ClipboardCopy() Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//FPlatformMisc::ClipboardCopy(Str);
	FPlatformApplicationMisc::ClipboardCopy(Str);
}

void UtilEngineWrap::ClipboardPaste(class FString& Dest)
{
	// UE 4.19.1 warning C4996: 'FGenericPlatformMisc::ClipboardPaste': FPlatformMisc::ClipboardPaste() has been superseded by FPlatformApplicationMisc::ClipboardPaste() Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//FPlatformMisc::ClipboardPaste(Dest);
	FPlatformApplicationMisc::ClipboardPaste(Dest);
}

TArray< TSharedRef<class SWindow> > UtilEngineWrap::GetInteractiveTopLevelWindows()
{
	return FSlateApplication::Get().GetInteractiveTopLevelWindows();
}

bool UtilEngineWrap::FindPathToWidget(TSharedRef<const SWidget> InWidget, FWidgetPath& OutWidgetPath, EVisibility VisibilityFilter)
{
	return FSlateApplication::Get().FindPathToWidget(InWidget, OutWidgetPath, VisibilityFilter);
}

bool UtilEngineWrap::FindPathToWidget(const TArray<TSharedRef<SWindow>>& WindowsToSearch, TSharedRef<const SWidget> InWidget, FWidgetPath& OutWidgetPath, EVisibility VisibilityFilter)
{
	return FSlateWindowHelper::FindPathToWidget(UtilEngineWrap::GetInteractiveTopLevelWindows(), InWidget, OutWidgetPath, VisibilityFilter);
}

bool UtilEngineWrap::SetKeyboardFocus(const TSharedPtr<SWidget>& OptionalWidgetToFocus, EFocusCause ReasonFocusIsChanging)
{
	return FSlateApplication::Get().SetKeyboardFocus(OptionalWidgetToFocus, ReasonFocusIsChanging);
}

void UtilEngineWrap::SetUserFocusToGameViewport(uint32 UserIndex, EFocusCause ReasonFocusIsChanging)
{
	FSlateApplication::Get().SetUserFocusToGameViewport(UserIndex, ReasonFocusIsChanging);
}

int32 UtilEngineWrap::GetUserIndexForKeyboard()
{
	return FSlateApplication::Get().GetUserIndexForKeyboard();
}

FString UtilEngineWrap::UrlEncode(const FString& UnencodedString)
{
	//return FPlatformHttp::UrlEncode(UnencodedString);
	return "";
}

//bool UtilEngineWrap::OpenLauncher(const FOpenLauncherOptions& Options)
//{
//	FString CrashedAppPathUri;
//	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
//	FOpenLauncherOptions OpenOptions(FString::Printf(TEXT("apps/%s"), *CrashedAppPathUri));
//	OpenOptions.bSilent = true;
//	DesktopPlatform->OpenLauncher(OpenOptions);
//}

FProcHandle UtilEngineWrap::CreateProc(const TCHAR* URL, const TCHAR* Parms, bool bLaunchDetached, bool bLaunchHidden, bool bLaunchReallyHidden, uint32* OutProcessID, int32 PriorityModifier, const TCHAR* OptionalWorkingDirectory, void* PipeWriteChild, void * PipeReadChild)
{
	return FPlatformProcess::CreateProc(URL, Parms, bLaunchDetached, bLaunchHidden, bLaunchReallyHidden, OutProcessID, PriorityModifier, OptionalWorkingDirectory, PipeWriteChild, PipeReadChild);
}

UObject* UtilEngineWrap::StaticLoadObject(UClass* Class, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename, uint32 LoadFlags, UPackageMap* Sandbox, bool bAllowObjectReconciliation)
{
	Class->GetDefaultObject(); // force the CDO to be created if it hasn't already
	UObject* ObjectPtr = ::StaticLoadObject(Class, InOuter, Name, Filename, LoadFlags, Sandbox, bAllowObjectReconciliation);

	if (ObjectPtr)
	{
		ObjectPtr->AddToRoot();
	}

	return ObjectPtr;
}

UClass* UtilEngineWrap::StaticLoadClass(UClass* BaseClass, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename, uint32 LoadFlags, UPackageMap* Sandbox)
{
	UClass* LoadedClass = ::StaticLoadClass(BaseClass, InOuter, Name, Filename, LoadFlags, Sandbox);

	if (LoadedClass)
	{
		LoadedClass->AddToRoot();
	}

	return LoadedClass;
}

FString UtilEngineWrap::GetPathName(const UObject* curObj, const UObject* StopOuter/*=NULL*/)
{
	FString Result;

	if (nullptr != curObj)
	{
		Result = curObj->GetPathName(StopOuter);
	}
	return Result;
}

UMyGameViewportClientBase* const UtilEngineWrap::GetGameViewportClient()
{
	UMyGameInstanceBase* GameInstance = UtilEngineWrap::GetGameInstance();
	UMyGameViewportClientBase* const GameViewport = Cast<UMyGameViewportClientBase>(GameInstance->GetGameViewportClient());

	return GameViewport;
}

FViewport* const UtilEngineWrap::GetViewport()
{
	UMyGameInstanceBase* GameInstance = UtilEngineWrap::GetGameInstance();
	UMyGameViewportClientBase* const GameViewport = Cast<UMyGameViewportClientBase>(GameInstance->GetGameViewportClient());
	if (GameViewport != NULL && GameViewport->Viewport != NULL)
	{
		return GameViewport->Viewport;
	}

	return nullptr;
}

void UtilEngineWrap::EnableScreenSaver(bool bEnable)
{
	GEngine->EnableScreenSaver(bEnable);
}

int32 UtilEngineWrap::LoadPackageAsync(const FString& InName, FLoadPackageAsyncDelegate InCompletionDelegate, TAsyncLoadPriority InPackagePriority, EPackageFlags InPackageFlags)
{
	return ::LoadPackageAsync(InName, InCompletionDelegate, InPackagePriority, InPackageFlags);
}

void UtilEngineWrap::CancelAsyncLoading()
{
	::CancelAsyncLoading();
}

float UtilEngineWrap::GetAsyncLoadPercentage(const FName& PackageName)
{
	return ::GetAsyncLoadPercentage(PackageName);
}

bool UtilEngineWrap::IsGarbageCollecting()
{
	return ::IsGarbageCollecting();
}

void UtilEngineWrap::CollectGarbage(EObjectFlags KeepFlags, bool bPerformFullPurge)
{
	::CollectGarbage(KeepFlags, bPerformFullPurge);
}

bool UtilEngineWrap::TryCollectGarbage(EObjectFlags KeepFlags, bool bPerformFullPurge)
{
	return ::TryCollectGarbage(KeepFlags, bPerformFullPurge);
}

const FWorldContext* UtilEngineWrap::GetWorldContextFromGameViewport(const UGameViewportClient *InViewport)
{
	return GEngine->GetWorldContextFromGameViewport(InViewport);
}

APlayerController* UtilEngineWrap::GetPrimaryPlayerController()
{
	return UtilEngineWrap::GetGameInstance()->GetPrimaryPlayerController();
}

void UtilEngineWrap::SetClientTravel(UWorld *InWorld, const TCHAR* NextURL, ETravelType InTravelType)
{
	GEngine->SetClientTravel(InWorld, NextURL, InTravelType);
}

bool UtilEngineWrap::ServerTravel(const FString& InURL, bool bAbsolute, bool bShouldSkipGameNotify)
{
	return UtilEngineWrap::GetWorld()->ServerTravel(InURL, bAbsolute, bShouldSkipGameNotify);
}

void UtilEngineWrap::OpenLevel(const UObject* WorldContextObject, FName LevelName, bool bAbsolute, FString Options)
{
	UGameplayStatics::OpenLevel(WorldContextObject, LevelName, bAbsolute, Options);
}

void UtilEngineWrap::OpenLevel(const UObject* WorldContextObject, std::string LevelName, bool bAbsolute, FString Options)
{
	FName name = UtilStr::ConvStdStr2FName(LevelName);
	UGameplayStatics::OpenLevel(WorldContextObject, name, bAbsolute, Options);
}

void UtilEngineWrap::LoadStreamLevel(const UObject* WorldContextObject, FName LevelName, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, FLatentActionInfo LatentInfo)
{
	UGameplayStatics::LoadStreamLevel(WorldContextObject, LevelName, bMakeVisibleAfterLoad, bShouldBlockOnLoad, LatentInfo);
}

void UtilEngineWrap::LoadStreamLevel(const UObject* WorldContextObject, std::string LevelName, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, FLatentActionInfo LatentInfo)
{
	FName name = UtilStr::ConvStdStr2FName(LevelName);
	UGameplayStatics::LoadStreamLevel(WorldContextObject, name, bMakeVisibleAfterLoad, bShouldBlockOnLoad, LatentInfo);
}

void UtilEngineWrap::UnloadStreamLevel(const UObject* WorldContextObject, FName LevelName, FLatentActionInfo LatentInfo)
{
	UGameplayStatics::UnloadStreamLevel(WorldContextObject, LevelName, LatentInfo);
}

UMyLocalPlayerBase* UtilEngineWrap::GetLocalPlayerFromControllerId(const UGameViewportClient* InViewport, const int32 ControllerId)
{
	return Cast<UMyLocalPlayerBase>(GEngine->GetLocalPlayerFromControllerId(InViewport, ControllerId));
}

int UtilEngineWrap::GetNumLocalPlayers()
{
	return UtilEngineWrap::GetGameInstance()->GetNumLocalPlayers();
}

void UtilEngineWrap::SetGameDefaultMap(const std::string& NewMap)
{
	FString param = UtilStr::ConvStdStr2FString(const_cast<std::string&>(NewMap));
	UGameMapsSettings::SetGameDefaultMap(param);
}

double UtilEngineWrap::Seconds()
{
	double StartTime = FPlatformTime::Seconds();
	return StartTime;
}

FWorldContext* UtilEngineWrap::GetWorldContextFromPIEInstance(const int32 PIEInstance)
{
	FWorldContext* worldContext = GEngine->GetWorldContextFromPIEInstance(PIEInstance);
	return worldContext;
}

UWorld* UtilEngineWrap::GetGlobalWorld()
{
	return GWorld;
}

void UtilEngineWrap::SetTransientMasterVolume(float size)
{
	UWorld* GameInstanceWorld = UtilEngineWrap::GetGlobalWorld();

	if (FAudioDevice* GameInstanceAudioDevice = GameInstanceWorld->GetAudioDevice())
	{
		GameInstanceAudioDevice->SetTransientMasterVolume(0.0f);
	}
}

FVector2D UtilEngineWrap::getScreenSize()
{
	FVector2D screenSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	return screenSize;
}

FVector2D UtilEngineWrap::getSystemResolution()
{
	FVector2D Result = FVector2D(GSystemResolution.ResX, GSystemResolution.ResY);
	return Result;
}

void UtilEngineWrap::SetMaterial(UMeshComponent* meshComponent, int32 ElementIndex, UMaterialInterface* Material)
{
	meshComponent->SetMaterial(ElementIndex, Material);
}

// Engine\Source\Runtime\Engine\Private\Components\PrimitiveComponent.cpp
UMaterialInstanceDynamic* UtilEngineWrap::SetMaterial(UPrimitiveComponent* primitiveComponent, int32 ElementIndex, UMaterialInterface* Material)	   // ; error C2761: 'SetMaterial': member function redeclaration not allowed ，因为最后多加了个分号
{
	UMaterialInstanceDynamic* ret = nullptr;

	if (nullptr != primitiveComponent)
	{
		ret = primitiveComponent->CreateAndSetMaterialInstanceDynamicFromMaterial(ElementIndex, Material);
	}

	return ret;
}

void UtilEngineWrap::TestFileWriteCompressed(FString _path)
{
	//FPlatformFileManager::Get().SetPlatformFile(*CurrentPlatformFile);
	//Step 1: Variable Data -> Binary
	uint8 b = 1;
	int32 num = 123;
	float height = 456.789;
	FString dataStr = FString::Printf(TEXT("--- dataStr"));
	FVector tmp(11.11, 22.22, 33.33);
	TArray<FRotator> SaveDataRotatorArray;
	for (int32 i = 0; i < 10; i++)
		SaveDataRotatorArray.Push(FRotator(i * 10, i * 10, i * 10));

	FBufferArchive ToBinary;
	ToBinary << b;
	ToBinary << num;
	ToBinary << height;
	ToBinary << dataStr;
	ToBinary << tmp; //save player location to hard disk
	ToBinary << SaveDataRotatorArray;

	//Save data 
	//FString SavePath = "C:\\mysavefileCp.save";

	//No Data
	if (ToBinary.Num() <= 0) return;

	// Compress File 
	//tmp compressed data array
	TArray<uint8> CompressedData;
	FArchiveSaveCompressedProxy Compressor =
		FArchiveSaveCompressedProxy(CompressedData, ECompressionFlags::COMPRESS_ZLIB);

	//Send entire binary array/archive to compressor
	Compressor << ToBinary;

	//send archive serialized data to binary array
	Compressor.Flush();

	//test size
	FString str = FString::Printf(TEXT("--- befor Compresse:%d, after Compresse:%d"), ToBinary.Num(), CompressedData.Num());
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);

	////Step 2: Binary to Hard Disk - compress
	//vibes to file, return successful or not
	if (FFileHelper::SaveArrayToFile(CompressedData, *_path))
	{
		// Free Binary Arrays 
		Compressor.FlushCache();
		CompressedData.Empty();

		ToBinary.FlushCache();
		ToBinary.Empty();

		// Close Buffer 
		ToBinary.Close();
		return;
	}
	else
	{
		// Free Binary Arrays 
		Compressor.FlushCache();
		CompressedData.Empty();

		ToBinary.FlushCache();
		ToBinary.Empty();

		// Close Buffer 
		ToBinary.Close();
		return;
	}
}

void UtilEngineWrap::TestFileReadCompressed(FString _path)
{
	//Load the Compressed data array
	TArray<uint8> CompressedData;
	if (!FFileHelper::LoadFileToArray(CompressedData, *_path))
	{
		FString str = FString::Printf(TEXT("--- FFILEHELPER:>> Invalid File"));
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
		return;
	}

	// Decompress File 
	FArchiveLoadCompressedProxy Decompressor =
		FArchiveLoadCompressedProxy(CompressedData, ECompressionFlags::COMPRESS_ZLIB);

	//Decompression Error?
	if (Decompressor.GetError())
	{
		FString str = FString::Printf(TEXT("--- FArchiveLoadCompressedProxy>> ERROR : File Was Not Compressed"));
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
		return;
	}

	//Decompress
	FBufferArchive DecompressedBinaryArray;
	Decompressor << DecompressedBinaryArray;

	uint8 b = 0;
	int32 num = 0;
	float height = 0.f;
	FString dataStr(TEXT(""));
	FVector location;
	TArray<FRotator> rotatorArr;

	//Read the Data Retrieved by GFileManager
	FMemoryReader FromBinary = FMemoryReader(DecompressedBinaryArray, true); //true, free data after done
	FromBinary.Seek(0);
	FromBinary << b;
	FromBinary << num;
	FromBinary << height;
	FromBinary << dataStr;
	FromBinary << location;
	FromBinary << rotatorArr;

	CompressedData.Empty();
	Decompressor.FlushCache();
	FromBinary.FlushCache();

	// Empty & Close Buffer 
	DecompressedBinaryArray.Empty();
	DecompressedBinaryArray.Close();


	//print
	FString str2 = FString::Printf(TEXT("--- b:%d, num:%d, height:%f, dataStr:%s\n"), b, num, height, *dataStr);
	FString str3 = FString::Printf(TEXT("--- location x:%f, y:%f, z:%f\n"), location.X, location.Y, location.Z);

	FString str4("");
	for (auto rot : rotatorArr)
	{
		FString tmp = FString::Printf(TEXT("--- rotator Pitch:%f, Yaw:%f, Roll:%f\n"), rot.Pitch, rot.Yaw, rot.Roll);
		str4.Append(tmp);
	}
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, str2 + str3 + str4);
}

void UtilEngineWrap::TestFileWriteUnCompressed(FString _path)
{
	//FPlatformFileManager::Get().SetPlatformFile(*CurrentPlatformFile);
	//Step 1: Variable Data -> Binary
	FBufferArchive ToBinary;
	uint8 b = 1;
	int32 num = 123;
	float height = 456.789;
	FString dataStr = FString::Printf(TEXT("--- dataStr"));
	FVector tmp(11.11, 22.22, 33.33);
	TArray<FRotator> SaveDataRotatorArray;
	for (int32 i = 0; i < 10; i++)
		SaveDataRotatorArray.Push(FRotator(i * 10, i * 10, i * 10));

	ToBinary << b;
	ToBinary << num;
	ToBinary << height;
	ToBinary << dataStr;
	ToBinary << tmp; //save player location to hard disk
	ToBinary << SaveDataRotatorArray;

	//Save data 
	//FString SavePath = "C:\\mysavefileUnCp.save";

	//No Data
	if (ToBinary.Num() <= 0) return;

	//Step 2: Binary to Hard Disk
	if (FFileHelper::SaveArrayToFile(ToBinary, *_path))
	{
		// Free Binary Array    
		ToBinary.FlushCache();
		ToBinary.Empty();

		FString str = FString::Printf(TEXT("--- SaveFile Success"));
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
		return;
	}

	// Free Binary Array    
	ToBinary.FlushCache();
	ToBinary.Empty();
}

void UtilEngineWrap::TestFileReadUnCompressed(FString _path)
{
	//Load the data array,
	//  you do not need to pre-initialize this array,
	//      UE4 C++ is awesome and fills it 
	//      with whatever contents of file are, 
	//      and however many bytes that is
	TArray<uint8> TheBinaryArray;
	if (!FFileHelper::LoadFileToArray(TheBinaryArray, *_path))
	{
		FString str = FString::Printf(TEXT("--- LoadFileToArray Fail"));
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
		return;
	}

	//Testing
	FString str = FString::Printf(TEXT("--- Loaded File Size:%d"), TheBinaryArray.Num());
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);

	//File Load Error
	if (TheBinaryArray.Num() <= 0) return;

	uint8 b = 0;
	int32 num = 0;
	float height = 0.f;
	FString dataStr(TEXT(""));
	FVector location;
	TArray<FRotator> rotatorArr;

	//Read the Data Retrieved by GFileManager
	FMemoryReader FromBinary = FMemoryReader(TheBinaryArray, true); //true, free data after done
	FromBinary.Seek(0);

	FromBinary << b;
	FromBinary << num;
	FromBinary << height;
	FromBinary << dataStr;
	FromBinary << location;
	FromBinary << rotatorArr;

	//Clean up 
	FromBinary.FlushCache();
	FromBinary.Close();

	// Empty & Close Buffer 
	TheBinaryArray.Empty();

	//print
	FString str2 = FString::Printf(TEXT("--- b:%d, num:%d, height:%f, dataStr:%s\n"), b, num, height, *dataStr);
	FString str3 = FString::Printf(TEXT("--- location x:%f, y:%f, z:%f\n"), location.X, location.Y, location.Z);

	FString str4("");
	for (auto rot : rotatorArr)
	{
		FString tmp = FString::Printf(TEXT("--- rotator Pitch:%f, Yaw:%f, Roll:%f\n"), rot.Pitch, rot.Yaw, rot.Roll);
		str4.Append(tmp);
	}

	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, str2 + str3 + str4);
}

bool UtilEngineWrap::IsPendingKill(AActor* actor)
{
	bool ret = false;

	if (nullptr != actor)
	{
		ret = actor->IsPendingKill();
	}

	return ret;
}

void UtilEngineWrap::Destroy(AActor* actor)
{
	if (nullptr != actor)
	{
		actor->Destroy();
	}
}

uint32 UtilEngineWrap::getFrameNumber()
{
	return GFrameNumber;
}

uint32 UtilEngineWrap::getFrameNumberRenderThread()
{
	return GFrameNumberRenderThread;
}

bool UtilEngineWrap::isMultithreaded()
{
	const bool bIsMultithreaded = FPlatformProcess::SupportsMultithreading();
	return bIsMultithreaded;
}

bool UtilEngineWrap::isInAsyncLoadingThread()
{
	bool ret = IsInAsyncLoadingThread();
	return ret;
}

bool UtilEngineWrap::requiresCookedData()
{
	bool ret = FPlatformProperties::RequiresCookedData();
	return ret;
}

bool UtilEngineWrap::isWidgetVisible(UWidget* widget)
{
	bool ret = false;

	if (nullptr != widget)
	{
		//ret = widget->IsVisible();
		ret = (ESlateVisibility::Visible == widget->GetVisibility());
	}

	return ret;
}

void UtilEngineWrap::setWidgetVisible(UWidget* widget, bool isVisible)
{
	if (nullptr != widget)
	{
		widget->SetVisibility(ESlateVisibility::Visible);
	}
}

FColor UtilEngineWrap::convLineColorToColor(FLinearColor lineColor)
{
	return lineColor.ToRGBE();
}

FLinearColor UtilEngineWrap::convColorToLineColor(FColor color)
{
	return FLinearColor::FromSRGBColor(color);
}

void UtilEngineWrap::setActorPos(AActor* actor, FVector NewLocation)
{
	actor->SetActorLocation(NewLocation);
}

void UtilEngineWrap::setActorRotate(AActor* actor, FRotator NewRotation)
{
	actor->SetActorRotation(NewRotation);
}

void UtilEngineWrap::setActorScale(AActor* actor, FVector NewScale3D)
{
	actor->SetActorScale3D(NewScale3D);
}

FVector UtilEngineWrap::getActorPos(AActor* actor)
{
	return actor->GetActorLocation();
}

FRotator UtilEngineWrap::getActorRotate(AActor* actor)
{
	return actor->GetActorRotation();
}

FVector UtilEngineWrap::getActorScale(AActor* actor)
{
	return actor->GetActorScale();
}

void AddActorLocalOffset(AActor* actor, FVector DeltaLocation, bool bSweep, FHitResult* OutSweepHitResult, ETeleportType Teleport)
{
	actor->AddActorLocalOffset(DeltaLocation, bSweep, OutSweepHitResult, Teleport);
}

void AddActorLocalRotation(AActor* actor, const FQuat& DeltaRotation, bool bSweep, FHitResult* OutSweepHitResult, ETeleportType Teleport)
{
	actor->AddActorLocalRotation(DeltaRotation, bSweep, OutSweepHitResult, Teleport);
}

FTransform UtilEngineWrap::getActorTransform(AActor* actor)
{
	return actor->GetActorTransform();
}

USceneComponent* UtilEngineWrap::getActorRootComponent(AActor* actor)
{
	return actor->GetRootComponent();
}

FVector UtilEngineWrap::getActorPivotOffset(AActor* actor)
{
	return actor->GetPivotOffset();
}

void UtilEngineWrap::setActorVisible(AActor* actor, bool isVisible)
{
	actor->SetActorHiddenInGame(isVisible);
}

void UtilEngineWrap::setActorEnableCollision(AActor* actor, bool isEnable)
{
	actor->SetActorEnableCollision(isEnable);
}

void UtilEngineWrap::AttachToComponent(AActor* actor, USceneComponent* Parent, const FAttachmentTransformRules& AttachmentRules, FName SocketName)
{
	actor->AttachToComponent(Parent, AttachmentRules, SocketName);
}

void UtilEngineWrap::AttachToActor(AActor* actor, AActor* ParentActor, const FAttachmentTransformRules& AttachmentRules, FName SocketName)
{
	actor->AttachToActor(ParentActor, AttachmentRules, SocketName);
}

void UtilEngineWrap::setActorComponentActive(UActorComponent* actorComponent, bool isActive)
{
	actorComponent->bIsActive = isActive;
}

AActor* UtilEngineWrap::getActorComponentOwner(UActorComponent* actorComponent)
{
	return actorComponent->GetOwner();
}

UWorld* UtilEngineWrap::getWorldByActorComponent(UActorComponent* actorComponent)
{
	return actorComponent->GetWorld();
}

const TSet<UActorComponent*>& UtilEngineWrap::getAllComponent(AActor* actor)
{
	return actor->GetComponents();
}

const void UtilEngineWrap::destroyComponent(UActorComponent* actorComponent)
{
	if (nullptr != actorComponent)
	{
		actorComponent->DestroyComponent();
	}
}

void UtilEngineWrap::setScalarParameterValue(UMaterialInstanceDynamic* materialInstanceDynamic, FName ParameterName, float Value)
{
	if (nullptr != materialInstanceDynamic)
	{
		materialInstanceDynamic->SetScalarParameterValue(ParameterName, Value);
	}
}

void UtilEngineWrap::setTextureParameterValue(UMaterialInstanceDynamic* materialInstanceDynamic, FName ParameterName, UTexture* Value)
{
	if (nullptr != materialInstanceDynamic)
	{
		materialInstanceDynamic->SetTextureParameterValue(ParameterName, Value);
	}
}

void UtilEngineWrap::conditionalCollectGarbage()
{
	GEngine->ConditionalCollectGarbage();
}

void UtilEngineWrap::collectGarbage(EObjectFlags KeepFlags, bool bPerformFullPurge)
{
	::CollectGarbage(KeepFlags, bPerformFullPurge);
}

AActor* UtilEngineWrap::createActor(std::string name)
{
	AActor* ret = NULL;

	ret = UtilEngineWrap::NewObject<AActor>();

	return ret;
}

void UtilEngineWrap::SetParent(AActor* child, AActor* parent, bool worldPositionStays)
{
	
}

void UtilEngineWrap::SetActive(AActor* target, bool bshow)
{
	UtilEngineWrap::setActorVisible(target, bshow);
}

bool UtilEngineWrap::IsActive(AActor* target)
{
	return false;
}

FTransform UtilEngineWrap::GetTransform(AActor* target)
{
	return target->GetTransform();
}

FVector UtilEngineWrap::getPos(AActor* actor)
{
	FVector ret;

	if (actor)
	{
		ret = actor->GetTransform().GetLocation();
	}

	return ret;
}

void UtilEngineWrap::setPos(FTransform& tran, FVector& pos)
{
	// 如果使用物理，使用 Transform 移动的时候，不会遵守物理运算，如果设置了 UnityEngine.Rigidbody.constraints ，对应的移动也会移动
	if (tran.IsValid())
	{
		tran.SetLocation(pos);
	}
}

void UtilEngineWrap::setPosByActor(AActor* actor, FVector& pos)
{
	// 如果使用物理，使用 Transform 移动的时候，不会遵守物理运算，如果设置了 UnityEngine.Rigidbody.constraints ，对应的移动也会移动
	if (actor)
	{
		// 需要构造 Transform ，然后调用 AddActorWorldTransform ，因为 Transform 是一个结构体，不是引用
		//actor->GetTransform().SetLocation(pos);
		actor->AddActorWorldOffset(pos);
	}
}

FVector UtilEngineWrap::getScale(AActor* actor)
{
	FVector ret;

	if (actor)
	{
		ret = actor->GetTransform().GetScale3D();
	}

	return ret;
}

void UtilEngineWrap::setScale(FTransform& tran, FVector& scale)
{
	if (tran.IsValid())
	{
		// 需要构造 Transform ，然后调用 AddActorWorldTransform ，因为 Transform 是一个结构体，不是引用
		tran.SetScale3D(scale);
	}
}

void UtilEngineWrap::setScaleByActor(AActor* actor, FVector& scale)
{
	if (actor)
	{
		// 需要构造 Transform ，然后调用 AddActorWorldTransform ，因为 Transform 是一个结构体，不是引用
		//actor->GetTransform().SetScale3D(scale);
		//actor->SetActorRelativeScale3D(scale);
		actor->SetActorScale3D(scale);
	}
}

FQuat UtilEngineWrap::getRotate(AActor* actor)
{
	FQuat ret;

	if (actor)
	{
		ret = actor->GetTransform().GetRotation();
	}

	return ret;
}

void UtilEngineWrap::setRotate(FTransform& tran, FQuat& rotate)
{
	if (tran.IsValid())
	{
		tran.SetRotation(rotate);
	}
}

void UtilEngineWrap::setRotateByActor(AActor* actor, FQuat& rotate)
{
	if (actor)
	{
		// 需要构造 Transform ，然后调用 AddActorWorldTransform ，因为 Transform 是一个结构体，不是引用
		// actor->GetTransform().SetRotation(rotate);
		actor->AddActorWorldRotation(rotate);
	}
}

EWorldType::Type UtilEngineWrap::getWorldType()
{
	EWorldType::Type ret = EWorldType::Game;
	UWorld* world = UtilEngineWrap::GetWorld();

	if (nullptr != world)
	{
		ret = world->WorldType;
	}

	return ret;
}

bool UtilEngineWrap::isGameWorld()
{
	bool ret = false;

	if (EWorldType::Game == UtilEngineWrap::getWorldType())
	{
		ret = true;
	}

	return ret;
}

bool UtilEngineWrap::isEditorWorld()
{
	bool ret = false;

	if (EWorldType::Editor == UtilEngineWrap::getWorldType())
	{
		ret = true;
	}

	return ret;
}

std::string UtilEngineWrap::getManifestName()
{
	return "";
}

TScriptDelegate<FWeakObjectPtr> UtilEngineWrap::addUObjectButtonClickHandle(UUserWidget* widget, const FName& buttonName, UObject* pThis, const FName& functionName)
{
	TScriptDelegate<FWeakObjectPtr> handle;

	if (nullptr != widget && nullptr != pThis)
	{
		//UButton* button = widget->GetSlateWidgetFromName(buttonName);
		UButton* button = Cast<UButton>(widget->GetWidgetFromName(buttonName));
		if (nullptr != button)
		{
			handle.BindUFunction(pThis, functionName);
			button->OnClicked.Add(handle);
		}
	}

	return handle;
}

void UtilEngineWrap::Destroy(AActor* actor, bool bNetForce, bool bShouldModifyLevel)
{
	if (nullptr != actor)
	{
		actor->Destroy(bNetForce, bShouldModifyLevel);
	}
}

void UtilEngineWrap::DestroyImmediate(AActor* actor, bool bNetForce, bool bShouldModifyLevel)
{
	if (nullptr != actor)
	{
		actor->Destroy(bNetForce, bShouldModifyLevel);
	}
}