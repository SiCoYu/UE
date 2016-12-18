#ifndef __ResItem_H
#define __ResItem_H

#include "IDispatchObject.h"
#include "ResPackType.h"
#include "ResLoadType.h"
#include <string>
#include "Platform.h"

class RefCountResLoadResultNotify;
class LoadItem;
class UObject;

class ResItem : public IDispatchObject
{
protected :
	ResPackType mResPackType;    // 资源打包类型
    ResLoadType mResLoadType;    // 资源加载类型

	std::string mPath;                // 完整的目录
	std::string mPathNoExt;           // 不包括扩展名字的路径
	std::string mExtName;             // 扩展名字

    bool mIsResNeedCoroutine;     // 资源是否需要协同程序
    RefCountResLoadResultNotify* mRefCountResLoadResultNotify;

public:
	ResItem();
	ResPackType getResPackType();
	void setResPackType(ResPackType value);
	std::string getPath();
	void setPath(std::string value);
	std::string getPathNoExt();
	void setPathNoExt(std::string value);
	std::string getExtName();
	void setExtName(std::string value);
	bool getResNeedCoroutine();
	void setResNeedCoroutine(bool value);
	ResLoadType getResLoadType();
	void setResLoadType(ResLoadType value);
	RefCountResLoadResultNotify* getRefCountResLoadResultNotify();
	void setRefCountResLoadResultNotify(RefCountResLoadResultNotify* value);
	virtual std::string getPrefabName();         // 只有 Prefab 资源才实现这个函数
	virtual void init(LoadItem* item);
	virtual void failed(LoadItem* item);
	virtual void reset();
    // 卸载
	virtual void unload();
	virtual UObject* InstantiateObject(std::string resName);
	virtual UObject* getObject(std::string resName);
	virtual uint8* getBytes(std::string resName);            // 获取字节数据
	virtual std::string getText(std::string resName);
	void copyFrom(ResItem* rhv);
};

#endif