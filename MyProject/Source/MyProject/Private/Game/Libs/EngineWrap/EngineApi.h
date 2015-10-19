#ifndef __ENGINEAPI_H
#define __ENGINEAPI_H

// #include "Platform.h"
#include "Core.h"		// "Platform.h" 已经包含在 "Core.h" 中了

class UGameInstance;
class UMyProjectEngine;
class UMyProjectGameInstance;
class UUserWidget;

class EngineApi
{
public:
	virtual UGameInstance* getGameInstance();
	virtual UWorld* getWorld();
	virtual void showCursor();
	UMyProjectEngine* getEngine();
	UMyProjectGameInstance* getMyProjectGameInstanceByEngine();
	UWorld* getWorldByEngine();

	ACharacter* getFirstCharacter();	// 获取第一个 ACharacter ，就是主角自己

	static void addEventHandle(UButton* pBtn, UObject* pFuncObj, FName funcName);
	static uint32 getUTCSec();
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
};

#endif				// __ENGINEAPI_H