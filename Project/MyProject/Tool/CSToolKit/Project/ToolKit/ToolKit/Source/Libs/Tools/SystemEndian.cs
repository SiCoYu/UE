namespace SDK.Lib
{
    public class SystemEndian
    {
        static public MEndian msLocalEndian = MEndian.eLITTLE_ENDIAN;   // 本地字节序
        static public MEndian msNetEndian = MEndian.eBIG_ENDIAN;        // 网络字节序
        static public MEndian msServerEndian = SystemEndian.msNetEndian;// 服务器字节序，规定服务器字节序就是网络字节序
    }
}