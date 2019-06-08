namespace SDK.Lib
{
    /**
     * @brief 文件日志
     */
    public class WinLogDevice : LogDeviceBase
    {
        public override void logout(string message, LogColor type = LogColor.eLC_LOG)
        {
            if (type == LogColor.eLC_LOG)
            {
                
            }
            else if (type == LogColor.eLC_WARN)
            {
                
            }
            else if (type == LogColor.eLC_ERROR)
            {
                
            }
        }
    }
}