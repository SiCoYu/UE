namespace SDK.Lib
{
    /**
     * @brief 一个位置的所有版本 Resources \ StreamingAssets \ Application.persistentDataPath \ web 
     */
    public class ServerVer : FileVerBase
    {
        // MiniVersion 必须每一次从服务器上下载
        public MDictionary<string, FileVerInfo> mPath2HashDic;      // Resources 路径到版本信息
        public MDictionary<string, FileVerInfo> mABPath2HashDic;    // AB 资源包路径到版本信息

        public ServerVer()
        {
            this.mPath2HashDic = new MDictionary<string, FileVerInfo>();
            this.mABPath2HashDic = new MDictionary<string, FileVerInfo>();
        }

        virtual public void loadMiniVerFile()
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("ServerVer::loadMiniVerFile", LogTypeId.eLogAutoUpdate);
            }

            AuxDownloader auxDownload = new AuxDownloader();
            auxDownload.setVersion(UtilSysLibWrap.getRandomVersion());
            auxDownload.download(
                VerFileName.VER_MINI,
                null, 
                this.onMiniLoadEventHandle,
                null, 
                null, 
                0, 
                false, 
                (int)DownloadType.eWebRequest
                );
        }

        // 加载一个表完成
        protected void onMiniLoadEventHandle(IDispatchObject dispObj, uint uniqueId)
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("ServerVer::onMiniLoadEventHandle", LogTypeId.eLogAutoUpdate);
            }

            AuxDownloader downloadItem = dispObj as AuxDownloader;

            if (downloadItem.hasSuccessLoaded())
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log("ServerVer::onMiniLoadEventHandle, loaded", LogTypeId.eLogAutoUpdate);
                }

                byte[] textAsset = downloadItem.getBytes();

                if (textAsset != null)
                {
                    // Lzma 解压缩
                    //byte[] outBytes = null;
                    //uint outLen = 0;
                    //MLzma.DecompressStrLZMA(textAsset, (uint)textAsset.Length, ref outBytes, ref outLen);
                    this.parseMiniFile(System.Text.Encoding.UTF8.GetString(textAsset));
                }

                this.mIsMiniLoadSuccess = true;
            }
            else if (downloadItem.hasFailed())
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log("ServerVer::onMiniLoadEventHandle, error", LogTypeId.eLogAutoUpdate);
                }

                this.mIsMiniLoadSuccess = false;
            }

            downloadItem.dispose();

            this.mMiniLoadedDispatch.dispatchEvent(null);
        }

        // 加载版本文件
        public void loadVerFile()
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("ServerVer::loadVerFile", LogTypeId.eLogAutoUpdate);
            }

            AuxDownloader auxDownload = new AuxDownloader();
            auxDownload.setVersion(UtilSysLibWrap.getRandomVersion());
            auxDownload.download(
                VerFileName.VER_P,
                null,
                this.onVerLoadEventHandle, 
                null,
                null,
                0, 
                false, 
                (int)DownloadType.eWebRequest
                );
        }

        // 加载一个表完成
        protected void onVerLoadEventHandle(IDispatchObject dispObj, uint uniqueId)
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("ServerVer::onVerLoadEventHandle", LogTypeId.eLogAutoUpdate);
            }

            AuxDownloader downloadItem = dispObj as AuxDownloader;

            if (downloadItem.hasSuccessLoaded())
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("ServerVer::onVerLoadEventHandle, loaded, origPath = {0}", downloadItem.getOrigPath()), LogTypeId.eLogAutoUpdate);
                }

                byte[] textAsset = downloadItem.getBytes();

                if (textAsset != null)
                {
                    this.loadFormText(System.Text.Encoding.UTF8.GetString(textAsset), this.mPath2HashDic, this.mABPath2HashDic);
                }

                this.mIsVerLoadSuccess = true;
            }
            else if (downloadItem.hasFailed())
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("ServerVer::onVerLoadEventHandle, failed, origPath = {0}", downloadItem.getOrigPath()), LogTypeId.eLogAutoUpdate);
                }

                this.mIsVerLoadSuccess = false;
            }

            this.mLoadedDispatch.dispatchEvent(null);
        }

        public void savePVerToPersistentPath()
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("ServerVer::savePVerToPersistentPath, start", LogTypeId.eLogAutoUpdate);
            }

            string path = UtilFileIO.combine(MFileSys.msPersistentDataPath, VerFileName.VER_P);

            if (UtilFileIO.existFile(path))
            {
                UtilFileIO.deleteFile(path);
            }

            MDataStream dataStream = new MDataStream(path, null, MFileMode.eCreateNew, MFileAccess.eWrite);
            dataStream.open();

            string line = "";
            FileVerInfo fileVerInfo = null;

            foreach (System.Collections.Generic.KeyValuePair<string, FileVerInfo> kv in this.mPath2HashDic.getData())
            {
                fileVerInfo = kv.Value;

                line = string.Format("{0}={1}={2}={3}={4}", fileVerInfo.mOrigPath, fileVerInfo.mResUniqueId, fileVerInfo.mLoadPath, fileVerInfo.mFileMd5, fileVerInfo.mFileSize);
                dataStream.writeLine(line);
            }

            dataStream.dispose();
            dataStream = null;
        }
    }
}