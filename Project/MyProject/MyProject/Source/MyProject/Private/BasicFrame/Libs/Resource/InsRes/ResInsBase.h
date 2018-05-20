#ifndef __ResInsBase_H
#define __ResInsBase_H

#include "IDispatchObject.h"
#include <string>

class RefCountResLoadResultNotify;
class ResItem;

class ResInsBase : public IDispatchObject
{
protected:
	RefCountResLoadResultNotify* mRefCountResLoadResultNotify;
	bool mIsOrigResNeedImmeUnload;        // 原始资源是否需要立刻卸载

public:
    std::string mPath;

public:
	ResInsBase();
	// warning C4265: 'ResInsBase': class has virtual functions, but destructor is not virtual instances of this class may not be destructed correctly
	virtual ~ResInsBase();
	bool getIsOrigResNeedImmeUnload();
	void setIsOrigResNeedImmeUnload(bool value);
	std::string GetPath();
	std::string getPrefabName();         // 只有 Prefab 资源才实现这个函数
	void init(ResItem* res);

protected:
    // 这个是内部初始化实现，初始化都重载这个，但是现在很多都是重载了
	virtual void initImpl(ResItem* res);

public:
	virtual void failed(ResItem* res);
	virtual void unload();
	RefCountResLoadResultNotify* getRefCountResLoadResultNotify();
	void setRefCountResLoadResultNotify(RefCountResLoadResultNotify* value);

	bool hasSuccessLoaded();
	bool hasFailed();
	virtual std::string getOrigPath();
	virtual std::string getResUniqueId();
};

#endif