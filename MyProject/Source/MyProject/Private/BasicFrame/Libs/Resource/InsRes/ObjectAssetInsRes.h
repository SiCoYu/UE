#ifndef __ObjectAssetInsRes_H
#define __ObjectAssetInsRes_H

#include "InsResBase.h"
#include <string>
#include "Math/Vector.h"	// FVector
#include "Math/Quat.h"	// FQuat

class UObject;
class ResInsEventDispatch;

class ObjectAssetInsRes : public InsResBase
{
public:
	UObject* mGo;
	UObject* mRetGO;

public:
	ObjectAssetInsRes();
protected:
	virtual void initImpl(ResItem* res) override;

public:
	UObject* InstantiateObject(std::string resName, bool isSetInitOrientPos, FVector position, FQuat rotation, ResInsEventDispatch* evtHandle);
	UObject* getObject();
	virtual void unload() override;
};

#endif