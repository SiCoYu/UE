#pragma once

#include "MyProject.h"
#include "SubclassAccessOrdnance.h"
#include "SubclassAccessWeaponData.generated.h"

/**
* @brief https://wiki.unrealengine.com/Access_Functions_%26_Variables_From_a_TSubclassOf_Variable_in_C%2B%2B
* @brief TSubclassOf is a special template of UClass which only accepts specific subclasses of some base class. So it's still a UClass which is just a class specifier which you can spawn things from, but it does not have the variables or functions of the declared class. however, you can GetDefaultObject<T>() which is a master copy of the defined class object and contains the default variables which you can use before spawning that object.
* @brief TSubclassOf 的类型一般是 UClass 的子类，而 UClass 一般是 Blueprint 类型
*/


USTRUCT()
struct FSubclassAccessWeaponData
{
	GENERATED_USTRUCT_BODY()

public:
	/* Actual Ordnance To Fire */
	UPROPERTY(EditDefaultsOnly, Category = "Ordnance")
	TSubclassOf<ASubclassAccessOrdnance> OrdnanceClass;

	FSubclassAccessWeaponData()
		: OrdnanceClass(nullptr)
	{
	}
};