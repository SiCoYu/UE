namespace SDK.Lib
{
    /**
     *@brief 资源重定向 Item
     */
    public class ResRedirectItem
    {
        public string mOrigPath;             // 资源原始目录，就是逻辑加载资源的目录
        public ResLoadType mResLoadType;        // 资源目录
        public FileVerInfo mFileVerInfo;        // 文件的基本信息

        public ResRedirectItem(string origPath = "", int redirect = (int)ResLoadType.eLoadResource)
        {
            this.mOrigPath = origPath;
            this.mResLoadType = (ResLoadType)redirect;
        }

        public bool isRedirectR()
        {
            return this.mResLoadType == ResLoadType.eLoadResource;
        }

        public bool isRedirectS()
        {
            return this.mResLoadType == ResLoadType.eLoadStreamingAssets;
        }

        public bool isRedirectP()
        {
            return this.mResLoadType == ResLoadType.eLoadLocalPersistentData;
        }

        public bool isRedirectW()
        {
            return this.mResLoadType == ResLoadType.eLoadWeb;
        }
    }
}