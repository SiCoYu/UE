using SDK.Lib;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace ToolSet
{
    /**
     * @brief 打包策略，都是针对文件夹的，每一个顶层文件夹以及子文件夹只能用同种打包策略
     */
    public enum AssetBundleBuildPolicy
    {
        eFolder,        // 文件夹策略,文件夹内部打包成一个
        eSingleFile,    // 文件夹中每个文件打包一个
        eSingleDependency,  // 文件夹中，单引用依赖打包成一个包，多引用打包成一个包
    }

    public class AssetItemV2
    {
        public bool IsAddedAssetBundleBuild = false;
        public bool IsCollectedDependency = false;
        public bool IsIncludeAssetBundleItem = true;   // 是否是需要包含在输入列表的资源

		public string AssetAbsolutePath;
		public string AssetLongPackageName;
        public List<AssetItemV2> ChildDependencyList;
        public Dictionary<string, AssetItemV2> AssetPath2ChildAssetDic;
        public List<AssetItemV2> ParentReferenceList;
        public Dictionary<string, AssetItemV2> AssetPath2ParentAssetDic;

        protected Dictionary<int, System.Object> _UserDataDic;

        public AssetItemV2()
        {
            this.IsAddedAssetBundleBuild = false;
            this.IsCollectedDependency = false;
            this.ChildDependencyList = new List<AssetItemV2>();
            this.AssetPath2ChildAssetDic = new Dictionary<string, AssetItemV2>();
            this.ParentReferenceList = new List<AssetItemV2>();
            this.AssetPath2ParentAssetDic = new Dictionary<string, AssetItemV2>();
        }

        public void Init()
        {

        }

        public void Dispose()
        {
            this.ChildDependencyList.Clear();
            this.AssetPath2ChildAssetDic.Clear();
            this.ParentReferenceList.Clear();
            this.AssetPath2ParentAssetDic.Clear();

            if (null != this._UserDataDic)
            {
                this._UserDataDic.Clear();
                this._UserDataDic = null;
            }
        }

        public void AddUserData(int key, System.Object value)
        {
            if (null == this._UserDataDic)
            {
                this._UserDataDic = new Dictionary<int, object>();
            }

            this._UserDataDic.Add(key, value);
        }

        public System.Object GetUserData(int key)
        {
            if (null != this._UserDataDic && this._UserDataDic.ContainsKey(key))
            {
                return this._UserDataDic[key];
            }

            return null;
        }

        public int GetChildDepencencyNum()
        {
            return this.ChildDependencyList.Count;
        }

        public int GetParentReferenceNum()
        {
            return this.ParentReferenceList.Count;
        }

        public void AddChild(AssetItemV2 childAssetItem)
        {
            if (!this.AssetPath2ChildAssetDic.ContainsKey(childAssetItem.AssetLongPackageName))
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("AddChild, Parent {0} , Child {1}", this.AssetLongPackageName, childAssetItem.AssetLongPackageName));
                }

                this.ChildDependencyList.Add(childAssetItem);
                this.AssetPath2ChildAssetDic.Add(childAssetItem.AssetLongPackageName, childAssetItem);
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("AddChild, {0} already exist", childAssetItem.AssetLongPackageName));
                }
            }
        }

        public void AddParent(AssetItemV2 parentAssetItem)
        {
            if (!this.AssetPath2ParentAssetDic.ContainsKey(parentAssetItem.AssetLongPackageName))
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("AddParent, Parent {0} , Child {1}", parentAssetItem.AssetLongPackageName, this.AssetLongPackageName));
                }

                this.ParentReferenceList.Add(parentAssetItem);
                this.AssetPath2ParentAssetDic.Add(parentAssetItem.AssetLongPackageName, parentAssetItem);
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("AddParent, {0} already exist", parentAssetItem.AssetLongPackageName));
                }
            }
        }
    }

    public class AssetBundleItemV2
    {
        // 没有扩展名字，从 AssetBundleBuilderV2.ASB_RES_PATH_SLASH 后开始的
        protected string _AssetBundleShortName;
        // 扩展名字 unity3d，从 AssetBundleBuilderV2.ASB_RES_PATH_SLASH 后开始的小写
        protected string _AssetBundleName;
        public List<AssetItemV2> AssetItemList;

        public AssetBundleItemV2()
        {
            this.AssetItemList = new List<AssetItemV2>();
        }

        public void InitAssetBundleName(AssetPackageGraph assetContext)
        {
            UtilDebug.Assert(this.AssetItemList.Count > 0, "InitAssetBundleName error");

            string origPath = this.AssetItemList[0].AssetLongPackageName;
            origPath = assetContext.GetAndCheckAssetBundleFileNameLength(origPath);

            this._AssetBundleName = AssetPackageUtil.ChangeExtNameDotToUnderlineAndAddAssetBundleExt(origPath);

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("InitAssetBundleName, AssetBundleName is {0}", this._AssetBundleName));
            }
        }

        public int GetAssetCount()
        {
            return this.AssetItemList.Count;
        }

        public string GetAsbShortName()
        {
            return this._AssetBundleShortName;
        }

        public void SetAsbShortName(string name)
        {
            this._AssetBundleShortName = name;
        }

        public string GetAssetBundlePath()
        {
            return this._AssetBundleName;
        }

        public List<string> GetAssetNameList()
        {
            List<string> nameList = new List<string>();

            for (int index = 0; index < this.AssetItemList.Count; ++index)
            {
                nameList.Add(this.AssetItemList[index].AssetLongPackageName);
            }

            return nameList;
        }

        public void SetAssetNameList(String[] nameList)
        {
            AssetItemV2 assetItem = null;

            for (int index = 0; index < nameList.Length; ++index)
            {
                assetItem = new AssetItemV2();
                this.AssetItemList.Add(assetItem);
                assetItem.AssetLongPackageName = nameList[index];
            }
        }

        public string ToConfigString()
        {
            List<string> assetPathList = this.GetAssetNameList();

            return string.Join(",", new string[]
            {
                this.GetAsbShortName(),
                assetPathList.Count > 0 ? string.Join(";", assetPathList.ToArray()) : ""
            });
        }
    }

	public class AssetBundleBuild
	{
		public string assetBundleName;
		public string[] assetNames;
	}

	public class AssetPackageGraph
	{
		protected AssetRegister mAssetRegister;
		// 收集目录，用来建立引用关系，这个目录尽量包含所有的资源，否则很有可能引用关系建立不全
		protected List<string> _CollectRootPathList;
        // 这个建立 AssetBundle 目录，不包含文件，一般是 _CollectRootPathList 的子目录或者就是 _CollectRootPathList
        protected List<string> _IncludeAssetBundlePathList;
        // 不包含在 AssetBundle 中目录列表
        protected List<string> _ExcludeAssetBundlePathList;
        // 不包含在 AssetBundle 中文件列表
        protected List<string> _ExcludeAssetBundleFileList;
        // 不包含在 AssetBundle 中文件扩展名列表
        protected List<string> _ExcludeAssetBundleFileExtNameList;

        protected List<AssetItemV2> _CollectAllAssetItemList;
        protected List<AssetItemV2> _CollectIncludeAssetItemList;
        protected List<AssetItemV2> _CollectExcludeAssetItemList;
        protected Dictionary<string, AssetItemV2> _CollectAssetPath2AssetDic;
        protected List<AssetBundleItemV2> _AssetBundleItemList;
        protected List<AssetBundleBuild> _AssetBundleBuildList;
        protected string _FileNamePostFix;

        protected Dictionary<string, string> _RecordAllFile2OrigPathDic;
        protected Dictionary<string, string> _Changed2OrigPathDic;

        public AssetPackageGraph()
        {
			this.mAssetRegister = new AssetRegister();

			this._CollectRootPathList = new List<string>();
            this._IncludeAssetBundlePathList = new List<string>();
            this._ExcludeAssetBundlePathList = new List<string>(); 
            this._ExcludeAssetBundleFileList = new List<string>();
            this._ExcludeAssetBundleFileExtNameList = new List<string>();

            this._CollectAllAssetItemList = new List<AssetItemV2>();
            this._CollectIncludeAssetItemList = new List<AssetItemV2>();
            this._CollectExcludeAssetItemList = new List<AssetItemV2>();

            this._CollectAssetPath2AssetDic = new Dictionary<string, AssetItemV2>();
            this._AssetBundleItemList = new List<AssetBundleItemV2>();
            this._AssetBundleBuildList = new List<AssetBundleBuild>();
            this._FileNamePostFix = "";

            this._RecordAllFile2OrigPathDic = new Dictionary<string, string>();
            this._Changed2OrigPathDic = new Dictionary<string, string>();
        }

        public void Init()
        {
			this.mAssetRegister.init();
			this._CheckIncludeAndExcludePath();
        }

        public void Dispose()
        {
            for (int index = 0; index < this._CollectAllAssetItemList.Count; ++index)
            {
                this._CollectAllAssetItemList[index].Dispose();
            }

            this._CollectRootPathList.Clear();

            this._IncludeAssetBundlePathList.Clear();
            this._ExcludeAssetBundlePathList.Clear();
            this._ExcludeAssetBundleFileList.Clear();
            this._ExcludeAssetBundleFileExtNameList.Clear();

            this._CollectAllAssetItemList.Clear();
            this._CollectIncludeAssetItemList.Clear();
            this._CollectExcludeAssetItemList.Clear();
            this._CollectAssetPath2AssetDic.Clear();
            this._AssetBundleItemList.Clear();
            this._AssetBundleBuildList.Clear();

            this._RecordAllFile2OrigPathDic.Clear();
            this._Changed2OrigPathDic.Clear();

			this.mAssetRegister.dispose();
		}

        public void SetFileNamePostFix(string value)
        {
            this._FileNamePostFix = value;
        }

        public List<AssetItemV2> GetAllAssetItemList()
        {
            return this._CollectAllAssetItemList;
        }

        public List<AssetItemV2> GetIncludeAssetItemList()
        {
            return this._CollectIncludeAssetItemList;
        }

        public List<AssetItemV2> GetExcludeAssetItemList()
        {
            return this._CollectExcludeAssetItemList;
        }

        public Dictionary<string, AssetItemV2> GetAssetPath2AssetDic()
        {
            return this._CollectAssetPath2AssetDic;
        }

        public List<AssetBundleItemV2> GetAssetBundleItemList()
        {
            return this._AssetBundleItemList;
        }

        public void AddCollectRootPath(string absolutePathWithContent)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("AddRootPath, {0}", absolutePathWithContent));
            }
            UtilDebug.Assert(!string.IsNullOrEmpty(absolutePathWithContent), "path is null");
            UtilDebug.Assert(-1 != absolutePathWithContent.IndexOf(UtilUE4EngineWrap.DEFAULT_PHYSICS_FOLDER), "path is not include content");

            this._CollectRootPathList.Add(absolutePathWithContent);
        }

        public void AddIncludeAssetBundlePath(string relativePathStartWithAsset)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("AddIncludeAssetBundlePath, {0}", relativePathStartWithAsset));
            }

            UtilDebug.Assert(!string.IsNullOrEmpty(relativePathStartWithAsset), "path is null");
            UtilDebug.Assert(0 == relativePathStartWithAsset.IndexOf("Assets/"), "path is not start with Asset");

            for (int index = 0; index < this._ExcludeAssetBundlePathList.Count; ++index)
            {
                UtilDebug.Assert(relativePathStartWithAsset != this._ExcludeAssetBundlePathList[index], "relativePathStartWithAsset already in _ExcludeAssetBundlePathList");
            }


            if (!this._IncludeAssetBundlePathList.Contains(relativePathStartWithAsset))
            {
                this._IncludeAssetBundlePathList.Add(relativePathStartWithAsset);
            }
            else
            {
                UtilDebug.Log(string.Format("AddIncludeAssetBundlePath, {0} is already in", relativePathStartWithAsset));
            }
        }

        public void AddExcludeAssetBundlePath(string relativePathStartWithAsset)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("AddExcludeAssetBundlePath, {0}", relativePathStartWithAsset));
            }

            UtilDebug.Assert(!string.IsNullOrEmpty(relativePathStartWithAsset), "path is null");
            UtilDebug.Assert(0 == relativePathStartWithAsset.IndexOf("Assets/"), "path is not start with Asset");

            for (int index = 0; index < this._IncludeAssetBundlePathList.Count; ++index)
            {
                UtilDebug.Assert(relativePathStartWithAsset != this._IncludeAssetBundlePathList[index], "relativePathStartWithAsset already in _IncludeAssetBundlePathList");
            }

            if (!this._ExcludeAssetBundlePathList.Contains(relativePathStartWithAsset))
            {
                this._ExcludeAssetBundlePathList.Add(relativePathStartWithAsset);
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("AddExcludeAssetBundlePath, {0} is already in", relativePathStartWithAsset));
                }
            }
        }

        public void AddExcludeAssetBundleFile(string relativePathStartWithAsset)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("AddExcludeAssetBundleFile, {0}", relativePathStartWithAsset));
            }

            UtilDebug.Assert(!string.IsNullOrEmpty(relativePathStartWithAsset), "path is null");
            UtilDebug.Assert(0 == relativePathStartWithAsset.IndexOf("Assets/"), "path is not start with Asset");

            for (int index = 0; index < this._IncludeAssetBundlePathList.Count; ++index)
            {
                UtilDebug.Assert(relativePathStartWithAsset != this._IncludeAssetBundlePathList[index], "relativePathStartWithAsset already in _IncludeAssetBundlePathList");
            }

            if (!this._ExcludeAssetBundleFileList.Contains(relativePathStartWithAsset))
            {
                this._ExcludeAssetBundleFileList.Add(relativePathStartWithAsset);
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("AddExcludeAssetBundleFile, {0} is already in", relativePathStartWithAsset));
                }
            }
        }

        public void AddExcludeAssetBundleFileExtName(string extName)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("AddExcludeAssetBundleFileExtName, {0}", extName));
            }

            UtilDebug.Assert(!string.IsNullOrEmpty(extName), "extName is null");

            if (!this._ExcludeAssetBundleFileExtNameList.Contains(extName))
            {
                this._ExcludeAssetBundleFileExtNameList.Add(extName);
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("extName, {0} is already in", extName));
                }
            }
        }

        protected void _CheckIncludeAndExcludePath()
        {
            
        }

        protected void _AddAssetItem(AssetItemV2 assetItem)
        {
            if (!this._CollectAssetPath2AssetDic.ContainsKey(assetItem.AssetLongPackageName))
            {
                this._CollectAssetPath2AssetDic.Add(assetItem.AssetLongPackageName, assetItem);
                this._CollectAllAssetItemList.Add(assetItem);

                if (assetItem.IsIncludeAssetBundleItem)
                {
                    this._CollectIncludeAssetItemList.Add(assetItem);
                }
                else
                {
                    this._CollectExcludeAssetItemList.Add(assetItem);
                }
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("AddAssetItem, {0} is already", assetItem.AssetLongPackageName));
                }
            }
        }

        public List<AssetBundleBuild> GetAssetBundleBuildList()
        {
            return this._AssetBundleBuildList;
        }

        protected bool _IsCircularDependency(AssetItemV2 assetItem, Stack<AssetItemV2> stack)
        {
            bool ret = false;

            ret = stack.Contains(assetItem);

            return ret;
        }

        protected void _CheckAssetUniqueInAssetBundleItem()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_CheckAssetUniqueInAssetBundleItem, start"));
            }

            Dictionary<string, bool> path2FlagDic = new Dictionary<string, bool>();
            AssetBundleItemV2 assetBundleItem = null;
            AssetItemV2 assetItem = null;

            for (int indexX = 0; indexX < this._AssetBundleItemList.Count; ++indexX)
            {
                assetBundleItem = this._AssetBundleItemList[indexX];

                for (int indexY = 0; indexY < assetBundleItem.AssetItemList.Count; ++indexY)
                {
                    assetItem = assetBundleItem.AssetItemList[indexY];

                    if (!path2FlagDic.ContainsKey(assetItem.AssetLongPackageName))
                    {
                        path2FlagDic.Add(assetItem.AssetLongPackageName, true);
                    }
                    else
                    {
                        if (AssetPackageUtil.ENABLE_ERROR_LOG)
                        {
                            UtilDebug.LogError(string.Format("_CheckAssetUniqueInAssetBundleItem, diff {0} error", assetItem.AssetLongPackageName));
                        }
                    }
                }
            }

            if (path2FlagDic.Count != this._CollectIncludeAssetItemList.Count)
            {
                if (AssetPackageUtil.ENABLE_ERROR_LOG)
                {
                    UtilDebug.LogError(string.Format("_CheckAssetUniqueInAssetBundleItem, num error, {0} != {1}", path2FlagDic.Count, this._CollectIncludeAssetItemList.Count));

                    bool isFind = false;
                    foreach (KeyValuePair<string, bool> kvData in path2FlagDic)
                    {
                        isFind = false;

                        for (int index = 0; index < this._CollectIncludeAssetItemList.Count; ++index)
                        {
                            if (kvData.Key == this._CollectIncludeAssetItemList[index].AssetLongPackageName)
                            {
                                isFind = true;
                                break;
                            }
                        }

                        if(!isFind)
                        {
                            UtilDebug.LogError(string.Format("_CheckAssetUniqueInAssetBundleItem, kvData error, {0} not find", kvData.Key));
                        }
                    }

                    for (int index = 0; index < this._CollectIncludeAssetItemList.Count; ++index)
                    {
                        isFind = false;

                        foreach (KeyValuePair<string, bool> kvData in path2FlagDic)
                        {
                            if (kvData.Key == this._CollectIncludeAssetItemList[index].AssetLongPackageName)
                            {
                                isFind = true;
                                break;
                            }
                        }

                        if (!isFind)
                        {
                            UtilDebug.LogError(string.Format("_CheckAssetUniqueInAssetBundleItem, List error, {0} not find", this._CollectIncludeAssetItemList[index].AssetLongPackageName));
                        }
                    }
                }
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_CheckAssetUniqueInAssetBundleItem, end"));
            }
        }

        // 检查资源正确性
        protected void _CheckAssetCorrect()
        {
            this._CheckAssetUniqueInAssetBundleItem();
        }

        protected bool _IsIncludeAssetBundleItemList(AssetItemV2 assetItem)
        {
            bool ret = true;
            string maxDepthIncludePath = "";
            string maxDepthExcludePath = "";

            ret = !_ExcludeAssetBundleFileList.Contains(assetItem.AssetLongPackageName);

            if (ret)
            {
                for (int index = 0; index < this._IncludeAssetBundlePathList.Count; ++index)
                {
                    if (0 == assetItem.AssetLongPackageName.IndexOf(this._IncludeAssetBundlePathList[index]))
                    {
                        if (maxDepthIncludePath.Length < this._IncludeAssetBundlePathList[index].Length)
                        {
                            maxDepthIncludePath = this._IncludeAssetBundlePathList[index];
                        }
                    }
                }

                if (!string.IsNullOrEmpty(maxDepthIncludePath))
                {
                    for (int index = 0; index < this._ExcludeAssetBundlePathList.Count; ++index)
                    {
                        if (0 == assetItem.AssetLongPackageName.IndexOf(this._ExcludeAssetBundlePathList[index]))
                        {
                            if (maxDepthExcludePath.Length < this._ExcludeAssetBundlePathList[index].Length)
                            {
                                maxDepthExcludePath = this._ExcludeAssetBundlePathList[index];
                            }
                        }
                    }

                    if (!string.IsNullOrEmpty(maxDepthExcludePath))
                    {
                        if (maxDepthIncludePath.Length > maxDepthExcludePath.Length)
                        {
                            ret = true;
                        }
                        else
                        {
                            ret = false;
                        }
                    }
                    else
                    {
                        ret = true;
                    }
                }
                else
                {
                    ret = false;
                }
            }

            return ret;
        }

        // Android 平台文件名字 100 个字符限制，不包含文件路径
        public string GetAndCheckAssetBundleFileNameLength(string origPath)
        {
            string filePathNoFileName = AssetPackageUtil.GetFilePathNoFileName(origPath);
            string fileNameNoExtName = AssetPackageUtil.GetFileNameNoPathAndExt(origPath);
            string fileExtName = AssetPackageUtil.GetFileExtName(origPath);
            int assetBundleFileNameLen = AssetPackageUtil.GetAssetBundleFileNameLength(fileNameNoExtName, fileExtName);

            string changedFileName = origPath;
            int findIndex = 0;
            bool isValidChangedPath = false;

            if (assetBundleFileNameLen > 100)
            {
                int needRemoveCount = assetBundleFileNameLen - 98;  // 预留两位添加
                if (fileNameNoExtName.Length > needRemoveCount)
                {
                    fileNameNoExtName = fileNameNoExtName.Substring(needRemoveCount);
                }
                else
                {
                    UtilDebug.LogError(string.Format("{0} filenamenoext too short", origPath));
                }

                for (findIndex = 0; findIndex < 100; ++findIndex)
                {
                    if (0 == findIndex)
                    {
                        changedFileName = AssetPackageUtil.GetFullPathFromSeparate(filePathNoFileName, fileNameNoExtName, fileExtName);
                    }
                    else
                    {
                        changedFileName = AssetPackageUtil.GetFullPathFromSeparate(filePathNoFileName, string.Format("{0}{1}", findIndex - 1, fileNameNoExtName), fileExtName);
                    }

                    if (!this._Changed2OrigPathDic.ContainsKey(changedFileName))
                    {
                        isValidChangedPath = true;
                        this._Changed2OrigPathDic.Add(changedFileName, origPath);

                        if (!this._RecordAllFile2OrigPathDic.ContainsKey(changedFileName))
                        {
                            this._RecordAllFile2OrigPathDic.Add(changedFileName, origPath);
                        }
                        else
                        {
                            UtilDebug.Log(string.Format("{0} is already exist", changedFileName));
                            throw new Exception(string.Format("{0} is already exist", changedFileName));
                        }

                        break;
                    }
                }
            }
            else
            {
                isValidChangedPath = true;

                if (!this._RecordAllFile2OrigPathDic.ContainsKey(changedFileName))
                {
                    this._RecordAllFile2OrigPathDic.Add(changedFileName, origPath);
                }
                else
                {
                    UtilDebug.LogError(string.Format("{0} is already exist", changedFileName));
                    throw new Exception(string.Format("{0} is already exist", changedFileName));
                }
            }

            if (!isValidChangedPath)
            {
                UtilDebug.LogError(string.Format("{0} is not valid", changedFileName));
                throw new Exception(string.Format("{0} is already exist", changedFileName));
            }

            return changedFileName;
        }

        protected void _WriteAssetBundleChangedFilePathManifest(string fileName)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteAssetBundleChangedFilePathManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetPackageUtil.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "ChangedFilePathManifest");
            }
            if (File.Exists(fileName))
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("{0} exist, delete", fileName));
                }

                try
                {
                    File.Delete(fileName);
                }
                catch (Exception exp)
                {
                    if (AssetPackageUtil.ENABLE_ERROR_LOG)
                    {
                        UtilDebug.LogError(string.Format("{0} delete, error {1}", fileName, exp.Message));
                    }
                }
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("{0} not exist", fileName));
                }
            }

            FileStream fileStream = null;

            try
            {
                fileStream = new FileStream(fileName, FileMode.CreateNew, FileAccess.Write);

                byte[] byteArray = null;

                byteArray = Encoding.UTF8.GetBytes(string.Format("Total Count is {0}\n\n", this._Changed2OrigPathDic.Count));
                fileStream.Write(byteArray, 0, byteArray.Length);

                int indexX = 0;
                foreach (KeyValuePair<string, string> kvData in this._Changed2OrigPathDic)
                {
                    byteArray = Encoding.UTF8.GetBytes(string.Format("Orig {0}, changed {1}\n", kvData.Value, kvData.Key));
                    fileStream.Write(byteArray, 0, byteArray.Length);

                    byteArray = Encoding.UTF8.GetBytes(string.Format("\n"));
                    fileStream.Write(byteArray, 0, byteArray.Length);

                    ++indexX;
                }

                fileStream.Close();
                fileStream.Dispose();
                fileStream = null;
            }
            catch (Exception exp)
            {
                UtilDebug.Log(string.Format("error {0}", exp.Message));

                if (null != fileStream)
                {
                    fileStream.Close();
                    fileStream.Dispose();
                    fileStream = null;
                }
            }
            finally
            {
                if (null != fileStream)
                {
                    fileStream.Close();
                    fileStream.Dispose();
                    fileStream = null;
                }
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteAssetBundleChangedFilePathManifest, end"));
            }
        }

        protected void _WriteAssetBundleManifest(string fileName)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteAssetBundleManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetPackageUtil.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "AssetBundleManifest");
            }
            if (File.Exists(fileName))
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("{0} exist, delete", fileName));
                }

                try
                {
                    File.Delete(fileName);
                }
                catch(Exception exp)
                {
                    if (AssetPackageUtil.ENABLE_ERROR_LOG)
                    {
                        UtilDebug.LogError(string.Format("{0} delete, error {1}", fileName, exp.Message));
                    }
                }
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("{0} not exist", fileName));
                }
            }

            FileStream fileStream = null;

            try
            {
                fileStream = new FileStream(fileName, FileMode.CreateNew, FileAccess.Write);

                AssetBundleItemV2 assetBundleItem = null;
                AssetItemV2 assetItem = null;
                byte[] byteArray = null;

                byteArray = Encoding.UTF8.GetBytes(string.Format("Total AssetBundle Count is {0}\n\n", this._AssetBundleItemList.Count));
                fileStream.Write(byteArray, 0, byteArray.Length);

                for (int indexX = 0; indexX < this._AssetBundleItemList.Count; ++indexX)
                {
                    assetBundleItem = this._AssetBundleItemList[indexX];
                    byteArray = Encoding.UTF8.GetBytes(string.Format("AssetBundleName: {0}, num = {1}\n", assetBundleItem.GetAssetBundlePath(), assetBundleItem.AssetItemList.Count));
                    fileStream.Write(byteArray, 0, byteArray.Length);

                    for (int indexY = 0; indexY < assetBundleItem.AssetItemList.Count; ++indexY)
                    {
                        assetItem = assetBundleItem.AssetItemList[indexY];
                        byteArray = Encoding.UTF8.GetBytes(string.Format("{0}\n", assetItem.AssetLongPackageName));
                        fileStream.Write(byteArray, 0, byteArray.Length);
                    }

                    byteArray = Encoding.UTF8.GetBytes(string.Format("\n"));
                    fileStream.Write(byteArray, 0, byteArray.Length);
                }

                fileStream.Close();
                fileStream.Dispose();
                fileStream = null;
            }
            catch(Exception exp)
            {
                UtilDebug.Log(string.Format("error {0}", exp.Message));

                if (null != fileStream)
                {
                    fileStream.Close();
                    fileStream.Dispose();
                    fileStream = null;
                }
            }
            finally
            {
                if (null != fileStream)
                {
                    fileStream.Close();
                    fileStream.Dispose();
                    fileStream = null;
                }
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteAssetBundleManifest, end"));
            }
        }

        protected void _WriteAllCollectAssetDependencyManifest(string fileName)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteAllCollectAssetDependencyManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetPackageUtil.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "AllCollectAssetDependencyManifest");
            }
            if (File.Exists(fileName))
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("{0} exist, delete", fileName));
                }

                try
                {
                    File.Delete(fileName);
                }
                catch (Exception exp)
                {
                    if (AssetPackageUtil.ENABLE_ERROR_LOG)
                    {
                        UtilDebug.LogError(string.Format("{0} delete, error {1}", fileName, exp.Message));
                    }
                }
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("{0} not exist", fileName));
                }
            }

            FileStream fileStream = null;

            try
            {
                fileStream = new FileStream(fileName, FileMode.CreateNew, FileAccess.Write);

                AssetItemV2 assetItem = null;
                AssetItemV2 dependencyAssetItem = null;
                byte[] byteArray = null;

                byteArray = Encoding.UTF8.GetBytes(string.Format("Total _CollectAssetItem Count is {0}\n\n", this._CollectAllAssetItemList.Count));
                fileStream.Write(byteArray, 0, byteArray.Length);

                for (int indexX = 0; indexX < this._CollectAllAssetItemList.Count; ++indexX)
                {
                    assetItem = this._CollectAllAssetItemList[indexX];
                    byteArray = Encoding.UTF8.GetBytes(string.Format("AssetName:{0}\n", assetItem.AssetLongPackageName));
                    fileStream.Write(byteArray, 0, byteArray.Length);

                    for (int indexY = 0; indexY < assetItem.ChildDependencyList.Count; ++indexY)
                    {
                        dependencyAssetItem = assetItem.ChildDependencyList[indexY];
                        byteArray = Encoding.UTF8.GetBytes(string.Format("{0}\n", dependencyAssetItem.AssetLongPackageName));
                        fileStream.Write(byteArray, 0, byteArray.Length);
                    }

                    byteArray = Encoding.UTF8.GetBytes(string.Format("\n"));
                    fileStream.Write(byteArray, 0, byteArray.Length);
                }

                fileStream.Close();
                fileStream.Dispose();
                fileStream = null;
            }
            catch (Exception exp)
            {
                UtilDebug.Log(string.Format("error {0}", exp.Message));

                if (null != fileStream)
                {
                    fileStream.Close();
                    fileStream.Dispose();
                    fileStream = null;
                }
            }
            finally
            {
                if (null != fileStream)
                {
                    fileStream.Close();
                    fileStream.Dispose();
                    fileStream = null;
                }
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteAllCollectAssetDependencyManifest, end"));
            }
        }

        protected void _WriteIncludeAssetDependencyManifest(string fileName)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteIncludeAssetDependencyManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetPackageUtil.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "IncludeAssetDependencyManifest");
            }
            if (File.Exists(fileName))
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("{0} exist, delete", fileName));
                }

                try
                {
                    File.Delete(fileName);
                }
                catch (Exception exp)
                {
                    if (AssetPackageUtil.ENABLE_ERROR_LOG)
                    {
                        UtilDebug.LogError(string.Format("{0} delete, error {1}", fileName, exp.Message));
                    }
                }
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("{0} not exist", fileName));
                }
            }

            FileStream fileStream = null;

            try
            {
                fileStream = new FileStream(fileName, FileMode.CreateNew, FileAccess.Write);

                AssetItemV2 assetItem = null;
                AssetItemV2 dependencyAssetItem = null;
                byte[] byteArray = null;

                byteArray = Encoding.UTF8.GetBytes(string.Format("Total _CollectAssetItem Count is {0}\n\n", this._CollectIncludeAssetItemList.Count));
                fileStream.Write(byteArray, 0, byteArray.Length);

                for (int indexX = 0; indexX < this._CollectIncludeAssetItemList.Count; ++indexX)
                {
                    assetItem = this._CollectIncludeAssetItemList[indexX];
                    byteArray = Encoding.UTF8.GetBytes(string.Format("AssetName:{0}\n", assetItem.AssetLongPackageName));
                    fileStream.Write(byteArray, 0, byteArray.Length);

                    for (int indexY = 0; indexY < assetItem.ChildDependencyList.Count; ++indexY)
                    {
                        dependencyAssetItem = assetItem.ChildDependencyList[indexY];
                        if (dependencyAssetItem.IsIncludeAssetBundleItem)
                        {
                            byteArray = Encoding.UTF8.GetBytes(string.Format("{0}\n", dependencyAssetItem.AssetLongPackageName));
                            fileStream.Write(byteArray, 0, byteArray.Length);
                        }
                    }

                    byteArray = Encoding.UTF8.GetBytes(string.Format("\n"));
                    fileStream.Write(byteArray, 0, byteArray.Length);
                }

                fileStream.Close();
                fileStream.Dispose();
                fileStream = null;
            }
            catch (Exception exp)
            {
                UtilDebug.Log(string.Format("error {0}", exp.Message));

                if (null != fileStream)
                {
                    fileStream.Close();
                    fileStream.Dispose();
                    fileStream = null;
                }
            }
            finally
            {
                if (null != fileStream)
                {
                    fileStream.Close();
                    fileStream.Dispose();
                    fileStream = null;
                }
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteIncludeAssetDependencyManifest, end"));
            }
        }

        protected void _WriteExcludeAssetDependencyManifest(string fileName)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteExcludeAssetDependencyManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetPackageUtil.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "ExcludeAssetDependencyManifest");
            }
            if (File.Exists(fileName))
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("{0} exist, delete", fileName));
                }

                try
                {
                    File.Delete(fileName);
                }
                catch (Exception exp)
                {
                    if (AssetPackageUtil.ENABLE_ERROR_LOG)
                    {
                        UtilDebug.LogError(string.Format("{0} delete, error {1}", fileName, exp.Message));
                    }
                }
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("{0} not exist", fileName));
                }
            }

            FileStream fileStream = null;

            try
            {
                fileStream = new FileStream(fileName, FileMode.CreateNew, FileAccess.Write);

                AssetItemV2 assetItem = null;
                AssetItemV2 dependencyAssetItem = null;
                byte[] byteArray = null;

                byteArray = Encoding.UTF8.GetBytes(string.Format("Total _CollectAssetItem Count is {0}\n\n", this._CollectExcludeAssetItemList.Count));
                fileStream.Write(byteArray, 0, byteArray.Length);

                for (int indexX = 0; indexX < this._CollectExcludeAssetItemList.Count; ++indexX)
                {
                    assetItem = this._CollectExcludeAssetItemList[indexX];
                    byteArray = Encoding.UTF8.GetBytes(string.Format("AssetName:{0}\n", assetItem.AssetLongPackageName));
                    fileStream.Write(byteArray, 0, byteArray.Length);

                    for (int indexY = 0; indexY < assetItem.ChildDependencyList.Count; ++indexY)
                    {
                        dependencyAssetItem = assetItem.ChildDependencyList[indexY];

                        if (!dependencyAssetItem.IsIncludeAssetBundleItem)
                        {
                            byteArray = Encoding.UTF8.GetBytes(string.Format("{0}\n", dependencyAssetItem.AssetLongPackageName));
                            fileStream.Write(byteArray, 0, byteArray.Length);
                        }
                    }

                    byteArray = Encoding.UTF8.GetBytes(string.Format("\n"));
                    fileStream.Write(byteArray, 0, byteArray.Length);
                }

                fileStream.Close();
                fileStream.Dispose();
                fileStream = null;
            }
            catch (Exception exp)
            {
                UtilDebug.Log(string.Format("error {0}", exp.Message));

                if (null != fileStream)
                {
                    fileStream.Close();
                    fileStream.Dispose();
                    fileStream = null;
                }
            }
            finally
            {
                if (null != fileStream)
                {
                    fileStream.Close();
                    fileStream.Dispose();
                    fileStream = null;
                }
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteExcludeAssetDependencyManifest, end"));
            }
        }

        protected void _WriteAllCollectAssetManifest(string fileName)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteAllCollectAssetManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetPackageUtil.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "AllCollectAssetManifest");
            }
            if (File.Exists(fileName))
            {
                UtilDebug.Log(string.Format("{0} exist, delete", fileName));

                try
                {
                    File.Delete(fileName);
                }
                catch (Exception exp)
                {
                    if (AssetPackageUtil.ENABLE_ERROR_LOG)
                    {
                        UtilDebug.LogError(string.Format("{0} delete, error {1}", fileName, exp.Message));
                    }
                }
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("{0} not exist", fileName));
                }
            }

            FileStream fileStream = null;

            try
            {
                fileStream = new FileStream(fileName, FileMode.CreateNew, FileAccess.Write);

                AssetItemV2 assetItem = null;
                byte[] byteArray = null;

                byteArray = Encoding.UTF8.GetBytes(string.Format("Total _CollectAllAssetItemList Count is {0}\n\n", this._CollectAllAssetItemList.Count));
                fileStream.Write(byteArray, 0, byteArray.Length);

                for (int indexX = 0; indexX < this._CollectAllAssetItemList.Count; ++indexX)
                {
                    assetItem = this._CollectAllAssetItemList[indexX];
                    byteArray = Encoding.UTF8.GetBytes(string.Format("AssetName:{0}\n\n", assetItem.AssetLongPackageName));
                    fileStream.Write(byteArray, 0, byteArray.Length);
                }

                fileStream.Close();
                fileStream.Dispose();
                fileStream = null;
            }
            catch (Exception exp)
            {
                UtilDebug.Log(string.Format("error {0}", exp.Message));

                if (null != fileStream)
                {
                    fileStream.Close();
                    fileStream.Dispose();
                    fileStream = null;
                }
            }
            finally
            {
                if (null != fileStream)
                {
                    fileStream.Close();
                    fileStream.Dispose();
                    fileStream = null;
                }
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteAllCollectAssetManifest, end"));
            }
        }

        protected void _WriteIncludeAssetManifest(string fileName)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteIncludeAssetManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetPackageUtil.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "IncludeAssetManifest");
            }
            if (File.Exists(fileName))
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("{0} exist, delete", fileName));
                }

                try
                {
                    File.Delete(fileName);
                }
                catch (Exception exp)
                {
                    if (AssetPackageUtil.ENABLE_ERROR_LOG)
                    {
                        UtilDebug.LogError(string.Format("{0} delete, error {1}", fileName, exp.Message));
                    }
                }
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("{0} not exist", fileName));
                }
            }

            FileStream fileStream = null;

            try
            {
                fileStream = new FileStream(fileName, FileMode.CreateNew, FileAccess.Write);

                AssetItemV2 assetItem = null;
                byte[] byteArray = null;

                byteArray = Encoding.UTF8.GetBytes(string.Format("Total _CollectExcludeAssetItemList Count is {0}\n\n", this._CollectIncludeAssetItemList.Count));
                fileStream.Write(byteArray, 0, byteArray.Length);

                for (int indexX = 0; indexX < this._CollectIncludeAssetItemList.Count; ++indexX)
                {
                    assetItem = this._CollectIncludeAssetItemList[indexX];
                    byteArray = Encoding.UTF8.GetBytes(string.Format("AssetName:{0}\n\n", assetItem.AssetLongPackageName));
                    fileStream.Write(byteArray, 0, byteArray.Length);
                }

                fileStream.Close();
                fileStream.Dispose();
                fileStream = null;
            }
            catch (Exception exp)
            {
                if (AssetPackageUtil.ENABLE_ERROR_LOG)
                {
                    UtilDebug.LogError(string.Format("error {0}", exp.Message));
                }

                if (null != fileStream)
                {
                    fileStream.Close();
                    fileStream.Dispose();
                    fileStream = null;
                }
            }
            finally
            {
                if (null != fileStream)
                {
                    fileStream.Close();
                    fileStream.Dispose();
                    fileStream = null;
                }
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteIncludeAssetManifest, end"));
            }
        }

        protected void _WriteExcludeAssetManifest(string fileName)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteExcludeAssetManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetPackageUtil.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "ExcludeAssetManifest");
            }
            if (File.Exists(fileName))
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("{0} exist, delete", fileName));
                }

                try
                {
                    File.Delete(fileName);
                }
                catch (Exception exp)
                {
                    if (AssetPackageUtil.ENABLE_ERROR_LOG)
                    {
                        UtilDebug.LogError(string.Format("{0} delete, error {1}", fileName, exp.Message));
                    }
                }
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("{0} not exist", fileName));
                }
            }

            FileStream fileStream = null;

            try
            {
                if (File.Exists(fileName))
                {
                    File.Delete(fileName);
                }

                fileStream = new FileStream(fileName, FileMode.CreateNew, FileAccess.Write);

                AssetItemV2 assetItem = null;
                byte[] byteArray = null;

                byteArray = Encoding.UTF8.GetBytes(string.Format("Total _CollectExcludeAssetItemList Count is {0}\n\n", this._CollectExcludeAssetItemList.Count));
                fileStream.Write(byteArray, 0, byteArray.Length);

                for (int indexX = 0; indexX < this._CollectExcludeAssetItemList.Count; ++indexX)
                {
                    assetItem = this._CollectExcludeAssetItemList[indexX];
                    byteArray = Encoding.UTF8.GetBytes(string.Format("AssetName:{0}\n\n", assetItem.AssetLongPackageName));
                    fileStream.Write(byteArray, 0, byteArray.Length);
                }

                fileStream.Close();
                fileStream.Dispose();
                fileStream = null;
            }
            catch (Exception exp)
            {
                if (AssetPackageUtil.ENABLE_ERROR_LOG)
                {
                    UtilDebug.LogError(string.Format("error {0}", exp.Message));
                }

                if (null != fileStream)
                {
                    fileStream.Close();
                    fileStream.Dispose();
                    fileStream = null;
                }
            }
            finally
            {
                if (null != fileStream)
                {
                    fileStream.Close();
                    fileStream.Dispose();
                    fileStream = null;
                }
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteExcludeAssetManifest, end"));
            }
        }

        protected void _WriteAllAssetManifest()
        {
            this._WriteAssetBundleManifest("");
            this._WriteIncludeAssetDependencyManifest("");
            this._WriteExcludeAssetDependencyManifest("");
            this._WriteAllCollectAssetDependencyManifest("");
            this._WriteIncludeAssetManifest("");
            this._WriteExcludeAssetManifest("");
            this._WriteAllCollectAssetManifest("");
            this._WriteAssetBundleChangedFilePathManifest("");
        }

        protected void _FindDependency(AssetItemV2 assetItem)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_FindDependency, start"));
            }

            Stack<AssetItemV2> stack = new Stack<AssetItemV2>();
            this._DepthFirstFindDependency(assetItem, stack);
            stack.Clear();

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_FindDependency, end"));
            }
        }

        protected void _DepthFirstFindDependency(AssetItemV2 assetItem, Stack<AssetItemV2> stack)
        {
            // 循环依赖检测
            if (this._IsCircularDependency(assetItem, stack))
            {
                if (AssetPackageUtil.ENABLE_ERROR_LOG)
                {
                    UtilDebug.LogError(string.Format("_DepthFirstFindDependency, CircularDependency {0}", assetItem.AssetLongPackageName));
                }
            }

            if (!assetItem.IsCollectedDependency)
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("_DepthFirstFindDependency, {0}", assetItem.AssetLongPackageName));
                }

                stack.Push(assetItem);

                assetItem.IsCollectedDependency = true;

                string[] dependencyArray = this.mAssetRegister.GetDependencies(assetItem.AssetLongPackageName, false);
                AssetItemV2 depencyAssetItem = null;
                string dependencyPath = "";

                for (int index = 0; index < dependencyArray.Length; ++index)
                {
                    dependencyPath = dependencyArray[index];

                    if (assetItem.AssetLongPackageName != dependencyPath)
                    {
                        if (this._CollectAssetPath2AssetDic.TryGetValue(dependencyPath, out depencyAssetItem))
                        {
                            assetItem.AddChild(depencyAssetItem);
                            depencyAssetItem.AddParent(assetItem);
                            this._DepthFirstFindDependency(depencyAssetItem, stack);
                        }
                        else
                        {
                            if (AssetPackageUtil.ENABLE_COMMON_LOG)
                            {
                                // 依赖查找不到，会自动打包到 AssetBundle 包中去的
                                UtilDebug.Log(string.Format("_DepthFirstFindDependency, {0} Can not find file", dependencyArray[index]));
                            }
                        }
                    }
                    else
                    {
                        if (AssetPackageUtil.ENABLE_COMMON_LOG)
                        {
                            UtilDebug.Log(string.Format("_DepthFirstFindDependency, {0} same dependency", dependencyArray[index]));
                        }
                    }
                }

                AssetItemV2 assetItemPop = stack.Pop();
                UtilDebug.Assert(assetItemPop == assetItem);
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_DepthFirstFindDependency, end");
            }
        }

        protected void _DepthFirstBuildOneAssetBundleItem(AssetItemV2 assetItem, AssetBundleItemV2 assetBundleItemV2)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_DepthFirstBuildOneAssetBundleItem, start");
            }

            if (!assetItem.IsAddedAssetBundleBuild)
            {
                assetItem.IsAddedAssetBundleBuild = true;

                if (assetItem.IsIncludeAssetBundleItem)
                {
                    assetBundleItemV2.AssetItemList.Add(assetItem);
                }
                else
                {
                    if (AssetPackageUtil.ENABLE_COMMON_LOG)
                    {
                        UtilDebug.Log(string.Format("_DepthFirstBuildOneAssetBundleItem, exclude {0}", assetItem.AssetLongPackageName));
                    }
                }

                AssetItemV2 dependencyAssetItemV2 = null;

                for (int index = 0; index < assetItem.ChildDependencyList.Count; ++index)
                {
                    dependencyAssetItemV2 = assetItem.ChildDependencyList[index];

                    if (1 == dependencyAssetItemV2.GetParentReferenceNum())
                    {
                        this._DepthFirstBuildOneAssetBundleItem(dependencyAssetItemV2, assetBundleItemV2);
                    }
                    else if (dependencyAssetItemV2.GetParentReferenceNum() > 1)
                    {
                        this._BuildOneAssetBundleItem(dependencyAssetItemV2);
                    }
                    else
                    {
                        if (AssetPackageUtil.ENABLE_COMMON_LOG)
                        {
                            UtilDebug.Log(string.Format("_DepthFirstBuildOneAssetBundleItem, error {0}", assetItem.AssetLongPackageName));
                        }
                    }
                }
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_DepthFirstBuildOneAssetBundleItem, end");
            }
        }

        protected virtual void _BuildOneAssetBundleItem(AssetItemV2 assetItem)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_BuildOneAssetBundleItem, start");
            }

            if (!assetItem.IsAddedAssetBundleBuild)
            {
                AssetBundleItemV2 assetBundleItemV2 = new AssetBundleItemV2();

                this._DepthFirstBuildOneAssetBundleItem(assetItem, assetBundleItemV2);

                // 有可能被在 Exclude Asset 列表里面
                if (assetBundleItemV2.GetAssetCount() > 0)
                {
                    this._AssetBundleItemList.Add(assetBundleItemV2);
                    assetBundleItemV2.InitAssetBundleName(this);
                }
                else
                {
                    if (AssetPackageUtil.ENABLE_COMMON_LOG)
                    {
                        UtilDebug.Log("_BuildOneAssetBundleItem, AssetBundle count is zero");
                    }
                }
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_BuildOneAssetBundleItem, end");
            }
        }

        protected void _OutDetailOneAssetBundleInfo(AssetBundleItemV2 assetBundleItem)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_OutDetailAssetBundleInfo, start");
                UtilDebug.Log(string.Format("Main Asset: {0}", assetBundleItem.GetAssetBundlePath()));

                for (int index = 0; index < assetBundleItem.AssetItemList.Count; ++index)
                {
                    UtilDebug.Log(string.Format("Child Asset: {0}", assetBundleItem.AssetItemList[index].AssetLongPackageName));
                }

                UtilDebug.Log("_OutDetailAssetBundleInfo, end");
            }
        }

        protected void _OutDetailAssetBundleInfo()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_OutDetailAssetBundleInfo, start");
            }

            for (int index = 0; index < this._AssetBundleItemList.Count; ++index)
            {
                this._OutDetailOneAssetBundleInfo(this._AssetBundleItemList[index]);
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_OutDetailAssetBundleInfo, start");
            }
        }

        protected bool _IsIncludeInCollectList(string assetRelativePathFromAsset)
        {
            return true;
        }

        protected bool _IsExcludeAssetBundleFileExtNameList(string extName)
        {
            return this._ExcludeAssetBundleFileExtNameList.Contains(extName);
        }

        protected void _OnFileHandle(string fullPath)
        {
            if (!this._IsExcludeAssetBundleFileExtNameList(AssetPackageUtil.GetFileExtName(fullPath)))
            {
                if (this._IsIncludeInCollectList(fullPath))
                {
                    AssetItemV2 assetItem = new AssetItemV2();
					fullPath = UtilFileIO.normalPath(fullPath);
					assetItem.AssetAbsolutePath = fullPath;
					assetItem.AssetLongPackageName = UtilUE4EngineWrap.ConvertFilenameToLongPackageName(ref fullPath);
                    assetItem.IsIncludeAssetBundleItem = this._IsIncludeAssetBundleItemList(assetItem);
                    this._AddAssetItem(assetItem);

                    if (AssetPackageUtil.ENABLE_COMMON_LOG)
                    {
                        UtilDebug.Log(string.Format("_OnFileHandle, {0}", assetItem.AssetLongPackageName));
                    }
                }
            }
        }
        
        protected void _CollectAssetListByRootDir(string rootPath)
        {
            if (Directory.Exists(rootPath))
            {
                AssetPackageUtil.TraverseDir(rootPath, true, this._OnFileHandle);
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("_CollectAssetListByRootDir, {0} path not exist", rootPath));
                }
            }
        }

        protected void _CollectAllAssetList()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_CollectAssetList, start");
            }

            string rootPath = "";

            for (int index = 0; index < this._CollectRootPathList.Count; ++index)
            {
                rootPath = this._CollectRootPathList[index];
                this._CollectAssetListByRootDir(rootPath);
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_CollectAssetList, end");
            }
        }

        protected void _CollectAssetDependency()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_CollectAssetDependency, start");
            }

            AssetItemV2 assetItem = null;
            int listLen = this._CollectAllAssetItemList.Count;
            int index = 0;

            for (; index < listLen; ++index)
            {
                assetItem = this._CollectAllAssetItemList[index];
                this._FindDependency(assetItem);
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_CollectAssetDependency, end");
            }
        }

        protected virtual void _BuildAssetBundleItemList()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_BuildAssetBundleList, start");
            }

            AssetItemV2 assetItemV2 = null;

            for (int index = 0; index < this._CollectAllAssetItemList.Count; ++index)
            {
                assetItemV2 = this._CollectAllAssetItemList[index];

                if (0 == assetItemV2.GetParentReferenceNum())
                {
                    this._BuildOneAssetBundleItem(assetItemV2);
                }
            }

            this._OutDetailAssetBundleInfo();

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_BuildAssetBundleList, end");
            }
        }

        protected void _BuildAssetBundleBuildList()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_BuildAssetBundleList, start");
            }

            AssetBundleItemV2 assetBundleItem = null;

            for (int index = 0; index < this._AssetBundleItemList.Count; ++index)
            {
                assetBundleItem = this._AssetBundleItemList[index];
                AssetBundleBuild assetBundleBuild = new AssetBundleBuild();
                //this._AssetBundleBuildList.Add(assetBundleBuild);
                assetBundleBuild.assetBundleName = assetBundleItem.GetAssetBundlePath();
                assetBundleBuild.assetNames = new string[assetBundleItem.AssetItemList.Count];

                for (int indexItem = 0; indexItem < assetBundleItem.AssetItemList.Count; ++indexItem)
                {
                    assetBundleBuild.assetNames[indexItem] = assetBundleItem.AssetItemList[indexItem].AssetLongPackageName;
                }

                this._AssetBundleBuildList.Add(assetBundleBuild);
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_BuildAssetBundleList, end");
            }
        }

        protected void _BuildAssetBundleImpl()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_BuildAssetBundleImpl, start");
            }

			AssetPackageUtil.BuildAssetBundle(this);

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_BuildAssetBundleImpl, end");
            }
        }

        public virtual void OutAssetManifest()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("OutAssetManifest, start");
            }

            this._CollectAllAssetList();
            this._CollectAssetDependency();
            this._BuildAssetBundleItemList();
            this._CheckAssetCorrect();
            this._WriteAllAssetManifest();

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("OutAssetManifest, end");
            }
        }

        public virtual void BuildAssetBundleItemInfo()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("BuildAssetBundleItemInfo, start");
            }

            this._CollectAllAssetList();
            this._CollectAssetDependency();
            this._BuildAssetBundleItemList();
            this._CheckAssetCorrect();
            this._WriteAllAssetManifest();

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("BuildAssetBundleItemInfo, end");
            }
        }

        public void BuildAssetBundle()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("BuildAssetBundle, start");
            }

            this._CollectAllAssetList();
            this._CollectAssetDependency();
            this._BuildAssetBundleItemList();
            this._CheckAssetCorrect();
            this._BuildAssetBundleBuildList();
            this._BuildAssetBundleImpl();
            this._WriteAllAssetManifest();

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("BuildAssetBundle, end");
            }
        }
    }

    public class SingleDependencyAssetPackageGraph : AssetPackageGraph
	{
        public SingleDependencyAssetPackageGraph()
        {

        }
    }

    public class SingleFileAssetPackageGraph : AssetPackageGraph
	{
        public SingleFileAssetPackageGraph()
        {

        }

        protected override void _BuildOneAssetBundleItem(AssetItemV2 assetItem)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_BuildOneAssetBundleItem, start");
            }

            if (!assetItem.IsAddedAssetBundleBuild)
            {
                AssetBundleItemV2 assetBundleItemV2 = new AssetBundleItemV2();
                this._AssetBundleItemList.Add(assetBundleItemV2);
                assetBundleItemV2.AssetItemList.Add(assetItem);
                assetBundleItemV2.InitAssetBundleName(this);
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_BuildOneAssetBundleItem, end");
            }
        }

        protected override void _BuildAssetBundleItemList()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_BuildAssetBundleList, start");
            }

            AssetItemV2 assetItemV2 = null;

            for (int index = 0; index < this._CollectAllAssetItemList.Count; ++index)
            {
                assetItemV2 = this._CollectAllAssetItemList[index];
                this._BuildOneAssetBundleItem(assetItemV2);
            }

            this._OutDetailAssetBundleInfo();

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_BuildAssetBundleList, end");
            }
        }

        public override void BuildAssetBundleItemInfo()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("BuildAssetBundleItemInfo, start");
            }

            this._CollectAllAssetList();
            this._CollectAssetDependency();
            this._BuildAssetBundleItemList();

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("BuildAssetBundleItemInfo, end");
            }
        }
    }
}