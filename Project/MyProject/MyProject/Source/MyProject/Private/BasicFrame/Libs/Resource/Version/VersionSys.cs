namespace SDK.Lib
{
    /**
     * @brief 版本系统，文件格式   path=value
     */
    public class VersionSys
    {
        public ServerVer mServerVer;
        public LocalVer mLocalVer;

        public AddOnceAndCallOnceEventDispatch mMiniLoadResultDispatch;
        public AddOnceAndCallOnceEventDispatch mLoadResultDispatch;

        public bool mIsNeedUpdateApp;       // 是否需要更新 App
        public bool mIsNeedUpdateVerFile;   // 是否需要更新版本文件

        public string mMiniVer;    // mini 版本文件版本号

        public VersionSys()
        {
            this.mMiniVer = UtilEngineWrap.Range(0, int.MaxValue).ToString();
            this.mMiniLoadResultDispatch = new AddOnceAndCallOnceEventDispatch();
            this.mLoadResultDispatch = new AddOnceAndCallOnceEventDispatch();

            this.mServerVer = new ServerVer();
            this.mLocalVer = new LocalVer();
        }

        public void init()
        {
            
        }

        public void loadAllLocalVer()
        {
            this.mLocalVer.loadAllLocalVer();
        }

        public string getMajorVersion()
        {
            string ret = "";

            if(this.mServerVer.mIsMiniLoadSuccess)
            {
                ret = this.mServerVer.mMajorVersion;
            }
            else
            {
                ret = this.mLocalVer.mMajorVersion;
            }

            return ret;
        }

        public string getMinorVersion()
        {
            string ret = "";

            if (this.mServerVer.mIsMiniLoadSuccess)
            {
                ret = this.mServerVer.mMinorVersion;
            }
            else
            {
                ret = this.mLocalVer.mMinorVersion;
            }

            return ret;
        }

        public string getPatchVersion()
        {
            string ret = "";

            if (this.mServerVer.mIsMiniLoadSuccess)
            {
                ret = this.mServerVer.mPatchVersion;
            }
            else
            {
                ret = this.mLocalVer.mPatchVersion;
            }

            return ret;
        }

        public string getTimeStamp()
        {
            string ret = "";

            if (this.mServerVer.mIsMiniLoadSuccess)
            {
                ret = this.mServerVer.mTimeStamp;
            }
            else
            {
                ret = this.mLocalVer.mTimeStamp;
            }

            return ret;
        }

        public string getDetailVersionString()
        {
            string ret = "";

            if (this.mServerVer.mIsMiniLoadSuccess)
            {
                ret = this.mServerVer.getDetailVersionString();
            }
            else
            {
                ret = this.mLocalVer.getDetailVersionString();
            }

            return ret;
        }

        public string getDotVersionString()
        {
            string ret = "";

            if (this.mServerVer.mIsMiniLoadSuccess)
            {
                ret = this.mServerVer.getDotVersionString();
            }
            else
            {
                ret = this.mLocalVer.getDotVersionString();
            }

            return ret;
        }

        public string getVersionString()
        {
            string ret = "";

            if (this.mServerVer.mIsMiniLoadSuccess)
            {
                ret = this.mServerVer.getVersionString();
            }
            else
            {
                ret = this.mLocalVer.getVersionString();
            }

            return ret;
        }

        public void loadWebMiniVerFile()
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("VersionSys::loadWebMiniVerFile", LogTypeId.eLogAutoUpdate);
            }

            this.mServerVer.mMiniLoadedDispatch.addEventHandle(null, this.onWebMiniLoaded);
            this.mServerVer.loadMiniVerFile();
        }

        public void loadWebVerFile()
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("VersionSys::loadWebVerFile, start", LogTypeId.eLogAutoUpdate);
            }

            if (this.mLocalVer.mIsVerLoadSuccess)
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log("VersionSys::loadWebVerFile, mLocalVer.mIsVerLoadSuccess is true", LogTypeId.eLogAutoUpdate);
                }

                if (this.mIsNeedUpdateVerFile)
                {
                    if (MacroDef.ENABLE_LOG)
                    {
                        Ctx.msInstance.mLogSys.log("VersionSys::loadWebVerFile, mIsNeedUpdateVerFile is true", LogTypeId.eLogAutoUpdate);
                    }

                    this.mServerVer.mLoadedDispatch.addEventHandle(null, this.onWebVerLoaded);
                    this.mServerVer.loadVerFile();
                }
                else
                {
                    if (MacroDef.ENABLE_LOG)
                    {
                        Ctx.msInstance.mLogSys.log("VersionSys::loadWebVerFile, mIsNeedUpdateVerFile is false", LogTypeId.eLogAutoUpdate);
                    }

                    this.mLoadResultDispatch.dispatchEvent(null);
                }
            }
            else
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log("VersionSys::loadWebVerFile, mLocalVer.mIsVerLoadSuccess is false", LogTypeId.eLogAutoUpdate);
                }

                if (this.mIsNeedUpdateVerFile)
                {
                    if (MacroDef.ENABLE_LOG)
                    {
                        Ctx.msInstance.mLogSys.log("VersionSys::loadWebVerFile, mIsNeedUpdateVerFile is true", LogTypeId.eLogAutoUpdate);
                    }

                    this.mServerVer.mLoadedDispatch.addEventHandle(null, this.onWebVerLoaded);
                    this.mServerVer.loadVerFile();
                }
                else
                {
                    if (MacroDef.ENABLE_LOG)
                    {
                        Ctx.msInstance.mLogSys.log("VersionSys::loadWebVerFile, mIsNeedUpdateVerFile is false", LogTypeId.eLogAutoUpdate);
                    }

                    this.mLoadResultDispatch.dispatchEvent(null);
                }
            }
        }

        public void onWebMiniLoaded(IDispatchObject dispObj, uint uniqueId)
        {
            if (this.mServerVer.mIsMiniLoadSuccess)
            {
                // 删除旧 mini 版本，修改新版本文件名字
                //UtilFileIO.deleteFile(Path.Combine(MFileSys.getLocalWriteDir(), VerFileName.VER_P));
                // 修改新的版本文件名字
                //UtilFileIO.renameFile(UtilLogic.combineVerPath(Path.Combine(MFileSys.getLocalWriteDir(), VerFileName.VER_MINI), m_miniVer), Path.Combine(MFileSys.getLocalWriteDir(), VerFileName.VER_MINI));

                this.mIsNeedUpdateApp = (this.mLocalVer.mMajorVersion != this.mServerVer.mMajorVersion);      // 如果版本不一致，需要重新加载 App
                this.mIsNeedUpdateVerFile = (this.mLocalVer.mFileVerInfo.mFileMd5 != this.mServerVer.mFileVerInfo.mFileMd5);      // 如果版本不一致，需要重新加载版本文件

                //this.mIsNeedUpdateVerFile = true;         // 测试强制更新

                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log(string.Format("VersionSys::onWebMiniLoaded, loaded, mIsNeedUpdateApp = {0}, mIsNeedUpdateVerFile = {1}", this.mIsNeedUpdateApp.ToString(), this.mIsNeedUpdateVerFile.ToString()), LogTypeId.eLogAutoUpdate);
                }
            }
            else
            {
                if (MacroDef.ENABLE_LOG)
                {
                    Ctx.msInstance.mLogSys.log("VersionSys::onWebMiniLoaded, failed", LogTypeId.eLogAutoUpdate);
                }

                // 如果没有加载到服务器版本文件，就不用更新了
                this.mIsNeedUpdateApp = false;
                this.mIsNeedUpdateVerFile = false;
            }

            this.mMiniLoadResultDispatch.dispatchEvent(null);
        }

        public void onWebVerLoaded(IDispatchObject dispObj, uint uniqueId)
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("VersionSys::onWebVerLoaded", LogTypeId.eLogAutoUpdate);
            }

            this.mLoadResultDispatch.dispatchEvent(null);
        }

        public string getFileVer(string path)
        {
            if(this.mIsNeedUpdateVerFile)
            {
                if (this.mServerVer.mPath2HashDic.containsKey(path))
                {
                    return this.mServerVer.mPath2HashDic[path].mFileMd5;
                }
            }
            else
            {
                if (this.mLocalVer.mPath2Ver_P_Dic.containsKey(path))
                {
                    return this.mLocalVer.mPath2Ver_P_Dic[path].mFileMd5;
                }
            }

            return "";
        }

        // 保存 VerFileName.VER_MINI 版本文件和 VerFileName.VER_P 版本文件到 Persistent 文件夹
        public void saveWebMiniOrPVerToPersistentPath()
        {
            if (MacroDef.ENABLE_LOG)
            {
                Ctx.msInstance.mLogSys.log("VersionSys::saveWebMiniOrPVerToPersistentPath", LogTypeId.eLogAutoUpdate);
            }

            this.mServerVer.saveMiniVerToPersistentPath();

            if(this.mIsNeedUpdateVerFile)
            {
                this.mServerVer.savePVerToPersistentPath();
            }
        }

        // 如果 WebVerFile 版本文件更细了，就更新本地版本文件
        public void updateLocalVerFile()
        {
            if(null != this.mLocalVer.mPath2Ver_P_Dic)
            {
                this.mLocalVer.mPath2Ver_P_Dic.clear();
                this.mLocalVer.mABPath2Ver_P_Dic.clear();
            }

            this.mLocalVer.mPath2Ver_P_Dic = this.mServerVer.mPath2HashDic;
            this.mLocalVer.mABPath2Ver_P_Dic = this.mServerVer.mABPath2HashDic;

            this.mServerVer.mPath2HashDic = null;
            this.mServerVer.mABPath2HashDic = null;
        }
    }
}