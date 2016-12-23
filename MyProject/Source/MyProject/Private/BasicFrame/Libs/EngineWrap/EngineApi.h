#ifndef __EngineApi_H
#define __EngineApi_H

// #include "Platform.h"
#include "Core.h"		// "Platform.h" �Ѿ������� "Core.h" ����
//#include "ICUUtilities.h"

#include "UObject/Object.h" // UObject : public UObjectBaseUtility
#include "Math/Vector.h"	// FVector
#include "GameFramework/Actor.h"	// AActor
#include "Components/StaticMeshComponent.h"		// UStaticMeshComponent
#include "GenericPlatform/GenericPlatformMath.h"	// Max

#include "Containers/Array.h"	// TArray
//#include "IDesktopPlatform.h"	// FOpenLauncherOptions
#include "UObject/ConstructorHelpers.h"		// ConstructorHelpers
#include "Templates/SubclassOf.h"	// TSubclassOf
#include "UObject/UObjectGlobals.h"	// DuplicateObject

class UGameInstance;
class UMyEngine;
class UMyGameInstance;
class UUserWidget;
class SWindow;
struct FWorldContext;
class UWorld;
class AMyPlayerController;
class UMyLocalPlayer;


DECLARE_LOG_CATEGORY_EXTERN(MyLog, Log, All);


// https://wiki.unrealengine.com/Time_Macros
#define TIMENOW            (GetWorld() ? GetWorld()->GetTimeSeconds() : 0.0f)
#define TIMESINCE(Time)    (GetWorld()->GetTimeSeconds() - Time)


// https://wiki.unrealengine.com/Timer_Macros
#define SETTIMER(param1, param2, param3) \
{ \
    FTimerHandle TimerHandle; \
    GetWorldTimerManager().SetTimer(TimerHandle, this, &param1, param2, param3); \
}

#define SETTIMERH(handle, param1, param2, param3) (GetWorldTimerManager().SetTimer(handle, this, &param1, param2, param3))
#define CLEARTIMER(handle) (GetWorldTimerManager().ClearTimer(handle))
#define ISTIMERACTIVE(handle) (GetWorldTimerManager().IsTimerActive(handle))

#define GETTIMERREMAINING(handle) (GetWorldTimerManager().GetTimerRemaining(handle))
#define GETTIMERELAPSED(handle) (GetWorldTimerManager().GetTimerElapsed(handle))


class EngineApi
{
public:
	static UMyGameInstance* getGameInstance();
	static UWorld* GetWorld();
	static void showCursor();
	static UMyEngine* getEngine();
	static UMyGameInstance* getMyGameInstanceByEngine();
	static UMyGameInstance* getMyGameInstanceByController();
	static UWorld* getWorldByEngine();

	static ACharacter* getFirstCharacter();	// ��ȡ��һ�� ACharacter �����������Լ�
	static AMyPlayerController* GetPlayerController();
	static FWorldContext* GetWorldContextByGameInstance();
	static UWorld* GetWorldByWorldContext();
	static UMyGameInstance* GetGameInstanceByWorld();
	static UMyLocalPlayer* GetLocalPlayerByPlayerController();

	static ULevel* getCurrentLevelFromWorld();
	static ULevel* getPersistentLevelFromWorld();
	static UGameInstance* getGameInstanceFromWorld();
	static TArray<AActor*>& getActorArrayFromCurrentLevel();

	static void addEventHandle(UButton* pBtn, UObject* pFuncObj, FName funcName);
	static float getUTCSec();
	static float GetRealTimeSeconds();

	/**
	 *@brief ������ڵ�
	 */
	static void InsertMountPoint(const FString& RootPath, const FString& ContentPath);

	/**
	 *@brief �ļ��Ƿ����
	 *@param InPath �����������Ŀ¼
	 */
	static bool FileExists(const FString& InPath);

	/**
	 *@brief ����Ӧ���ļ��Ƿ����
	 *@param InPackageFilename ��������İ���Ŀ¼������ "/Game/UMG/UITestCanvas_Canvas"
	 */
	static bool PackageExists(const FString& InPackageFilename);

	/**
	 *@brief ��ȡ��Ϸ�û�Ŀ¼������ Unity �� Application.persistentDataPath ��дĿ¼
	 */
	static FString GameUserDir();
	static void SetActive(UWidget* target, bool bshow);
	static void Destroy(UWidget* obj);
	static void UnloadUnusedAssets();

	static void SetParent(UWidget*child, UPanelWidget* parent, bool worldPositionStays = true);

	/**
	 * @brief ���һ�� Child 
	 */
	void SetContentForSlot(UUserWidget* userWidget, FName SlotName, UWidget* Content);

	//static void ConvertString(const FString& Source, icu::UnicodeString& Destination, const bool ShouldNullTerminate);

	/**
	 * @brief ���ߵ�ѡ
	 */
	static bool LineTraceSingleByChannel(UWorld* World, struct FHitResult& OutHit, const FVector& Start, const FVector& End, ECollisionChannel TraceChannel, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam);

	/**
	 * @brief �����ѡ
	 */
	static bool SweepTestByChannel(UWorld* World, const FVector& Start, const FVector& End, const FQuat& Rot, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam);

	/**
	 * @brief �ص����Ե�ѡ
	 */
	static bool OverlapBlockingTestByChannel(UWorld* World, const FVector& Pos, const FQuat& Rot, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam);

	/**
	 * @brief �� UInputComponent ��ȡ Axis ����ֵ
	 */
	float GetAxisValue(UInputComponent* pUInputComponent, const FName AxisName);

	/**
	 * @brief �� AActor ��ȡ Axis ����ֵ
	 */
	float GetInputAxisValue(AActor* pAActor, const FName InputAxisName);

	/**
	 * @brief �� MainActor ��ȡ Axis ����ֵ
	 */
	float GetInputAxisValue(const FName InputAxisName);

	/**
	 * @brief ��ȡ��������ľ���λ����Ϣ
	 */
	static FTransform& getTransform(USceneComponent* pUSceneComponent);

	/**
	 * @brief ����������������ַ
	 * @brief https://wiki.unrealengine.com/How_to_Launch_Web_Browser_with_URL_From_In-Game
	 */
	static void LaunchURL(FString url);

	// https://wiki.unrealengine.com/Mesh_Collision,_Obtain_Closest_Point_on_Mesh_Surface_To_Other_Point
	static bool isValid(UObject* pObj);

	// https://wiki.unrealengine.com/Mesh_Collision,_Obtain_Closest_Point_on_Mesh_Surface_To_Other_Point
	float DistanceOfActorToThisMeshSurface(UStaticMeshComponent* StaticMeshComponent, AActor* TestActor, FVector& ClosestSurfacePoint) const;

	// https://wiki.unrealengine.com/Mass_Scale_of_Physics_Mesh,_Dynamically_Update_During_Runtime
	void SetMassScale(UStaticMeshComponent* StaticMeshComponent, const float& NewScale);

	// https://wiki.unrealengine.com/Min/Max_of_An_Array_of_Any_DataType,_Including_Ones_That_You_Create
	template< class T >
	static FORCEINLINE T Max(const TArray<T>& Values, int32* MaxIndex = NULL)
	{
		const T MaxValue = FMath::Max<T>(Values, &MaxIndex);
		return MaxValue;
	}

	// https://wiki.unrealengine.com/Solus_C%2B%2B_Tutorials
	// ʹ�� Cast<AYourLevelScriptActor>GetLevelScriptActor();
	ALevelScriptActor* GetLevelScriptActor(ULevel* OwnerLevel = NULL) const;

	// https://wiki.unrealengine.com/Solus_C%2B%2B_Tutorials
	static FORCEINLINE void GetDisplayAdapterScreenResolutions(FScreenResolutionArray& Resolutions);

	// https://wiki.unrealengine.com/Solus_C%2B%2B_Tutorials
	static bool IsTextValid(FText MyText);

	// https://wiki.unrealengine.com/Game_Instance,_Custom_Game_Instance_For_Inter-Level_Persistent_Data_Storage#Overview
	static void ClientMessage(FString str);

	// https://wiki.unrealengine.com/Solus_C%2B%2B_Tutorials
	static void Format();

	// https://wiki.unrealengine.com/Streamed_Levels,_Test_If_Actor_Is_In_Level_Bounds
	static FString GetWorldAssetPackageName(ULevelStreaming* StreamedLevel);

	// https://wiki.unrealengine.com/Time_Macros
	static float GetTimeSeconds();

	// Engine\Source\Runtime\Engine\Private\Actor.cpp
	//  error C2272: 'GetWorldTimerManager': modifiers not allowed on static member functions
	//static FTimerManager& GetWorldTimerManager() const;
	static FTimerManager& GetWorldTimerManager();

	static void AddReferencedObjects(UObject* InThis, FReferenceCollector& Collector);

	// error C2272: 'GetLevel': modifiers not allowed on static member functions
	//static ULevel* GetLevel(AActor* actor) const;
	static ULevel* GetLevel(AActor* actor);
	// https://wiki.unrealengine.com/UMG,_Referencing_UMG_Widgets_in_Code
	static void ExecuteConsoleCommand(const FString& Command);
	static void AddToViewport(UUserWidget* userWidget);

	template< class T >
	static T* MCreateWidget(UWorld* World, UClass* UserWidgetClass = T::StaticClass());

	template< class T >
	static T* MCreateWidget(APlayerController* OwningPlayer, UClass* UserWidgetClass = T::StaticClass());

	template< class T >
	static T* MCreateWidget(UGameInstance* OwningGame, UClass* UserWidgetClass = T::StaticClass());

	// F:\File\opensource\UnrealEngine-4.0\UnrealEngine-git\Engine\Source\Programs\CrashReporter\CrashReportClient\Private\CrashReportClient.cpp
	// /** Copies text to the operating system clipboard. */
	static void ClipboardCopy(const TCHAR* Str);

	/** Pastes in text from the operating system clipboard. */
	static void ClipboardPaste(class FString& Dest);

	// f:\File\opensource\UnrealEngine-4.0\UnrealEngine-git\Engine\Source\Runtime\Slate\Public\Framework\Application\SlateApplication.h
	/** @return an array of top-level windows that can be interacted with. e.g. when a modal window is up, only return the modal window */
	static TArray< TSharedRef<class SWindow> > GetInteractiveTopLevelWindows();

	static bool FindPathToWidget(TSharedRef<const SWidget> InWidget, FWidgetPath& OutWidgetPath, EVisibility VisibilityFilter = EVisibility::Visible);

	static bool FindPathToWidget(const TArray<TSharedRef<SWindow>>& WindowsToSearch, TSharedRef<const SWidget> InWidget, FWidgetPath& OutWidgetPath, EVisibility VisibilityFilter = EVisibility::Visible);

	static bool SetKeyboardFocus(const TSharedPtr<SWidget>& OptionalWidgetToFocus, EFocusCause ReasonFocusIsChanging = EFocusCause::SetDirectly);

	static void SetUserFocusToGameViewport(uint32 UserIndex, EFocusCause ReasonFocusIsChanging = EFocusCause::SetDirectly);

	// Engine\Source\Runtime\Online\HTTP\Public\GenericPlatform\GenericPlatformHttp.h
	static FString UrlEncode(const FString& UnencodedString);

	//static bool OpenLauncher(const FOpenLauncherOptions& Options);

	// Engine\Source\Runtime\Core\Public\Windows\WindowsPlatformProcess.h
	static FProcHandle CreateProc(const TCHAR* URL, const TCHAR* Parms, bool bLaunchDetached, bool bLaunchHidden, bool bLaunchReallyHidden, uint32* OutProcessID, int32 PriorityModifier, const TCHAR* OptionalWorkingDirectory, void* PipeWriteChild, void * PipeReadChild = nullptr);

	template<class T>
	static TSubclassOf<T> FindClass(const TCHAR* ClassToFind);

	template<class T>
	static T* FindObject(const TCHAR* ObjectToFind);

	template< class T >
	static T* MNewObject(UObject* Outer, UClass* Class, FName Name = NAME_None, EObjectFlags Flags = RF_NoFlags, UObject* Template = nullptr, bool bCopyTransientsFromClassDefaults = false, FObjectInstancingGraph* InInstanceGraph = nullptr);

	template< class T >
	static T* MNewObject(UObject* Outer = (UObject*)GetTransientPackage());

	template< class T >
	static T* MNewObject(UObject* Outer, FName Name, EObjectFlags Flags = RF_NoFlags, UObject* Template = nullptr, bool bCopyTransientsFromClassDefaults = false, FObjectInstancingGraph* InInstanceGraph = nullptr);

	template< class T >
	static T* MDuplicateObject(T const* SourceObject, UObject* Outer, const FName Name = NAME_None);
};

#include "EngineApi.inl"

#endif				// __ENGINEAPI_H