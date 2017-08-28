#include "MyProject.h"
#include "EngineApi.h"
#include "Common.h"
#include "EngineData.h"
#include "MyGameEngineBase.h"
#include "Internationalization/Text.h"	// FFormatOrderedArguments
#include "MyGameInstanceBase.h"
#include "Blueprint/UserWidget.h"	// UUserWidget
#include "GenericPlatform/GenericPlatformMisc.h"	//	ClipboardCopy
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

DEFINE_LOG_CATEGORY(MyLog);

UMyGameInstanceBase* EngineApi::GetGameInstance()
{
	return Cast<UMyGameInstanceBase>(UGameplayStatics::GetGameInstance(GEngineData->getMainActor()));
}

UWorld* EngineApi::GetWorld()
{
	// UE4 4.17
	// warning C4996: 'UEngine::GetWorldFromContextObject': GetWorldFromContextObject(Object) and GetWorldFromContextObject(Object, boolean) are replaced by GetWorldFromContextObject(Object, Enum) or GetWorldFromContextObjectChecked(Object) Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//UWorld* World = GEngine->GetWorldFromContextObject(GEngineData->getMainActor());
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

UMyGameEngineBase* EngineApi::getEngine()
{
	return Cast<UMyGameEngineBase>(GEngine);
}

UMyGameInstanceBase* EngineApi::getMyGameInstanceByEngine()
{
	UMyGameEngineBase* pUMyEngine = Cast<UMyGameEngineBase>(GEngine);
	UMyGameInstanceBase* const GI = Cast<UMyGameInstanceBase>(pUMyEngine->GameInstance);
	return GI;
}

UWorld* EngineApi::getWorldByEngine()
{
	UMyGameInstanceBase* pUMyProjectGameInstance = getMyGameInstanceByEngine();
	UWorld* const World = pUMyProjectGameInstance->GetWorld();
	return World;
}

UMyGameInstanceBase* EngineApi::getMyGameInstanceByController()
{
	return Cast<UMyGameInstanceBase>(GEngineData->getMainPlayerController()->GetGameInstance());
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

AMyPlayerControllerBase* EngineApi::GetPlayerController()
{
	AMyPlayerControllerBase* TargetPC = Cast<AMyPlayerControllerBase>(UGameplayStatics::GetPlayerController(GEngineData->getMainActor(), 0));
	return TargetPC;
}

FWorldContext* EngineApi::GetWorldContextByGameInstance()
{
	UMyGameInstanceBase* GameInstance = EngineApi::GetGameInstance();
	FWorldContext* const PieWorldContext = GameInstance->GetWorldContext();
	return PieWorldContext;
}

UWorld* EngineApi::GetWorldByWorldContext()
{
	FWorldContext* PieWorldContext = EngineApi::GetWorldContextByGameInstance();
	UWorld* PlayWorld = PieWorldContext->World();
	return PlayWorld;
}

UMyGameInstanceBase* EngineApi::GetGameInstanceByWorld()
{
	UWorld* NewWorld = EngineApi::GetWorld();
	UMyGameInstanceBase* GameInstance = Cast<UMyGameInstanceBase>(NewWorld->GetGameInstance());
	return GameInstance;
}

UMyLocalPlayerBase* EngineApi::GetLocalPlayerByPlayerController()
{
	AMyPlayerControllerBase* Controller = EngineApi::GetPlayerController();
	UMyLocalPlayerBase* Player = Cast<UMyLocalPlayerBase>(Controller->Player);
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
	// UE4 4.17
	// warning C4996: 'USceneComponent::ComponentToWorld': ComponentToWorld will be made private, use GetComponentTransform() instead. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	return pUSceneComponent->ComponentToWorld;
	//return pUSceneComponent->GetComponentTransform();
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

UMyGameViewportClientBase* const EngineApi::GetGameViewportClient()
{
	UMyGameInstanceBase* GameInstance = EngineApi::GetGameInstance();
	UMyGameViewportClientBase* const GameViewport = Cast<UMyGameViewportClientBase>(GameInstance->GetGameViewportClient());
	return GameViewport;
}

FViewport* const EngineApi::GetViewport()
{
	UMyGameInstanceBase* GameInstance = EngineApi::GetGameInstance();
	UMyGameViewportClientBase* const GameViewport = Cast<UMyGameViewportClientBase>(GameInstance->GetGameViewportClient());
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

void EngineApi::LoadStreamLevel(const UObject* WorldContextObject, std::string LevelName, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, FLatentActionInfo LatentInfo)
{
	FName name = UtilStr::ConvStdStr2FName(LevelName);
	return UGameplayStatics::LoadStreamLevel(WorldContextObject, name, bMakeVisibleAfterLoad, bShouldBlockOnLoad, LatentInfo);
}

APlayerController* EngineApi::GetPrimaryPlayerController()
{
	return EngineApi::GetGameInstance()->GetPrimaryPlayerController();
}

void EngineApi::SetClientTravel(UWorld *InWorld, const TCHAR* NextURL, ETravelType InTravelType)
{
	GEngine->SetClientTravel(InWorld, NextURL, InTravelType);
}

bool EngineApi::ServerTravel(const FString& InURL, bool bAbsolute, bool bShouldSkipGameNotify)
{
	return EngineApi::GetWorld()->ServerTravel(InURL, bAbsolute, bShouldSkipGameNotify);
}

UMyLocalPlayerBase* EngineApi::GetLocalPlayerFromControllerId(const UGameViewportClient* InViewport, const int32 ControllerId)
{
	return Cast<UMyLocalPlayerBase>(GEngine->GetLocalPlayerFromControllerId(InViewport, ControllerId));
}

int EngineApi::GetNumLocalPlayers()
{
	return EngineApi::GetGameInstance()->GetNumLocalPlayers();
}

void EngineApi::SetGameDefaultMap(const std::string& NewMap)
{
	FString param = UtilStr::ConvStdStr2FString(const_cast<std::string&>(NewMap));
	UGameMapsSettings::SetGameDefaultMap(param);
}

double EngineApi::Seconds()
{
	double StartTime = FPlatformTime::Seconds();
	return StartTime;
}

FWorldContext* EngineApi::GetWorldContextFromPIEInstance(const int32 PIEInstance)
{
	FWorldContext* worldContext = GEngine->GetWorldContextFromPIEInstance(PIEInstance);
	return worldContext;
}

UWorld* EngineApi::GetGlobalWorld()
{
	return GWorld;
}

void EngineApi::SetTransientMasterVolume(float size)
{
	UWorld* GameInstanceWorld = EngineApi::GetGlobalWorld();
	if (FAudioDevice* GameInstanceAudioDevice = GameInstanceWorld->GetAudioDevice())
	{
		GameInstanceAudioDevice->SetTransientMasterVolume(0.0f);
	}
}

FVector2D EngineApi::getScreenSize()
{
	FVector2D screenSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	return screenSize;
}

FVector2D EngineApi::getSystemResolution()
{
	FVector2D Result = FVector2D(GSystemResolution.ResX, GSystemResolution.ResY);
	return Result;
}

void EngineApi::SetMaterial(UMeshComponent* meshComponent, int32 ElementIndex, UMaterialInterface* Material)
{
	meshComponent->SetMaterial(ElementIndex, Material);
}

void EngineApi::TestFileWriteCompressed(FString _path)
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

void EngineApi::TestFileReadCompressed(FString _path)
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

void EngineApi::TestFileWriteUnCompressed(FString _path)
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

void EngineApi::TestFileReadUnCompressed(FString _path)
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

bool EngineApi::IsPendingKill(AActor* actor)
{
	return actor->IsPendingKill();
}

void EngineApi::Destroy(AActor* actor)
{
	actor->Destroy();
}

uint32 EngineApi::getFrameNumber()
{
	return GFrameNumber;
}

uint32 EngineApi::getFrameNumberRenderThread()
{
	return GFrameNumberRenderThread;
}