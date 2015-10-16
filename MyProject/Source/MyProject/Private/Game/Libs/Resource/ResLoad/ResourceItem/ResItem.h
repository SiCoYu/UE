#ifndef __ResItem_H
#define __ResItem_H

#include "IDispatchObject.h"
#include "ResPackType.h"
#include "ResLoadType.h"
#include <string>

class RefCountResLoadResultNotify;
class LoadItem;

class ResItem : public IDispatchObject
{
protected :
	ResPackType m_resPackType;    // 资源打包类型
    ResLoadType m_resLoadType;    // 资源加载类型

	std::string m_path;                // 完整的目录
	std::string m_pathNoExt;           // 不包括扩展名字的路径
	std::string m_extName;             // 扩展名字

    bool m_resNeedCoroutine;     // 资源是否需要协同程序
    RefCountResLoadResultNotify* m_refCountResLoadResultNotify;

public:
	ResItem();
	ResPackType getResPackType();
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
	std::string getPath();
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
	virtual GameObject InstantiateObject(std::string resName);
	virtual UnityEngine.Object getObject(std::string resName);
	virtual byte[] getBytes(std::string resName);            // 获取字节数据
	virtual std::string getText(std::string resName);
	void copyFrom(ResItem rhv);
};

#endif