#pragma once

#include "MyProject.h"

/**
 * @brief https://wiki.unrealengine.com/Dynamic_Load_Object
 */

//Get Path
static FORCEINLINE FName GetObjPath(const UObject* Obj)
{
	if (!Obj)
	{
		return NAME_None;
	}
	//~

	FStringAssetReference ThePath = FStringAssetReference(Obj);

	if (!ThePath.IsValid()) return NAME_None;

	//The Class FString Name For This Object
	FString Str = Obj->GetClass()->GetDescription();

	Str += "'";
	Str += ThePath.ToString();
	Str += "'";

	return FName(*Str);
}

//TEMPLATE Load Obj From Path
template <typename ObjClass>
static FORCEINLINE ObjClass* LoadObjFromPath(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	//~

	return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path.ToString()));
}

// Load PS From Path 
static FORCEINLINE UParticleSystem* LoadPSFromPath(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	//~

	return LoadObjFromPath<UParticleSystem>(Path);
}


// Load Material From Path 
static FORCEINLINE UMaterialInterface* LoadMatFromPath(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	//~

	return LoadObjFromPath<UMaterialInterface>(Path);
}

// Load Static Mesh From Path 
static FORCEINLINE UStaticMesh* LoadMeshFromPath(const FName& Path)
{
	if (Path == NAME_None) return NULL;
	//~

	return LoadObjFromPath<UStaticMesh>(Path);
}