#ifndef __ENGINEAPI_H
#define __ENGINEAPI_H

// #include "Platform.h"
#include "Core.h"		// "Platform.h" �Ѿ������� "Core.h" ����
//#include "ICUUtilities.h"

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

	ACharacter* getFirstCharacter();	// ��ȡ��һ�� ACharacter �����������Լ�

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
};

#endif				// __ENGINEAPI_H