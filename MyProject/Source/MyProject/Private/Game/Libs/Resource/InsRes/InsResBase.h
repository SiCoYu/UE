#ifndef __InsResBase_H
#define __InsResBase_H

#include "IDispatchObject.h"
#include <string>

class RefCountResLoadResultNotify;
class ResItem;

class InsResBase : public IDispatchObject
{
protected:
	RefCountResLoadResultNotify* m_refCountResLoadResultNotify;
	bool m_bOrigResNeedImmeUnload;        // 原始资源是否需要立刻卸载

public:
    std::string m_path;

public:
	InsResBase();
	bool getIsOrigResNeedImmeUnload();
	void setIsOrigResNeedImmeUnload(bool value)
    {
        m_bOrigResNeedImmeUnload = value;
    }

	std::string GetPath();
	std::string getPrefabName();         // 只有 Prefab 资源才实现这个函数
	void init(ResItem* res);

protected:
    // 这个是内部初始化实现，初始化都重载这个，但是现在很多都是重在了
	virtual void initImpl(ResItem* res);

public:
	virtual void failed(ResItem* res);
	virtual void unload();
	RefCountResLoadResultNotify* getRefCountResLoadResultNotify();
	void setRefCountResLoadResultNotify(RefCountResLoadResultNotify* value);
};

#endif