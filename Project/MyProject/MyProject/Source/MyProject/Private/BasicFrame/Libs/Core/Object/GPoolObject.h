#pragma once

#include <string>
#include "IPoolObject.h"
#include "MyAllocatedObject.h"
#include "TypeUniqueId.h"
#include "AssetUniqueId.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class GPoolObject : public MyAllocatedObject, public IPoolObject
{
	M_DECLARE_CLASS(GPoolObject, MyAllocatedObject)

protected:
	bool mIsUsePool;      // 是否使用 Pool
	std::string mGlobalUniqueId;
	TypeUniqueId mTypeUniqueId;
	AssetUniqueId mAssetUniqueId;

public:
	GPoolObject();

	virtual void init();

//protected:
public:
	virtual void onInit();
	virtual void onGetFromPool();
	virtual void onPutInPool();
	virtual void onDestroy();

public:
	virtual void dispose();
	virtual void destroy();

	virtual bool isUsePool();
	virtual void setIsUsePool(bool value);
	virtual void putInPool();
	virtual void getFromPool();
	void setGlobalUniqueId(std::string value);
	std::string getGlobalUniqueId();

	virtual void resetDefault() override;
};

MY_END_NAMESPACE