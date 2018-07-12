#ifndef __ResLoadType_H
#define __ResLoadType_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 资源加载类型，主要是从哪里加载
 */
enum class ResLoadType
{
	eLoadResource,  // Resource 缺省打进程序包里的AssetBundle里加载资源
	eLoadDisc,      // 从本地磁盘加载 AssetBundle 或者 Level
	eLoadDicWeb,    // 从本地磁盘加载，但是使用 www Web 接口
	eLoadWeb,       // 从 Web 加载

	eLoadStreamingAssets,   // 从 StreamingAssets 加载
	eLoadPersistentData,
	eLoadLocalPersistentData,
	eLoadNum
};

/**
 * @brief 资源加载模式，同步还是异步
 */
enum ResLoadMode
{
	eSync,		// 同步
	eAsync,		// 异步
};

/**
 * @brief 资源加载点，构造函数，其它时机
 */
enum ResLoadPoint
{
	eConstruct,		// 同步
	eOther,		// 异步
};

MY_END_NAMESPACE

#endif