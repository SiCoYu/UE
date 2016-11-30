#ifndef __ENGINEAPI_H
#define __ENGINEAPI_H

// #include "Platform.h"
#include "Core.h"		// "Platform.h" 已经包含在 "Core.h" 中了
//#include "ICUUtilities.h"

class UGameInstance;
class UMyProjectEngine;
class UMyProjectGameInstance;
class UUserWidget;

class EngineApi
{
public:
	static UGameInstance* getGameInstance();
	static UWorld* getWorld();
	static void showCursor();
	static UMyProjectEngine* getEngine();
	static UMyProjectGameInstance* getMyProjectGameInstanceByEngine();
	static UWorld* getWorldByEngine();

	static ACharacter* getFirstCharacter();	// 获取第一个 ACharacter ，就是主角自己

	static void addEventHandle(UButton* pBtn, UObject* pFuncObj, FName funcName);
	static float getUTCSec();
	static float GetRealTimeSeconds();
	/**
	 *@brief 插入挂在点
	 */
	static void InsertMountPoint(const FString& RootPath, const FString& ContentPath);
	/**
	 *@brief 文件是否存在
	 *@param InPath 这个是完整的目录
	 */
	static bool FileExists(const FString& InPath);
	/**
	 *@brief 包对应的文件是否存在
	 *@param InPackageFilename 这个完整的包的目录，例如 "/Game/UMG/UITestCanvas_Canvas"
	 */
	static bool PackageExists(const FString& InPackageFilename);
	/**
	 *@brief 获取游戏用户目录，类似 Unity 的 Application.persistentDataPath 可写目录
	 */
	static FString GameUserDir();
	static void SetActive(UWidget* target, bool bshow);
	static void Destroy(UWidget* obj);
	static void UnloadUnusedAssets();

	static void SetParent(UWidget*child, UPanelWidget* parent, bool worldPositionStays = true);

	/**
	 * @brief 添加一个 Child 
	 */
	void SetContentForSlot(UUserWidget* userWidget, FName SlotName, UWidget* Content);

	//static void ConvertString(const FString& Source, icu::UnicodeString& Destination, const bool ShouldNullTerminate);

	/**
	 * @brief 光线点选
	 */
	static bool LineTraceSingleByChannel(UWorld* World, struct FHitResult& OutHit, const FVector& Start, const FVector& End, ECollisionChannel TraceChannel, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam);

	/**
	 * @brief 区域点选
	 */
	static bool SweepTestByChannel(UWorld* World, const FVector& Start, const FVector& End, const FQuat& Rot, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam);

	/**
	 * @brief 重叠测试点选
	 */
	static bool OverlapBlockingTestByChannel(UWorld* World, const FVector& Pos, const FQuat& Rot, ECollisionChannel TraceChannel, const FCollisionShape& CollisionShape, const FCollisionQueryParams& Params = FCollisionQueryParams::DefaultQueryParam, const FCollisionResponseParams& ResponseParam = FCollisionResponseParams::DefaultResponseParam);

	/**
	 * @brief 从 UInputComponent 获取 Axis 输入值
	 */
	float GetAxisValue(UInputComponent* pUInputComponent, const FName AxisName);
	/**
	 * @brief 从 AActor 获取 Axis 输入值
	 */
	float GetInputAxisValue(AActor* pAActor, const FName InputAxisName);
	/**
	 * @brief 从 MainActor 获取 Axis 输入值
	 */
	float GetInputAxisValue(const FName InputAxisName);

	/**
	 * @brief 获取场景组件的具体位置信息
	 */
	static FTransform& getTransform(USceneComponent* pUSceneComponent);

	/**
	 * @brief 启动浏览器，浏览网址
	 * @brief https://wiki.unrealengine.com/How_to_Launch_Web_Browser_with_URL_From_In-Game
	 */
	static void LaunchURL(FString url);
};

#endif				// __ENGINEAPI_H