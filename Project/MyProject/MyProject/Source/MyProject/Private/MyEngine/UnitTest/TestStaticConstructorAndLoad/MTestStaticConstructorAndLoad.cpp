#include "MyProject.h"
#include "MTestStaticConstructorAndLoad.h"

AMTestStaticConstructorAndLoad::AMTestStaticConstructorAndLoad(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{

}

AMTestStaticConstructorAndLoad::AMTestStaticConstructorAndLoad()
{
	// Structure to hold one-time initialization
    static FClassFinder<UNavigationMeshBase> ClassFinder(TEXT("class'Engine.NavigationMeshBase'"));
    if (ClassFinder.Succeeded())
    {
        NavMeshClass = ClassFinder.Class;
    }
    else
    {
        NavMeshClass = nullptr;
    }
	
	// In many cases, you can just use USomeClass::StaticClass() and skip the complexity of the ClassFinder altogether. For example, you can use the method below in most circumstances: 
	NavMeshClass = UNavigationMeshBase::StaticClass();
	
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