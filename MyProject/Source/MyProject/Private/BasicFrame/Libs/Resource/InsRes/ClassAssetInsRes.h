#ifndef __ClassAssetInsRes_H
#define __ClassAssetInsRes_H

#include "InsResBase.h"
#include <string>
#include "Math/Vector.h"	// FVector
#include "Math/Quat.h"	// FQuat

class UClass;
class UObject;
class ResInsEventDispatch;

class ClassAssetInsRes : public InsResBase
{
public:
	UClass* mGo;
	UObject* mRetGO;

public:
	ClassAssetInsRes();

protected:
	virtual void initImpl(ResItem* res) override;

public:
	UObject* InstantiateObject(std::string resName, bool isSetInitOrientPos, FVector position, FQuat rotation, ResInsEventDispatch* evtHandle);
	UClass* getObject();
	virtual void unload() override;
};

#endif