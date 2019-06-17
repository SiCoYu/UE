#ifndef __LoadItem_H
#define __LoadItem_H

#include "IDispatchObject.h"
#include "ResPackType.h"
#include "ResLoadType.h"
#include <string>
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class NonRefCountResLoadResultNotify;
class LoadParam;

class LoadItem : public GObject/*, public IDispatchObject*/
{
	M_DECLARE_CLASS(LoadItem, GObject)

protected:
    ResPackType mResPackType;
    ResLoadType mResLoadType;   // 资源加载类型

	std::string mPath;                // 完整的目录
	std::string mPathNoExt;           // 不包括扩展名字的路径
	std::string mExtName;             // 扩展名字

    bool mIsLoadNeedCoroutine;     // 加载是否需要协同程序

    NonRefCountResLoadResultNotify* mNonRefCountResLoadResultNotify;

public:
	LoadItem();
	virtual ~LoadItem();

	virtual void init();
	virtual void dispose();

	ResPackType getResPackType();
	void setResPackType(ResPackType value);

	std::string getPath();
	void setPath(std::string value);

	std::string getPathNoExt();
	void setPathNoExt(std::string value);

	std::string getExtName();
	void setExtName(std::string value);

	bool getLoadNeedCoroutine();
	void setLoadNeedCoroutine(bool value);

	ResLoadType getResLoadType();
	void setResLoadType(ResLoadType value);

	NonRefCountResLoadResultNotify* getNonRefCountResLoadResultNotify();
	void setNonRefCountResLoadResultNotify(NonRefCountResLoadResultNotify* value);

	virtual UObject* getObject();
	virtual void setObject(UObject* value);

	virtual void load();
    // 这个是卸载，因为有时候资源加载进来可能已经不用了，需要直接卸载掉
	virtual void unload();
	virtual void reset();

	void setLoadParam(LoadParam* param);
};

MY_END_NAMESPACE

#endif