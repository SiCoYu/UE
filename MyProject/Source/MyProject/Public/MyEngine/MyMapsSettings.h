#pragma once

//#include "GameMapsSettings.h"	// UGameMapsSettings
//#include "MyMapsSettings.generated.h"

/**
 UGameMapsSettings 不能继承，因为代码里面都是直接获取 UGameMapsSettings 的
 const UGameMapsSettings* GameMapsSettings = GetDefault<UGameMapsSettings>();
 */

//UCLASS()
//class UMyMapsSettings : public UGameMapsSettings
//{
//	GENERATED_UCLASS_BODY()
//};