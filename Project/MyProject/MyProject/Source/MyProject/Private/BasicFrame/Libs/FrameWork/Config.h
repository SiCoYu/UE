#ifndef __Config_H
#define __Config_H

#include <string>
#include "MList.h"
#include "Platform.h"
#include "ResLoadType.h"
#include "ResPathType.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 宏定义说明区域
 * @def DEBUG_NOTNET 没有网络处理
 */

/**
 * @brief 基本的配置
 */
class Config : public GObject
{
public:
    static std::string StreamingAssets;
	static std::string UIModelLayer;

	std::string mIp;
    int mPort;
    uint16 mZone;

    std::string mWebIP;               // web 服务器
    int mWebPort;

	std::string mPathList[eTotal];
    ResLoadType mResLoadType;   // 资源加载类型
    std::string mDataPath;
    //public bool mIsNeedNet = false;                       // 是否需要网络
    std::string mNetLogPhp;       // Php 处理文件
	MList<std::string> mPakExtNameList;       // 打包的扩展名字列表

public:
	Config();
	~Config();

public:
	void init();
	void dispose();
};

MY_END_NAMESPACE

#endif