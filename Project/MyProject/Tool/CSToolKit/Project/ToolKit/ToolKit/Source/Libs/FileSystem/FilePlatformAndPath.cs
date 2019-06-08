namespace SDK.Lib
{
    public enum FilePlatformAndPath
    {
        eResourcesPath = 0,                 // Resources 文件夹下的文件操作
        eAndroidStreamingAssetsPath = 1,    // Android 平台下 StreamingAssetsPath 目录下，只有 Android 的 StreamingAssets 这个目录必须需要 WWW 才能读取，其它的平台所有的目录都可以使用 File 系统读取操作
        eOther,                             // 其它
    }
}