#ifndef __ENGINEAPI_H
#define __ENGINEAPI_H

// #include "Platform.h"
#include "Core.h"		// "Platform.h" �Ѿ������� "Core.h" ����

class UGameInstance;
class UMyProjectEngine;
class UMyProjectGameInstance;

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
	static uint32 getUTCSec();
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
};

#endif				// __ENGINEAPI_H