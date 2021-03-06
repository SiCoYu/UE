﻿#ifndef __ResItem_H
#define __ResItem_H

#include "IDispatchObject.h"
#include "ResPackType.h"
#include "ResLoadType.h"
#include <string>
#include "Platform.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "GObject.h"
#include "PlatformDefine.h"

class UObject;

MY_BEGIN_NAMESPACE(MyNS)

class RefCountResLoadResultNotify;
class LoadItem;
class LoadParam;

class ResItem : public GObject/*, public IDispatchObject*/
{
	M_DECLARE_CLASS(ResItem, GObject)

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
	virtual ~ResItem();

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
	virtual void initWithLoad(LoadItem* item);
	virtual void failed(LoadItem* item);
	virtual void reset();
    // 卸载
	virtual void unload();

	virtual void init() override;
	virtual void dispose();

	virtual UObject* InstantiateObject(std::string resName);
	virtual UObject* getObject(std::string resName);
	virtual uint8* getBytes(std::string resName);            // 获取字节数据
	virtual std::string getText(std::string resName);
	void copyFrom(ResItem* rhv);

	bool hasSuccessLoaded();
	bool hasFailed();

	virtual std::string getResUniqueId();
	void setLoadParam(LoadParam* param);
};

MY_END_NAMESPACE

#endif