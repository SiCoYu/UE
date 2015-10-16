#ifndef __Config_H
#define __Config_H

#include <string>
#include <vector>
#include "Platform.h"
#include "ResLoadType.h"
#include "ResPathType.h"

/**
 * @brief 宏定义说明区域
 * @def DEBUG_NOTNET 没有网络处理
 */

/**
 * @brief 基本的配置
 */
class Config
{
public:
    static std::string StreamingAssets;
	static std::string UIModelLayer;

	std::string m_ip;
    int m_port;
    uint16 m_zone;

    std::string m_webIP;               // web 服务器
    int m_webPort;

	std::string m_pathLst[eTotal];
    ResLoadType m_resLoadType;   // 资源加载类型
    std::string m_dataPath;
    //public bool m_bNeedNet = false;                       // 是否需要网络
    std::string m_netLogPhp;       // Php 处理文件
	std::vector<std::string> m_pakExtNameList;       // 打包的扩展名字列表

public:
	Config();
};

#endif