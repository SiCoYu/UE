#ifndef __UtilEngineWrap_H
#define __UtilEngineWrap_H

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
#include "UObject/UObjectGlobals.h"	// DuplicateObject, CollectGarbage
#include "AudioDevice.h"		// FAudioDevice
#include <string>	// string
#include "PlatformDefine.h"

class UMyGameEngineBase;
class UMyGameInstanceBase;
class UUserWidget;
class SWindow;
struct FWorldContext;
class UWorld;
class AMyPlayerControllerBase;
class UMyLocalPlayerBase;
class UMyGameViewportClientBase;
class UMeshComponent;
class UMaterialInterface;
class UWidget;
class UPrimitiveComponent;
class UMaterialInstanceDynamic;


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

MY_BEGIN_NAMESPACE(MyNS)

class UtilEngineWrap
{
public:
	static UMyGameInstanceBase* GetGameInstance();
	static UWorld* GetWorld();
	static void showCursor();
	static UMyGameEngineBase* getEngine();
	static UMyGameInstanceBase* getMyGameInstanceByEngine();
	static UMyGameInstanceBase* getMyGameInstanceByController();
	static UWorld* getWorldByEngine();

	// ���ܷ��� ACharacter ����Ϊ����ʹ�õ��Ǽ̳��� ACharacter �ģ���Ҫ���๦�ܵģ����߼̳��� APawn �ģ�����Ҫ���๦��
	//static ACharacter* getFirstCharacter();	// ��ȡ��һ�� ACharacter �����������Լ�
	static APawn* getFirstCharacter();	// ��ȡ��һ�� ACharacter �����������Լ�
	static AMyPlayerControllerBase* GetPlayerController();
	static FWorldContext* GetWorldContextByGameInstance();
	static UWorld* GetWorldByWorldContext();
	static UMyGameInstanceBase* GetGameInstanceByWorld();
	static UMyLocalPlayerBase* GetLocalPlayerByPlayerController();

	static ULevel* getCurrentLevelFromWorld();
	static ULevel* getPersistentLevelFromWorld();
	static UGameInstance* getGameInstanceFromWorld();
	static TArray<AActor*>& getActorArrayFromCurrentLevel();
	// ����ӿ�ֻ���� World ������ɺ����ʹ��
	static inline UWorld* GetGlobalWorld();

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
	static FORCEINLINE T Max(const TArray<T>& Values, int32* MaxIndex = nullptr);

	// https://wiki.unrealengine.com/Solus_C%2B%2B_Tutorials
	// ʹ�� Cast<AYourLevelScriptActor>GetLevelScriptActor();
	ALevelScriptActor* GetLevelScriptActor(ULevel* OwnerLevel = nullptr) const;

	// https://wiki.unrealengine.com/Solus_C%2B%2B_Tutorials
	static FORCEINLINE void GetDisplayAdapterScreenResolutions(FScreenResolutionArray& Resolutions);

	// https://wiki.unrealengine.com/Solus_C%2B%2B_Tutorials
	static bool IsTextValid(FText MyText);

	// https://wiki.unrealengine.com/Game_Instance,_Custom_Game_Instance_For_Inter-Level_Persistent_Data_Storage#Overview
	static void ClientMessage(FString str);

	// https://wiki.unrealengine.com/Solus_C%2B%2B_Tutorials
	// FText::Format FText ��ʽ��
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
	static T* CreateWidget(UWorld* World, UClass* UserWidgetClass = T::StaticClass());

	template< class T >
	static T* CreateWidget(APlayerController* OwningPlayer, UClass* UserWidgetClass = T::StaticClass());

	template< class T >
	static T* CreateWidget(UGameInstance* OwningGame, UClass* UserWidgetClass = T::StaticClass());

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

	// Engine\Source\Runtime\Slate\Private\Framework\Application\SlateApplication.cpp
	//void FSlateApplication::SetFocusToGameViewport()
	//{
	//	SetUserFocusToGameViewport(GetUserIndexForKeyboard(), EFocusCause::SetDirectly);
	//}
	static void SetUserFocusToGameViewport(uint32 UserIndex, EFocusCause ReasonFocusIsChanging = EFocusCause::SetDirectly);

	static int32 GetUserIndexForKeyboard();

	// Engine\Source\Runtime\Online\HTTP\Public\GenericPlatform\GenericPlatformHttp.h
	static FString UrlEncode(const FString& UnencodedString);

	//static bool OpenLauncher(const FOpenLauncherOptions& Options);

	// Engine\Source\Runtime\Core\Public\Windows\WindowsPlatformProcess.h
	static FProcHandle CreateProc(const TCHAR* URL, const TCHAR* Parms, bool bLaunchDetached, bool bLaunchHidden, bool bLaunchReallyHidden, uint32* OutProcessID, int32 PriorityModifier, const TCHAR* OptionalWorkingDirectory, void* PipeWriteChild, void * PipeReadChild = nullptr);

	// ���캯�����ܵ��ú���
	template<class T>
	static TSubclassOf<T> FindClass(const TCHAR* ClassToFind);

	template<class T>
	static T* FindObject(const TCHAR* ObjectToFind);

	template< class T >
	inline static T* FindObject(UObject* Outer, const TCHAR* Name, bool ExactClass = false);

	// �κεط������Ե���
	// Load an object.
	template< class T >
	static inline T* LoadObject(UObject* Outer, const TCHAR* Name, const TCHAR* Filename = nullptr, uint32 LoadFlags = LOAD_None, UPackageMap* Sandbox = nullptr);

	// Load a class object.
	template< class T >
	static inline UClass* LoadClass(UObject* Outer, const TCHAR* Name, const TCHAR* Filename = nullptr, uint32 LoadFlags = LOAD_None, UPackageMap* Sandbox = nullptr);

	// �κεط������Ե���
	// �ο� Engine\Source\Runtime\CoreUObject\Public\UObject\ConstructorHelpers.h
	// inline UClass* FindOrLoadClass(FString& PathName, UClass* BaseClass)
	static UObject* StaticLoadObject(UClass* Class, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename = NULL, uint32 LoadFlags = LOAD_None, UPackageMap* Sandbox = NULL, bool bAllowObjectReconciliation = true);

	static UClass* StaticLoadClass(UClass* BaseClass, UObject* InOuter, const TCHAR* Name, const TCHAR* Filename = NULL, uint32 LoadFlags = LOAD_None, UPackageMap* Sandbox = NULL);

	template< class T >
	static T* NewObject(UObject* Outer, UClass* Class, FName Name = NAME_None, EObjectFlags Flags = RF_NoFlags, UObject* Template = nullptr, bool bCopyTransientsFromClassDefaults = false, FObjectInstancingGraph* InInstanceGraph = nullptr);

	template< class T >
	static T* NewObject(UObject* Outer = (UObject*)GetTransientPackage());

	template< class T >
	static T* NewObject(UObject* Outer, FName Name, EObjectFlags Flags = RF_NoFlags, UObject* Template = nullptr, bool bCopyTransientsFromClassDefaults = false, FObjectInstancingGraph* InInstanceGraph = nullptr);

	template< class T >
	static T* DuplicateObject(T const* SourceObject, UObject* Outer, const FName Name = NAME_None);

	static FString GetPathName(const UObject* curObj, const UObject* StopOuter/*=NULL*/);

	template< class T >
	inline static T* FindSceneActor(const TCHAR* Name);

	template< class T >
	inline static T* FindSceneObject(const TCHAR* Name);

	inline static double Seconds();

	inline static FWorldContext* GetWorldContextFromPIEInstance(const int32 PIEInstance = 0);

	// Engine\Source\Editor\UnrealEd\Private\PlayLevel.cpp
	// ����������С
	static inline void SetTransientMasterVolume(float size);

	// Engine\Source\Runtime\Engine\Private\GameInstance.cpp
	static UMyGameViewportClientBase* const GetGameViewportClient();
	static FViewport* const GetViewport();
	// Engine\Source\Runtime\Engine\Private\UnrealEngine.cpp
	static void EnableScreenSaver(bool bEnable);

	// Engine\Source\Runtime\CoreUObject\Public\UObject\UObjectGlobals.h
	int32 LoadPackageAsync(const FString& InName, FLoadPackageAsyncDelegate InCompletionDelegate, TAsyncLoadPriority InPackagePriority = 0, EPackageFlags InPackageFlags = PKG_None);

	void CancelAsyncLoading();
	float GetAsyncLoadPercentage(const FName& PackageName);
	bool IsGarbageCollecting();
	void CollectGarbage(EObjectFlags KeepFlags, bool bPerformFullPurge = true);
	bool TryCollectGarbage(EObjectFlags KeepFlags, bool bPerformFullPurge = true);

	// Engine\Source\Runtime\Engine\Private\UnrealEngine.cpp
	static const FWorldContext* GetWorldContextFromGameViewport(const UGameViewportClient *InViewport);

	static APlayerController* GetPrimaryPlayerController();
	// InTravelType = TRAVEL_Absolute
	// void UEngine::TickWorldTravel(FWorldContext& Context, float DeltaSeconds)
	// TickWorldTravel ��ʱ���ִ�����õĵ�ͼ
	/**
	 * @brief [UE4]ServerTravel��ClientTravel���� 
	 * @url http://www.dawnarc.com/2017/06/ue4servertravel%E5%92%8Cclienttravel%E5%8C%BA%E5%88%AB/
	 * Browse, LoadMap, ServerTravel and ClientTravel?
	 * https://answers.unrealengine.com/questions/122565/browse-servertravel-and-clienttravel.html
	 * What��s the different between absolute travel and relative travel?
	 * https://answers.unrealengine.com/questions/101284/what-the-different-between-absolute-travel-and-rel.html
	 * What is the difference between ServerTravel and OpenLevel?
	 * https://answers.unrealengine.com/questions/55477/the-difference-of-the-two-functions.html
	 * PlayerController->ClientTravel()����Զ�̷�����
	 * https://answers.unrealengine.com/questions/29017/gamemode-multiplayer-c.html
	 * Seamless and non-seamless travel
	 * https://docs.unrealengine.com/latest/INT/Gameplay/Networking/Travelling
	 * ���⣬���Բμӹٷ�ShooterGame��APlayerController->ClientTravel()�÷���
	 */
	static void SetClientTravel(UWorld *InWorld, const TCHAR* NextURL, ETravelType InTravelType);
	static bool ServerTravel(const FString& InURL, bool bAbsolute = false, bool bShouldSkipGameNotify = false);

	/**
	 * @brief ���4��̬���ػ��棨��̨���عؿ�����ʵ��
	 * @url https://blog.csdn.net/sinat_27456831/article/details/49933285
	 * ����֪�������Ҫ�����µĹؿ�һ����ͨ��Open Level����ʵ�֣�������ʾ�����ǣ�load level�������������̣����֮ǰ�м��ض����ڲ��ŵĻ�����ִ��load level����ʱ�����н��̶�ֹͣ����������ֹͣ������Ϊ��֤��ͼ�� ����һ�ӹؿ����һ��������Ի������¡��ڡ�Change Streaming Method���¿���ѡ��ǰ�ؿ��ǡ����Ǽ��ء�����ͨ������ͼ�����ơ�ѡ����ͼ������������ǰ�ؿ������翪ʼ����ϷUI���棩ʱ�Ͳ�������ӹؿ���ͨ��load stream level�Ϳ����ں�̨�����ӹؿ�������Ӱ�쵱ǰ�������̣������ڽ��еĶ�̬���ػ��棩�� 
	 * @url http://api.unrealengine.com/INT/BlueprintAPI/Game/OpenLevel/
	 * @url https://answers.unrealengine.com/questions/32953/open-level-function.html
	 * @brief I have CargoBayMap_Version1.umap in the default value of the name variable. I have tried it with and without the umap extension as well as typing the name in directly. I also tried the travel command using an Execute Console Command function and this did not work either. I also tried in the editor and when launched on my computer.
	 * @url https://answers.unrealengine.com/questions/441857/open-level-options.html
	 */
	static void OpenLevel(const UObject* WorldContextObject, FName LevelName, bool bAbsolute, FString Options);
	static void OpenLevel(const UObject* WorldContextObject, std::string LevelName, bool bAbsolute, FString Options);
	static void LoadStreamLevel(const UObject* WorldContextObject, FName LevelName, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, FLatentActionInfo LatentInfo);
	static void LoadStreamLevel(const UObject* WorldContextObject, std::string LevelName, bool bMakeVisibleAfterLoad, bool bShouldBlockOnLoad, FLatentActionInfo LatentInfo);
	static void UnloadStreamLevel(const UObject* WorldContextObject, FName LevelName, FLatentActionInfo LatentInfo);

	static UMyLocalPlayerBase* UtilEngineWrap::GetLocalPlayerFromControllerId(const UGameViewportClient* InViewport, const int32 ControllerId);

	static int GetNumLocalPlayers();

	static void SetGameDefaultMap(const std::string& NewMap);

	// http://www.cnblogs.com/zhouxin/p/5454077.html
	template<class T>
	T* FindActor(FString name);

	// UE4 �����ܽ�: http://blog.csdn.net/lzt20007/article/details/51058598
	static FVector2D getScreenSize();

	// UE4��GetViewportSize��GSystemResolution: http://blog.csdn.net/lzt20007/article/details/51141328
	static FVector2D getSystemResolution();

	// Engine\Source\Runtime\Engine\Private\Components\MeshComponent.cpp
	static void SetMaterial(UMeshComponent* meshComponent, int32 ElementIndex, UMaterialInterface* Material);
	static UMaterialInstanceDynamic* SetMaterial(UPrimitiveComponent* primitiveComponent, int32 ElementIndex, UMaterialInterface* Material);

	// ue4-���ݶ����ƴ�ȡ: http://blog.csdn.net/yangxuan0261/article/details/54406581 , ������ַ: Read%26_Write_Any_Data_to_Compressed_Binary_Files�� , https://wiki.unrealengine.com/Save_System,Read%26_Write_Any_Data_to_Compressed_Binary_Files
	void TestFileWriteCompressed(FString _path);
	void TestFileReadCompressed(FString _path);
	void TestFileWriteUnCompressed(FString _path);
	void TestFileReadUnCompressed(FString _path);

	static bool IsPendingKill(AActor* actor);
	static void Destroy(AActor* actor);
	
	// Engine\Source\Runtime\Core\Private\Misc\Core.cpp	\ GFrameNumber \ GFrameNumberRenderThread
	static uint32 getFrameNumber();
	static uint32 getFrameNumberRenderThread();

	// �ж��Ƿ��Ƕ��߳�
	static bool isMultithreaded();
	// �Ƿ����֧�ֶ��߳�
	static bool isInAsyncLoadingThread();
	// �Ƿ���Ҫ Cook ����
	static bool requiresCookedData();
	// �����Ƿ�ɼ�
	static bool isWidgetVisible(UWidget* widget);
	static void setWidgetVisible(UWidget* widget, bool isVisible);

	static FColor convLineColorToColor(FLinearColor lineColor);
	static FLinearColor convColorToLineColor(FColor color);

	static void setActorPos(AActor* actor, FVector NewLocation);
	static void setActorRotate(AActor* actor, FRotator NewRotation);
	static void setActorScale(AActor* actor, FVector NewScale3D);

	void AddActorLocalOffset(AActor* actor, FVector DeltaLocation, bool bSweep = false, FHitResult* OutSweepHitResult = nullptr, ETeleportType Teleport = ETeleportType::None);
	void AddActorLocalRotation(AActor* actor, const FQuat& DeltaRotation, bool bSweep = false, FHitResult* OutSweepHitResult = nullptr, ETeleportType Teleport = ETeleportType::None);

	static FVector getActorPos(AActor* actor);
	static FRotator getActorRotate(AActor* actor);
	static FVector getActorScale(AActor* actor);

	static FTransform getActorTransform(AActor* actor);

	static USceneComponent* getActorRootComponent(AActor* actor);
	static FVector getActorPivotOffset(AActor* actor);
	static void setActorVisible(AActor* actor, bool isVisible);
	static void setActorEnableCollision(AActor* actor, bool isEnable);

	static void AttachToComponent(AActor* actor, USceneComponent* Parent, const FAttachmentTransformRules& AttachmentRules, FName SocketName = NAME_None);
	static void AttachToActor(AActor* actor, AActor* ParentActor, const FAttachmentTransformRules& AttachmentRules, FName SocketName = NAME_None);

	static void setActorComponentActive(UActorComponent* actorComponent, bool isActive);
	static AActor* getActorComponentOwner(UActorComponent* actorComponent);
	static UWorld* getWorldByActorComponent(UActorComponent* actorComponent);

	template<class T>
	static inline T* getComponentByClass(AActor* actor);
	static const TSet<UActorComponent*>& getAllComponent(AActor* actor);
	static const void destroyComponent(UActorComponent* actorComponent);
	// Engine\Source\Runtime\Engine\Classes\Materials\MaterialInstanceDynamic.h
	static void setScalarParameterValue(UMaterialInstanceDynamic* materialInstanceDynamic, FName ParameterName, float Value);
	// Engine\Source\Runtime\Engine\Private\Materials\MaterialInstanceDynamic.cpp
	static void setTextureParameterValue(UMaterialInstanceDynamic* materialInstanceDynamic, FName ParameterName, UTexture* Value);
	// �����������գ�������Ҫ�ֹ����ã�UE4 �����Լ��Ѿ�������
	static void conditionalCollectGarbage();
	// UObject\UObjectGlobals.h
	static void collectGarbage(EObjectFlags KeepFlags, bool bPerformFullPurge = true);
};

MY_END_NAMESPACE

#include "UtilEngineWrap.inl"

#endif				// __UtilEngineWrap_H