#include "MyProject.h"
#include "MTestStaticConstructorAndLoad.h"
#include "ConstructorHelpers.h"

// warning C4828: The file contains a character starting at offset 0x168 that is illegal in the current source character set (codepage 65001).
// 转换成 UTF-8 Without BOM
AMTestStaticConstructorAndLoad::AMTestStaticConstructorAndLoad(const FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

AMTestStaticConstructorAndLoad::AMTestStaticConstructorAndLoad()
{
	// FClassFinder 是类的内部类，一定要加外部类，否则编译不过
	// Structure to hold one-time initialization
    //static FClassFinder<UNavMovementComponent> ClassFinder(TEXT("class'Engine.UNavMovementComponent'"));
	static ConstructorHelpers::FClassFinder<UNavMovementComponent> ClassFinder(TEXT("class'Engine.UNavMovementComponent'"));

    if (ClassFinder.Succeeded())
    {
        NavMeshClass = ClassFinder.Class;
    }
    else
    {
        NavMeshClass = nullptr;
    }
	
	// In many cases, you can just use USomeClass::StaticClass() and skip the complexity of the ClassFinder altogether. For example, you can use the method below in most circumstances: 
	NavMeshClass = UNavMovementComponent::StaticClass();
	
    // Structure to hold one-time initialization
    struct FConstructorStatics
    {
        ConstructorHelpers::FObjectFinder<UStaticMesh> Object0;
        FConstructorStatics()
        : Object0(TEXT("StaticMesh'/Game/UT3/Pickups/Pickups/Health_Large/Mesh/S_Pickups_Base_Health_Large.S_Pickups_Base_Health_Large'"))
        {
        }
    };

    static FConstructorStatics ConstructorStatics;

    // Property initialization

    StaticMesh = ConstructorStatics.Object0.Object;
}