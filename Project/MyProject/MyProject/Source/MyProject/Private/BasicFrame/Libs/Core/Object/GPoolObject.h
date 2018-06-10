#pragma once

#include <string>
#include "IPoolObject.h"
#include "GObjectBase.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class GPoolObject : public GObjectBase, public IPoolObject
{
	M_DECLARE_CLASS(GPoolObject, GObjectBase)

protected:
	bool mIsUsePool;      // 是否使用 Pool
	int mNumUniqueId;
	std::string mStrUniqueId;

public:
	GPoolObject();

	virtual public void init();
	virtual protected void onInit();
	virtual protected void onGetFromPool();
	virtual protected void onPutInPool();
	virtual public void dispose();
	virtual public void destroy();
	virtual protected void onDestroy();
	bool isUsePool();
	void setIsUsePool(bool value);
	void putInPool();
	void getFromPool();
	void setNumUniqueId(int value);
	int getNumUniqueId();
	void setStrUniqueId(std::string value);
	std::string getStrUniqueId();
};

MY_END_NAMESPACE