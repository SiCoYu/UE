﻿namespace SDK.Lib
{
    /**
     * @brief 资源加载类型，主要是从哪里加载
     */
    public enum ResLoadType
    {
        eLoadResource,  // Resource 缺省打进程序包里的AssetBundle里加载资源
        eLoadDisc,      // 从本地磁盘加载 AssetBundle 或者 Level
        eLoadDicWeb,    // 从本地磁盘加载，但是使用 www Web 接口
        eLoadWeb,       // 从 Web 加载

        eStreamingAssets,   // 从 StreamingAssets 加载
        ePersistentData,
        eLoadNum
    }
}