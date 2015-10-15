#ifndef __LoadItem_H
#define __LoadItem_H

#include "IDispatchObject.h"
#include "ResPackType.h"
#include "ResLoadType.h"
#include <string>

class NonRefCountResLoadResultNotify;

class LoadItem : public IDispatchObject
{
protected:
    ResPackType m_resPackType;
    ResLoadType m_resLoadType;   // 资源加载类型

	std::string m_path;                // 完整的目录
	std::string m_pathNoExt;           // 不包括扩展名字的路径
	std::string m_extName;             // 扩展名字

    bool m_loadNeedCoroutine;     // 加载是否需要协同程序

    NonRefCountResLoadResultNotify* m_nonRefCountResLoadResultNotify;

public:
	LoadItem();
	ResPackType getResPackType();
	void setResPackType(ResPackType value);
	std::string getPath();
	void setPath(std::string value);
	std::string getPathNoExt();
	void setPathNoExt(std::string value);
	std::string getExtName();
	void setExtName(std::string value);
	ResLoadType getResLoadType();
	void setResLoadType(ResLoadType value);
	NonRefCountResLoadResultNotify* getNonRefCountResLoadResultNotify();
	void setNonRefCountResLoadResultNotify(NonRefCountResLoadResultNotify* value);
	virtual void load();
    // 这个是卸载，因为有时候资源加载进来可能已经不用了，需要直接卸载掉
	virtual void unload();
	virtual void reset();
};

#endif