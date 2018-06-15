#ifndef __ObjectAssetInsResBase_H
#define __ObjectAssetInsResBase_H

#include "ResInsBase.h"
#include <string>
#include "Math/Vector.h"	// FVector
#include "Math/Quat.h"	// FQuat
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "ResPackType.h"
#include "PlatformDefine.h"

class UObject;
class UClass;

MY_BEGIN_NAMESPACE(MyNS)

class ResInsEventDispatch;

class ObjectAssetInsResBase : public ResInsBase
{
	M_DECLARE_CLASS(ObjectAssetInsResBase, ResInsBase)

protected:
	UObject* mActor;
	UObject* mRetActor;
	ResPackType mResPackType;    // 资源打包类型

public:
	ObjectAssetInsResBase();
	// warning C4265: 'ObjectAssetInsResBase': class has virtual functions, but destructor is not virtual instances of this class may not be destructed correctly
	virtual ~ObjectAssetInsResBase();

protected:
	virtual void _initWithResImpl(ResItem* res) override;

public:
	UObject* InstantiateObject(std::string resName, bool isSetInitOrientPos = false, FVector position = FVector::ZeroVector, FQuat rotation = FQuat::Identity, ResInsEventDispatch* evtHandle = nullptr);
	UObject* getObject();
	UClass* getClass();
	virtual void unload() override;
};

MY_END_NAMESPACE

#endif