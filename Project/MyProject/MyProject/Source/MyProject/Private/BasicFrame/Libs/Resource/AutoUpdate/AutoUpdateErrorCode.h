namespace SDK.Lib
{
    /**
     * @brief 自动更新错误代码
     */
    public enum AutoUpdateErrorCode
    {
        eErrorNo,       // 没有错误
        eErrorDownloadWebVersionMiniFailed,     // 下载 Version_Mini.txt 失败
        eErrorDownloadWebVersionPFailed,        // 下载 Version_P.txt 失败
        eErrorDownloadWebResFailed,             // 下载 资源文件失败
    }
}