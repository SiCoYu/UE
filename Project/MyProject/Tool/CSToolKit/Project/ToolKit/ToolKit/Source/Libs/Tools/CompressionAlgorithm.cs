namespace SDK.Lib
{
    public enum CompressionAlgorithm
    {
        eNone,               // 不使用压缩
        eDEFLATE,            // 这个好像也是使用的是 ZLIB 这个压缩算法
        eZLIB,               // ZLIB 压缩算法
        eLZMA,               // 7Z 默认使用的压缩算法
        eLZ4,                // LZ4 压缩
    }
}