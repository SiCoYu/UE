#pragma once

//#include "GameMapsSettings.h"	// UGameMapsSettings
//#include "MyMapsSettings.generated.h"

/**
 UGameMapsSettings 不能继承，因为代码里面都是直接获取 UGameMapsSettings 的
 const UGameMapsSettings* GameMapsSettings = GetDefault<UGameMapsSettings>();
 但是 UGameMapsSettings 可以在配置文件 Engine\Config\BaseEngine.ini 中进行设置
 */

//UCLASS()
//class UMyMapsSettings : public UGameMapsSettings
//{
//	GENERATED_UCLASS_BODY()
//};