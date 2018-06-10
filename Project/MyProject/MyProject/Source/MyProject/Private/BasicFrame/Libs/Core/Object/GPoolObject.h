#pragma once

#include <string>
#include "IPoolObject.h"
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
	public GPoolObject();

	virtual public void init();
	virtual protected void onInit();
	virtual protected void onGetFromPool();
	virtual protected void onPutInPool();
	virtual public void dispose();
	virtual public void destroy();
	virtual protected void onDestroy();
	public bool isUsePool();
	public void setIsUsePool(bool value);
	public void putInPool();
	public void getFromPool();
	public void setNumUniqueId(int value);
	public int getNumUniqueId();
	public void setStrUniqueId(string value);
	public std::string getStrUniqueId();
};

MY_END_NAMESPACE