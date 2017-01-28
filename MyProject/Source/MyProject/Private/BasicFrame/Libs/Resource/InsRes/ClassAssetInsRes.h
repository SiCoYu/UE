#ifndef __ClassAssetInsRes_H
#define __ClassAssetInsRes_H

#include "InsResBase.h"
#include <string>
#include "Math/Vector.h"	// FVector
#include "Math/Quat.h"	// FQuat
#include "BaseClassDef.h"

class UClass;
class UObject;
class ResInsEventDispatch;

class ClassAssetInsRes : public InsResBase
{
	M_DECLARE_SUPER_KW(InsResBase)

public:
	UClass* mGo;
	UObject* mRetGO;

public:
	ClassAssetInsRes();

protected:
	virtual void initImpl(ResItem* res) override;

public:
	UObject* InstantiateObject(std::string resName, bool isSetInitOrientPos = false, FVector position = FVector::ZeroVector, FQuat rotation = FQuat::Identity, ResInsEventDispatch* evtHandle = nullptr);
	UClass* getObject();
	virtual void unload() override;
};

#endif