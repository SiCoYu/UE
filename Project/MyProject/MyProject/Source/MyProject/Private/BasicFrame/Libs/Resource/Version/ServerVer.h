#pragma once

#include <string>
#include "MDictionary.h"
#include "FileVerBase.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IDispatchObject;
class FileVerInfo;

/**
 * @brief 一个位置的所有版本 Resources \ StreamingAssets \ Application.persistentDataPath \ web 
 */
class ServerVer : public FileVerBase
{
public:
	typedef typename MDictionary<std::string, FileVerInfo*>::Iterator Path2HashDicIterator;

    // MiniVersion 必须每一次从服务器上下载
public:
	MDictionary<std::string, FileVerInfo*> mPath2HashDic;      // Resources 路径到版本信息
    MDictionary<std::string, FileVerInfo*> mABPath2HashDic;    // AB 资源包路径到版本信息

public:
	ServerVer();

	virtual void loadMiniVerFile();
	void _onMiniLoadEventHandle(IDispatchObject* dispObj, uint uniqueId);
	void loadVerFile();
    // 加载一个表完成
	void _onVerLoadEventHandle(IDispatchObject* dispObj, uint uniqueId);
	void savePVerToPersistentPath();
};

MY_END_NAMESPACE