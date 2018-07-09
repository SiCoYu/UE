using System.Collections.Generic;

namespace SDK.Lib
{
    /**
     * @brief 自动更新系统
     */
    public class AutoUpdateSys
    {
        protected FileGroup mFileGroup;
        protected AddOnceAndCallOnceEventDispatch mOnUpdateEndDispatch;
        protected AutoUpdateErrorInfo mAutoUpdateErrorInfo;

        public AutoUpdateSys()
        {
            this.mFileGroup = new FileGroup();
            this.mOnUpdateEndDispatch = new AddOnceAndCallOnceEventDispatch();
            this.mAutoUpdateErrorInfo = new AutoUpdateErrorInfo();
        }

        public void init()
        {
            
        }

        public void dispose()
        {

        }

        public FileGroup getFileGroup()
        {
            return this.mFileGroup;
        }

        public AutoUpdateErrorCode getAutoUpdateErrorCode()
        {
            return this.mAutoUpdateErrorInfo.getErrorCode();
        }

        public void setAutoUpdateErrorCode(AutoUpdateErrorCode value)
        {
            this.mAutoUpdateErrorInfo.setErrorCode(value);
        }

        public AddOnceAndCallOnceEventDispatch getUpdateEndDispatch()
        {
            return this.mOnUpdateEndDispatch;
        }

        public void startUpdate()
        {
            this.loadWebMiniVersion();
        }

        // 成功更新
        public bool isUpdateSuccess()
        {
            //return this.mFileGroup.isUpdateSuccess();
            return this.mAutoUpdateErrorInfo.getErrorCode() == AutoUpdateErrorCode.eErrorNo;
        }

        // 成功更新，并且重新下载 Version_P.txt，并且成功更新需要更新的资源文件
        public bool isUpdateWebVersionPSuccessAndAllUpdateSuccess()
        {
            bool ret = false;

            if (this.isUpdateSuccess())
            {
                if (Ctx.msInstance.mVersionSys.mIsNeedUpdateVerFile &&
                   Ctx.msInstance.mVersionSys.mServerVer.mIsVerLoadSuccess)
                {
                    ret = true;
                }
            }

            return ret;
        }

        protected void checkIsNeedUpdateManifest()
        {
            string platformManifestName = UtilEngineWrap.getManifestName();
            FileVerInfo serverManifestInfo = null;
            FileVerInfo localManifestInfo = null;

            if(Ctx.msInstance.mVersionSys.mServerVer.mABPath2HashDic.containsKey(platformManifestName))
            {
                serverManifestInfo = Ctx.msInstance.mVersionSys.mServerVer.mABPath2HashDic[platformManifestName];
            }
            if(Ctx.msInstance.mVersionSys.mLocalVer.mABPath2Ver_P_Dic.containsKey(platformManifestName))
            {
                localManifestInfo = Ctx.msInstance.mVersionSys.mLocalVer.mABPath2Ver_P_Dic[platformManifestName];
            }
            else
            {
                if (Ctx.msInstance.mVersionSys.mLocalVer.mABPath2Ver_S_Dic.containsKey(platformManifestName))
                {
                    localManifestInfo = Ctx.msInstance.mVersionSys.mLocalVer.mABPath2Ver_S_Dic[platformManifestName];
                }
            }

            if(MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("AutoUpdateSys::checkIsNeedUpdateManifest, mIsNeedUpdateManifest is false", LogTypeId.eLogAutoUpdate);
            }
        }

        public void loadWebMiniVersion()
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("AutoUpdateSys::loadWebMiniVersion", LogTypeId.eLogAutoUpdate);
            }

            Ctx.msInstance.mVersionSys.mMiniLoadResultDispatch.addEventHandle(null, this.onWebMiniVerLoadResult);
            Ctx.msInstance.mVersionSys.loadWebMiniVerFile();
        }

        public void onWebMiniVerLoadResult(IDispatchObject dispObj, uint uniqueId)
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("AutoUpdateSys::onWebMiniVerLoadResult", LogTypeId.eLogAutoUpdate);
            }

            UtilMsg.sendHttpEventLog((uint)EventLogId.eEL_3);

            // 如果 Mini 文件没有从服务器下载成功
            if (!Ctx.msInstance.mVersionSys.mServerVer.mIsMiniLoadSuccess)
            {
                this.setAutoUpdateErrorCode(AutoUpdateErrorCode.eErrorDownloadWebVersionMiniFailed);
                this.downloadWebMiniFail();
            }
            else if (Ctx.msInstance.mVersionSys.mIsNeedUpdateApp) // 如果需要更新
            {
                this.downloadApp();
            }
            else if (Ctx.msInstance.mVersionSys.mIsNeedUpdateVerFile) // 如果需要更新版本文件
            {
                // 本地文件版本必须要加载
                Ctx.msInstance.mVersionSys.mLoadResultDispatch.addEventHandle(null, this.onWebVerLoadResult);
                Ctx.msInstance.mVersionSys.loadWebVerFile();
            }
            else
            {
                // 没有任何改变，直接进入游戏
                this.onUpdateEnd();          // 更新结束
            }
        }

        public void onWebVerLoadResult(IDispatchObject idspObj, uint uniqueId)
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("AutoUpdateSys::onWebVerLoadResult, start", LogTypeId.eLogAutoUpdate);
            }

            if (Ctx.msInstance.mVersionSys.mServerVer.mIsVerLoadSuccess) // 如果需要更新版本文件
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log("AutoUpdateSys::onWebVerLoadResult, mIsVerLoadSuccess is true", LogTypeId.eLogAutoUpdate);
                }

                // 开始正式加载文件
                this.loadAllUpdateFile();
            }
            else
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log("AutoUpdateSys::onWebVerLoadResult, mIsVerLoadSuccess is false", LogTypeId.eLogAutoUpdate);
                }

                this.setAutoUpdateErrorCode(AutoUpdateErrorCode.eErrorDownloadWebVersionPFailed);
                this.onUpdateEnd();          // 更新结束
            }
        }

        // 下载基本的 Web 文件失败
        protected void downloadWebMiniFail()
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("AutoUpdateSys::downloadWebMiniFail", LogTypeId.eLogAutoUpdate);
            }

            this.onUpdateEnd();
        }

        // 下载 App 文件
        protected void downloadApp()
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("AutoUpdateSys::downloadApp", LogTypeId.eLogAutoUpdate);
            }

            Ctx.msInstance.mUiMgr.loadAndShowForm(UiFormId.eUiAppDownload);
        }

        protected void loadAllUpdateFile()
        {
            this.mFileGroup.reset();
            this.mFileGroup.setTotalNum(Ctx.msInstance.mVersionSys.mServerVer.mABPath2HashDic.getData().Count - this.getExcludeUpdateFileNum());

            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log(string.Format("AutoUpdateSys::loadAllUpdateFile, Start, total = {0}", this.mFileGroup.getTotalNum()), LogTypeId.eLogAutoUpdate);
            }

            //this.checkIsNeedUpdateManifest();

            bool isFileInStreaming = false;
            bool isFileInPersistent = false;
            bool isNeedUpdateFile = false;
            FileVerInfo fileVerInfo = null;

            Dictionary<string, FileVerInfo> dic = Ctx.msInstance.mVersionSys.mServerVer.mABPath2HashDic.getData();

            foreach (KeyValuePair<string, FileVerInfo> kv in dic)
            {
                if(this.isIncludeUpdateList(kv.Key))
                {
                    isFileInStreaming = false;
                    isFileInPersistent = false;
                    fileVerInfo = null;

                    isFileInPersistent = Ctx.msInstance.mVersionSys.mLocalVer.mABPath2Ver_P_Dic.containsKey(kv.Key);

                    if (isFileInPersistent)
                    {
                        fileVerInfo = Ctx.msInstance.mVersionSys.mLocalVer.mABPath2Ver_P_Dic[kv.Key];
                    }
                    else
                    {
                        isFileInStreaming = Ctx.msInstance.mVersionSys.mLocalVer.mABPath2Ver_S_Dic.containsKey(kv.Key);

                        if (isFileInStreaming)
                        {
                            fileVerInfo = Ctx.msInstance.mVersionSys.mLocalVer.mABPath2Ver_S_Dic[kv.Key];
                        }
                    }

                    if (isFileInPersistent || isFileInStreaming)
                    {
                        isNeedUpdateFile = fileVerInfo.mFileMd5 != kv.Value.mFileMd5;
                        //isNeedUpdateFile = true;    // 强制更新

                        if (isNeedUpdateFile)
                        {
                            this.mFileGroup.addLoadingPath(kv.Key, kv.Value);
                            this.loadOneUpdateFile(kv.Key, kv.Value);
                        }
                        else
                        {
                            this.mFileGroup.addLoadedPath(kv.Key);
                            this.mFileGroup.incCurNum();
                        }
                    }
                    else
                    {
                        this.mFileGroup.addLoadingPath(kv.Key, kv.Value);
                        this.loadOneUpdateFile(kv.Key, kv.Value);
                    }
                }
            }

            this.checkUpdateEnd();

            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("AutoUpdateSys::loadAllUpdateFile, End", LogTypeId.eLogAutoUpdate);
            }
        }

        protected void loadOneUpdateFile(string path, FileVerInfo fileInfo)
        {
            //string loadPath = UtilEngineWrap.combineVerPath(path, fileInfo.m_fileMd5);
            //mLoadingPath.add(loadPath);

            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log(string.Format("AutoUpdateSys::loadOneUpdateFile, add path = {0}", path), LogTypeId.eLogAutoUpdate);
            }

            if (Ctx.msInstance.mVersionSys.mLocalVer.mPath2Ver_P_Dic.containsKey(path))
            {
                //string checkPath = Path.Combine(MFileSys.getLocalWriteDir(), UtilLogic.combineVerPath(path, Ctx.msInstance.mVersionSys.mLocalVer.mPath2Ver_P_Dic[path].mFileMd5));

                string checkPath = UtilFileIO.combine(MFileSys.getLocalWriteDir(), path);

                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("AutoUpdateSys::loadOneUpdateFile, delete path = {0}", checkPath), LogTypeId.eLogAutoUpdate);
                }

                UtilFileIO.deleteFile(checkPath);     // 删除当前目录下已经有的 old 文件
            }

            //UtilEngineWrap.delFileNoVer(path);     // 删除当前目录下已经有的 old 文件

            AuxDownloader auxDownload = new AuxDownloader();
            auxDownload.setVersion(fileInfo.mFileMd5);
            auxDownload.setIsNeedUncompress(true);
            auxDownload.download(
                path, 
                null, 
                this.onLoadEventHandle,
                null, 
                null, 
                0, 
                true, 
                (int)DownloadType.eWebRequest
                );
        }

        protected void onLoadEventHandle(IDispatchObject dispObj, uint uniqueId)
        {
            this.mFileGroup.incCurNum();

            AuxDownloader downloader = dispObj as AuxDownloader;

            if (downloader.hasSuccessLoaded())
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("AutoUpdateSys::onLoadEventHandle, success, CurIndex = {0}, path = {1}", this.mFileGroup.getCurNum(), downloader.getOrigPath()), LogTypeId.eLogAutoUpdate);
                }

                this.mFileGroup.addLoadedPath(downloader.getOrigPath());
            }
            else if (downloader.hasFailed())
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("AutoUpdateSys::onLoadEventHandle, fail, CurNum = {0}, path = {1}", this.mFileGroup.getCurNum(), downloader.getOrigPath()), LogTypeId.eLogAutoUpdate);
                }

                this.mFileGroup.addFailedPath(downloader.getOrigPath());
            }

            this.mFileGroup.removeLoadingPath(downloader.getOrigPath());
            this.checkUpdateEnd();

            downloader.dispose();
        }

        protected void checkUpdateEnd()
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log(string.Format("AutoUpdateSys::checkUpdateEnd, curNum = {0}, totalNum = {1}", this.mFileGroup.getCurNum(), this.mFileGroup.getTotalNum()), LogTypeId.eLogAutoUpdate);
            }

            if (this.mFileGroup.isCurEqTotal())
            {
                if(this.mFileGroup.hasLoadFailed())
                {
                    this.setAutoUpdateErrorCode(AutoUpdateErrorCode.eErrorDownloadWebResFailed);
                }

                this.onUpdateEnd();
            }
        }

        public void onUpdateEnd()
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("AutoUpdateSys::onUpdateEnd, end", LogTypeId.eLogAutoUpdate);
                this.mFileGroup.logDownloadDetailInfo();
            }

            // 保存信息到本地
            if (this.isUpdateWebVersionPSuccessAndAllUpdateSuccess())     // 更新文件成功，将版本文件写入本地
            {
                // 保存 VerFileName.VER_MINI 版本文件和 VerFileName.VER_P 版本文件到 Persistent 文件夹
                Ctx.msInstance.mVersionSys.saveWebMiniOrPVerToPersistentPath();
                Ctx.msInstance.mVersionSys.updateLocalVerFile();
            }

            // 清理缓存重定向信息，因为之前信息可能是更新之前的定向，更新后需要重新生成一次
            Ctx.msInstance.mResRedirect.clearCacheInfo();

            // 通知上层
            this.mOnUpdateEndDispatch.dispatchEvent(null);
        }

        // 是否在更新列表中
        protected bool isIncludeUpdateList(string path)
        {
            bool ret = true;

            // 第一次从服务器上更新的时候，本地只有 StreamingAssets 目录下的 Version_S.txt ，但是 Version_P.txt 文件已经在 ServerVer.loadVerFile 文件中加载了，因此这里就不加载了
            if (VerFileName.VER_P == path)
            {
                ret = false;
            }

            return ret;
        }

        // 获取无需从服务器更新的文件数量
        protected int getExcludeUpdateFileNum()
        {
            // VerFileName.VER_P 文件除外
            return 1;
        }
    }
}