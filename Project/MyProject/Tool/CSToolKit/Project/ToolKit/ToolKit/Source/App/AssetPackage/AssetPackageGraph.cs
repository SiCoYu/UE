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

        public string AssetRelativePathStartWithAssets;
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
            if (!this.AssetPath2ChildAssetDic.ContainsKey(childAssetItem.AssetRelativePathStartWithAssets))
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("AddChild, Parent {0} , Child {1}", this.AssetRelativePathStartWithAssets, childAssetItem.AssetRelativePathStartWithAssets));
                }

                this.ChildDependencyList.Add(childAssetItem);
                this.AssetPath2ChildAssetDic.Add(childAssetItem.AssetRelativePathStartWithAssets, childAssetItem);
            }
            else
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("AddChild, {0} already exist", childAssetItem.AssetRelativePathStartWithAssets));
                }
            }
        }

        public void AddParent(AssetItemV2 parentAssetItem)
        {
            if (!this.AssetPath2ParentAssetDic.ContainsKey(parentAssetItem.AssetRelativePathStartWithAssets))
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("AddParent, Parent {0} , Child {1}", parentAssetItem.AssetRelativePathStartWithAssets, this.AssetRelativePathStartWithAssets));
                }

                this.ParentReferenceList.Add(parentAssetItem);
                this.AssetPath2ParentAssetDic.Add(parentAssetItem.AssetRelativePathStartWithAssets, parentAssetItem);
            }
            else
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("AddParent, {0} already exist", parentAssetItem.AssetRelativePathStartWithAssets));
                }
            }
        }
    }

    public class AssetBundleItemV2
    {
        // 没有扩展名字，从 AssetBundleBuilderV2.ASB_RES_PATH_SLASH 后开始的
        protected string _AssetBundleShortName;
        // 扩展名字  unity3d，从 AssetBundleBuilderV2.ASB_RES_PATH_SLASH 后开始的小写
        protected string _AssetBundleName;
        public List<AssetItemV2> AssetItemList;

        public AssetBundleItemV2()
        {
            this.AssetItemList = new List<AssetItemV2>();
        }

        public void InitAssetBundleName(AssetBundleBuilderContextV2 assetContext)
        {
            UnityEngine.Debug.Assert(this.AssetItemList.Count > 0, "InitAssetBundleName error");

            string origPath = this.AssetItemList[0].AssetRelativePathStartWithAssets;
            origPath = assetContext.GetAndCheckAssetBundleFileNameLength(origPath);

            this._AssetBundleName = AssetBundleBuilderUtilV2.ChangeExtNameDotToUnderlineAndAddAssetBundleExt(origPath);

            if (0 == this._AssetBundleName.IndexOf(AssetBundleBuilderUtilV2.ASB_RES_PATH_SLASH))
            {
                this._AssetBundleShortName = AssetBundleBuilderUtilV2.GetAsbShortName(origPath);
            }

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("InitAssetBundleName, AssetBundleName is {0}", this._AssetBundleName));
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
            if (0 == this._AssetBundleName.IndexOf(AssetBundleBuilderUtilV2.ASB_RES_PATH_SLASH))
            {
                string name = this._AssetBundleName.Substring(AssetBundleBuilderUtilV2.ASB_RES_PATH_SLASH.Length);
                return name.ToLower();
            }

            return this._AssetBundleName;
        }

        public List<string> GetAssetNameList()
        {
            List<string> nameList = new List<string>();

            for (int index = 0; index < this.AssetItemList.Count; ++index)
            {
                nameList.Add(this.AssetItemList[index].AssetRelativePathStartWithAssets);
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
                assetItem.AssetRelativePathStartWithAssets = nameList[index];
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

    public class AssetPackageGraph
	{
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

        public AssetBundleBuilderContextV2()
        {
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

        public void AddCollectRootPath(string relativePathStartWithAsset)
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("AddRootPath, {0}", relativePathStartWithAsset));
            }
            UnityEngine.Debug.Assert(!string.IsNullOrEmpty(relativePathStartWithAsset), "path is null");
            UnityEngine.Debug.Assert(0 == relativePathStartWithAsset.IndexOf("Assets/"), "path is not start with Asset");

            string fullPath = AssetBundleBuilderUtilV2.GetFullPathByRelativePathStartWithAsset(relativePathStartWithAsset);
            this._CollectRootPathList.Add(fullPath);
        }

        public void AddIncludeAssetBundlePath(string relativePathStartWithAsset)
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("AddIncludeAssetBundlePath, {0}", relativePathStartWithAsset));
            }

            UnityEngine.Debug.Assert(!string.IsNullOrEmpty(relativePathStartWithAsset), "path is null");
            UnityEngine.Debug.Assert(0 == relativePathStartWithAsset.IndexOf("Assets/"), "path is not start with Asset");

            for (int index = 0; index < this._ExcludeAssetBundlePathList.Count; ++index)
            {
                UnityEngine.Debug.Assert(relativePathStartWithAsset != this._ExcludeAssetBundlePathList[index], "relativePathStartWithAsset already in _ExcludeAssetBundlePathList");
            }


            if (!this._IncludeAssetBundlePathList.Contains(relativePathStartWithAsset))
            {
                this._IncludeAssetBundlePathList.Add(relativePathStartWithAsset);
            }
            else
            {
                UnityEngine.Debug.Log(string.Format("AddIncludeAssetBundlePath, {0} is already in", relativePathStartWithAsset));
            }
        }

        public void AddExcludeAssetBundlePath(string relativePathStartWithAsset)
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("AddExcludeAssetBundlePath, {0}", relativePathStartWithAsset));
            }

            UnityEngine.Debug.Assert(!string.IsNullOrEmpty(relativePathStartWithAsset), "path is null");
            UnityEngine.Debug.Assert(0 == relativePathStartWithAsset.IndexOf("Assets/"), "path is not start with Asset");

            for (int index = 0; index < this._IncludeAssetBundlePathList.Count; ++index)
            {
                UnityEngine.Debug.Assert(relativePathStartWithAsset != this._IncludeAssetBundlePathList[index], "relativePathStartWithAsset already in _IncludeAssetBundlePathList");
            }

            if (!this._ExcludeAssetBundlePathList.Contains(relativePathStartWithAsset))
            {
                this._ExcludeAssetBundlePathList.Add(relativePathStartWithAsset);
            }
            else
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("AddExcludeAssetBundlePath, {0} is already in", relativePathStartWithAsset));
                }
            }
        }

        public void AddExcludeAssetBundleFile(string relativePathStartWithAsset)
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("AddExcludeAssetBundleFile, {0}", relativePathStartWithAsset));
            }

            UnityEngine.Debug.Assert(!string.IsNullOrEmpty(relativePathStartWithAsset), "path is null");
            UnityEngine.Debug.Assert(0 == relativePathStartWithAsset.IndexOf("Assets/"), "path is not start with Asset");

            for (int index = 0; index < this._IncludeAssetBundlePathList.Count; ++index)
            {
                UnityEngine.Debug.Assert(relativePathStartWithAsset != this._IncludeAssetBundlePathList[index], "relativePathStartWithAsset already in _IncludeAssetBundlePathList");
            }

            if (!this._ExcludeAssetBundleFileList.Contains(relativePathStartWithAsset))
            {
                this._ExcludeAssetBundleFileList.Add(relativePathStartWithAsset);
            }
            else
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("AddExcludeAssetBundleFile, {0} is already in", relativePathStartWithAsset));
                }
            }
        }

        public void AddExcludeAssetBundleFileExtName(string extName)
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("AddExcludeAssetBundleFileExtName, {0}", extName));
            }

            UnityEngine.Debug.Assert(!string.IsNullOrEmpty(extName), "extName is null");

            if (!this._ExcludeAssetBundleFileExtNameList.Contains(extName))
            {
                this._ExcludeAssetBundleFileExtNameList.Add(extName);
            }
            else
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("extName, {0} is already in", extName));
                }
            }
        }

        protected void _CheckIncludeAndExcludePath()
        {
            
        }

        protected void _AddAssetItem(AssetItemV2 assetItem)
        {
            if (!this._CollectAssetPath2AssetDic.ContainsKey(assetItem.AssetRelativePathStartWithAssets))
            {
                this._CollectAssetPath2AssetDic.Add(assetItem.AssetRelativePathStartWithAssets, assetItem);
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
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("AddAssetItem, {0} is already", assetItem.AssetRelativePathStartWithAssets));
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
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_CheckAssetUniqueInAssetBundleItem, start"));
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

                    if (!path2FlagDic.ContainsKey(assetItem.AssetRelativePathStartWithAssets))
                    {
                        path2FlagDic.Add(assetItem.AssetRelativePathStartWithAssets, true);
                    }
                    else
                    {
                        if (AssetBundleBuilderUtilV2.ENABLE_ERROR_LOG)
                        {
                            UnityEngine.Debug.LogError(string.Format("_CheckAssetUniqueInAssetBundleItem, diff {0} error", assetItem.AssetRelativePathStartWithAssets));
                        }
                    }
                }
            }

            if (path2FlagDic.Count != this._CollectIncludeAssetItemList.Count)
            {
                if (AssetBundleBuilderUtilV2.ENABLE_ERROR_LOG)
                {
                    UnityEngine.Debug.LogError(string.Format("_CheckAssetUniqueInAssetBundleItem, num error, {0} != {1}", path2FlagDic.Count, this._CollectIncludeAssetItemList.Count));

                    bool isFind = false;
                    foreach (KeyValuePair<string, bool> kvData in path2FlagDic)
                    {
                        isFind = false;

                        for (int index = 0; index < this._CollectIncludeAssetItemList.Count; ++index)
                        {
                            if (kvData.Key == this._CollectIncludeAssetItemList[index].AssetRelativePathStartWithAssets)
                            {
                                isFind = true;
                                break;
                            }
                        }

                        if(!isFind)
                        {
                            UnityEngine.Debug.LogError(string.Format("_CheckAssetUniqueInAssetBundleItem, kvData error, {0} not find", kvData.Key));
                        }
                    }

                    for (int index = 0; index < this._CollectIncludeAssetItemList.Count; ++index)
                    {
                        isFind = false;

                        foreach (KeyValuePair<string, bool> kvData in path2FlagDic)
                        {
                            if (kvData.Key == this._CollectIncludeAssetItemList[index].AssetRelativePathStartWithAssets)
                            {
                                isFind = true;
                                break;
                            }
                        }

                        if (!isFind)
                        {
                            UnityEngine.Debug.LogError(string.Format("_CheckAssetUniqueInAssetBundleItem, List error, {0} not find", this._CollectIncludeAssetItemList[index].AssetRelativePathStartWithAssets));
                        }
                    }
                }
            }

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_CheckAssetUniqueInAssetBundleItem, end"));
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

            ret = !_ExcludeAssetBundleFileList.Contains(assetItem.AssetRelativePathStartWithAssets);

            if (ret)
            {
                for (int index = 0; index < this._IncludeAssetBundlePathList.Count; ++index)
                {
                    if (0 == assetItem.AssetRelativePathStartWithAssets.IndexOf(this._IncludeAssetBundlePathList[index]))
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
                        if (0 == assetItem.AssetRelativePathStartWithAssets.IndexOf(this._ExcludeAssetBundlePathList[index]))
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
            string filePathNoFileName = AssetBundleBuilderUtilV2.GetFilePathNoFileName(origPath);
            string fileNameNoExtName = AssetBundleBuilderUtilV2.GetFileNameNoPathAndExt(origPath);
            string fileExtName = AssetBundleBuilderUtilV2.GetFileExtName(origPath);
            int assetBundleFileNameLen = AssetBundleBuilderUtilV2.GetAssetBundleFileNameLength(fileNameNoExtName, fileExtName);

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
                    UnityEngine.Debug.LogError(string.Format("{0} filenamenoext too short", origPath));
                }

                for (findIndex = 0; findIndex < 100; ++findIndex)
                {
                    if (0 == findIndex)
                    {
                        changedFileName = AssetBundleBuilderUtilV2.GetFullPathFromSeparate(filePathNoFileName, fileNameNoExtName, fileExtName);
                    }
                    else
                    {
                        changedFileName = AssetBundleBuilderUtilV2.GetFullPathFromSeparate(filePathNoFileName, string.Format("{0}{1}", findIndex - 1, fileNameNoExtName), fileExtName);
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
                            UnityEngine.Debug.Log(string.Format("{0} is already exist", changedFileName));
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
                    UnityEngine.Debug.LogError(string.Format("{0} is already exist", changedFileName));
                    throw new Exception(string.Format("{0} is already exist", changedFileName));
                }
            }

            if (!isValidChangedPath)
            {
                UnityEngine.Debug.LogError(string.Format("{0} is not valid", changedFileName));
                throw new Exception(string.Format("{0} is already exist", changedFileName));
            }

            return changedFileName;
        }

        // 输出到打包配置文件
        public void WriteAssetBundleManifestToBuilderConfig()
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("WriteAssetBundleManifestToBuilderConfig, start"));
            }

            using (var writer = new StreamWriter(AssetBundleBuilderUtilV2.ASB_RES_FILE_PATH))
            {
                writer.WriteLine(AssetBundleBuilderUtilV2.HeaderLine);
                for (int i = 0; i < this._AssetBundleItemList.Count; i++)
                {
                    writer.WriteLine(this._AssetBundleItemList[i].ToConfigString());
                }
            }

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("WriteAssetBundleManifestToBuilderConfig, end"));
            }
        }

        public void LoadAssetBundleManifestToBuilderConfig()
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("LoadAssetBundleManifestToBuilderConfig, start"));
            }

            TextAsset config = AssetDatabase.LoadAssetAtPath<TextAsset>(AssetBundleBuilderUtilV2.ASB_RES_FILE_PATH);

            List<AssetBundleItemV2> entries = new List<AssetBundleItemV2>();
            using (var reader = new StringReader(config.text))
            {
                // skip header line
                reader.ReadLine();

                while (reader.Peek() != -1)
                {
                    var line = reader.ReadLine().Trim();
                    if (line == "")
                        continue;

                    var values = line.Split(',');
                    var index = 0;

                    AssetBundleItemV2 assetBundleItem = new AssetBundleItemV2();
                    assetBundleItem.SetAsbShortName(values[index++].Trim());
                    assetBundleItem.SetAssetNameList(values[index++].Trim().Split(';'));

                    entries.Add(assetBundleItem);
                }
            }

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("LoadAssetBundleManifestToBuilderConfig, end"));
            }
        }

        protected void _WriteAssetBundleChangedFilePathManifest(string fileName)
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_WriteAssetBundleChangedFilePathManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetBundleBuilderUtilV2.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "ChangedFilePathManifest");
            }
            if (File.Exists(fileName))
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("{0} exist, delete", fileName));
                }

                try
                {
                    File.Delete(fileName);
                }
                catch (Exception exp)
                {
                    if (AssetBundleBuilderUtilV2.ENABLE_ERROR_LOG)
                    {
                        UnityEngine.Debug.LogError(string.Format("{0} delete, error {1}", fileName, exp.Message));
                    }
                }
            }
            else
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("{0} not exist", fileName));
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
                UnityEngine.Debug.Log(string.Format("error {0}", exp.Message));

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

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_WriteAssetBundleChangedFilePathManifest, end"));
            }
        }

        protected void _WriteAssetBundleManifest(string fileName)
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_WriteAssetBundleManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetBundleBuilderUtilV2.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "AssetBundleManifest");
            }
            if (File.Exists(fileName))
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("{0} exist, delete", fileName));
                }

                try
                {
                    File.Delete(fileName);
                }
                catch(Exception exp)
                {
                    if (AssetBundleBuilderUtilV2.ENABLE_ERROR_LOG)
                    {
                        UnityEngine.Debug.LogError(string.Format("{0} delete, error {1}", fileName, exp.Message));
                    }
                }
            }
            else
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("{0} not exist", fileName));
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
                        byteArray = Encoding.UTF8.GetBytes(string.Format("{0}\n", assetItem.AssetRelativePathStartWithAssets));
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
                UnityEngine.Debug.Log(string.Format("error {0}", exp.Message));

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

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_WriteAssetBundleManifest, end"));
            }
        }

        protected void _WriteAllCollectAssetDependencyManifest(string fileName)
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_WriteAllCollectAssetDependencyManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetBundleBuilderUtilV2.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "AllCollectAssetDependencyManifest");
            }
            if (File.Exists(fileName))
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("{0} exist, delete", fileName));
                }

                try
                {
                    File.Delete(fileName);
                }
                catch (Exception exp)
                {
                    if (AssetBundleBuilderUtilV2.ENABLE_ERROR_LOG)
                    {
                        UnityEngine.Debug.LogError(string.Format("{0} delete, error {1}", fileName, exp.Message));
                    }
                }
            }
            else
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("{0} not exist", fileName));
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
                    byteArray = Encoding.UTF8.GetBytes(string.Format("AssetName:{0}\n", assetItem.AssetRelativePathStartWithAssets));
                    fileStream.Write(byteArray, 0, byteArray.Length);

                    for (int indexY = 0; indexY < assetItem.ChildDependencyList.Count; ++indexY)
                    {
                        dependencyAssetItem = assetItem.ChildDependencyList[indexY];
                        byteArray = Encoding.UTF8.GetBytes(string.Format("{0}\n", dependencyAssetItem.AssetRelativePathStartWithAssets));
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
                UnityEngine.Debug.Log(string.Format("error {0}", exp.Message));

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

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_WriteAllCollectAssetDependencyManifest, end"));
            }
        }

        protected void _WriteIncludeAssetDependencyManifest(string fileName)
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_WriteIncludeAssetDependencyManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetBundleBuilderUtilV2.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "IncludeAssetDependencyManifest");
            }
            if (File.Exists(fileName))
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("{0} exist, delete", fileName));
                }

                try
                {
                    File.Delete(fileName);
                }
                catch (Exception exp)
                {
                    if (AssetBundleBuilderUtilV2.ENABLE_ERROR_LOG)
                    {
                        UnityEngine.Debug.LogError(string.Format("{0} delete, error {1}", fileName, exp.Message));
                    }
                }
            }
            else
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("{0} not exist", fileName));
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
                    byteArray = Encoding.UTF8.GetBytes(string.Format("AssetName:{0}\n", assetItem.AssetRelativePathStartWithAssets));
                    fileStream.Write(byteArray, 0, byteArray.Length);

                    for (int indexY = 0; indexY < assetItem.ChildDependencyList.Count; ++indexY)
                    {
                        dependencyAssetItem = assetItem.ChildDependencyList[indexY];
                        if (dependencyAssetItem.IsIncludeAssetBundleItem)
                        {
                            byteArray = Encoding.UTF8.GetBytes(string.Format("{0}\n", dependencyAssetItem.AssetRelativePathStartWithAssets));
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
                UnityEngine.Debug.Log(string.Format("error {0}", exp.Message));

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

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_WriteIncludeAssetDependencyManifest, end"));
            }
        }

        protected void _WriteExcludeAssetDependencyManifest(string fileName)
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_WriteExcludeAssetDependencyManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetBundleBuilderUtilV2.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "ExcludeAssetDependencyManifest");
            }
            if (File.Exists(fileName))
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("{0} exist, delete", fileName));
                }

                try
                {
                    File.Delete(fileName);
                }
                catch (Exception exp)
                {
                    if (AssetBundleBuilderUtilV2.ENABLE_ERROR_LOG)
                    {
                        UnityEngine.Debug.LogError(string.Format("{0} delete, error {1}", fileName, exp.Message));
                    }
                }
            }
            else
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("{0} not exist", fileName));
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
                    byteArray = Encoding.UTF8.GetBytes(string.Format("AssetName:{0}\n", assetItem.AssetRelativePathStartWithAssets));
                    fileStream.Write(byteArray, 0, byteArray.Length);

                    for (int indexY = 0; indexY < assetItem.ChildDependencyList.Count; ++indexY)
                    {
                        dependencyAssetItem = assetItem.ChildDependencyList[indexY];

                        if (!dependencyAssetItem.IsIncludeAssetBundleItem)
                        {
                            byteArray = Encoding.UTF8.GetBytes(string.Format("{0}\n", dependencyAssetItem.AssetRelativePathStartWithAssets));
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
                UnityEngine.Debug.Log(string.Format("error {0}", exp.Message));

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

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_WriteExcludeAssetDependencyManifest, end"));
            }
        }

        protected void _WriteAllCollectAssetManifest(string fileName)
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_WriteAllCollectAssetManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetBundleBuilderUtilV2.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "AllCollectAssetManifest");
            }
            if (File.Exists(fileName))
            {
                UnityEngine.Debug.Log(string.Format("{0} exist, delete", fileName));

                try
                {
                    File.Delete(fileName);
                }
                catch (Exception exp)
                {
                    if (AssetBundleBuilderUtilV2.ENABLE_ERROR_LOG)
                    {
                        UnityEngine.Debug.LogError(string.Format("{0} delete, error {1}", fileName, exp.Message));
                    }
                }
            }
            else
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("{0} not exist", fileName));
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
                    byteArray = Encoding.UTF8.GetBytes(string.Format("AssetName:{0}\n\n", assetItem.AssetRelativePathStartWithAssets));
                    fileStream.Write(byteArray, 0, byteArray.Length);
                }

                fileStream.Close();
                fileStream.Dispose();
                fileStream = null;
            }
            catch (Exception exp)
            {
                UnityEngine.Debug.Log(string.Format("error {0}", exp.Message));

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

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_WriteAllCollectAssetManifest, end"));
            }
        }

        protected void _WriteIncludeAssetManifest(string fileName)
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_WriteIncludeAssetManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetBundleBuilderUtilV2.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "IncludeAssetManifest");
            }
            if (File.Exists(fileName))
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("{0} exist, delete", fileName));
                }

                try
                {
                    File.Delete(fileName);
                }
                catch (Exception exp)
                {
                    if (AssetBundleBuilderUtilV2.ENABLE_ERROR_LOG)
                    {
                        UnityEngine.Debug.LogError(string.Format("{0} delete, error {1}", fileName, exp.Message));
                    }
                }
            }
            else
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("{0} not exist", fileName));
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
                    byteArray = Encoding.UTF8.GetBytes(string.Format("AssetName:{0}\n\n", assetItem.AssetRelativePathStartWithAssets));
                    fileStream.Write(byteArray, 0, byteArray.Length);
                }

                fileStream.Close();
                fileStream.Dispose();
                fileStream = null;
            }
            catch (Exception exp)
            {
                if (AssetBundleBuilderUtilV2.ENABLE_ERROR_LOG)
                {
                    UnityEngine.Debug.LogError(string.Format("error {0}", exp.Message));
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

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_WriteIncludeAssetManifest, end"));
            }
        }

        protected void _WriteExcludeAssetManifest(string fileName)
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_WriteExcludeAssetManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetBundleBuilderUtilV2.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "ExcludeAssetManifest");
            }
            if (File.Exists(fileName))
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("{0} exist, delete", fileName));
                }

                try
                {
                    File.Delete(fileName);
                }
                catch (Exception exp)
                {
                    if (AssetBundleBuilderUtilV2.ENABLE_ERROR_LOG)
                    {
                        UnityEngine.Debug.LogError(string.Format("{0} delete, error {1}", fileName, exp.Message));
                    }
                }
            }
            else
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("{0} not exist", fileName));
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
                    byteArray = Encoding.UTF8.GetBytes(string.Format("AssetName:{0}\n\n", assetItem.AssetRelativePathStartWithAssets));
                    fileStream.Write(byteArray, 0, byteArray.Length);
                }

                fileStream.Close();
                fileStream.Dispose();
                fileStream = null;
            }
            catch (Exception exp)
            {
                if (AssetBundleBuilderUtilV2.ENABLE_ERROR_LOG)
                {
                    UnityEngine.Debug.LogError(string.Format("error {0}", exp.Message));
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

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_WriteExcludeAssetManifest, end"));
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
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_FindDependency, start"));
            }

            Stack<AssetItemV2> stack = new Stack<AssetItemV2>();
            this._DepthFirstFindDependency(assetItem, stack);
            stack.Clear();

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log(string.Format("_FindDependency, end"));
            }
        }

        protected void _DepthFirstFindDependency(AssetItemV2 assetItem, Stack<AssetItemV2> stack)
        {
            // 循环依赖检测
            if (this._IsCircularDependency(assetItem, stack))
            {
                if (AssetBundleBuilderUtilV2.ENABLE_ERROR_LOG)
                {
                    UnityEngine.Debug.LogError(string.Format("_DepthFirstFindDependency, CircularDependency {0}", assetItem.AssetRelativePathStartWithAssets));
                }
            }

            if (!assetItem.IsCollectedDependency)
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("_DepthFirstFindDependency, {0}", assetItem.AssetRelativePathStartWithAssets));
                }

                stack.Push(assetItem);

                assetItem.IsCollectedDependency = true;

                string[] dependencyArray = AssetDataBaseV2.GetDependencies(assetItem.AssetRelativePathStartWithAssets, false);
                AssetItemV2 depencyAssetItem = null;
                string dependencyPath = "";

                for (int index = 0; index < dependencyArray.Length; ++index)
                {
                    dependencyPath = dependencyArray[index];

                    if (assetItem.AssetRelativePathStartWithAssets != dependencyPath)
                    {
                        if (this._CollectAssetPath2AssetDic.TryGetValue(dependencyPath, out depencyAssetItem))
                        {
                            assetItem.AddChild(depencyAssetItem);
                            depencyAssetItem.AddParent(assetItem);
                            this._DepthFirstFindDependency(depencyAssetItem, stack);
                        }
                        else
                        {
                            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                            {
                                // 依赖查找不到，会自动打包到 AssetBundle 包中去的
                                UnityEngine.Debug.Log(string.Format("_DepthFirstFindDependency, {0} Can not find file", dependencyArray[index]));
                            }
                        }
                    }
                    else
                    {
                        if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                        {
                            UnityEngine.Debug.Log(string.Format("_DepthFirstFindDependency, {0} same dependency", dependencyArray[index]));
                        }
                    }
                }

                AssetItemV2 assetItemPop = stack.Pop();
                UnityEngine.Debug.Assert(assetItemPop == assetItem);
            }

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_DepthFirstFindDependency, end");
            }
        }

        protected void _DepthFirstBuildOneAssetBundleItem(AssetItemV2 assetItem, AssetBundleItemV2 assetBundleItemV2)
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_DepthFirstBuildOneAssetBundleItem, start");
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
                    if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                    {
                        UnityEngine.Debug.Log(string.Format("_DepthFirstBuildOneAssetBundleItem, exclude {0}", assetItem.AssetRelativePathStartWithAssets));
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
                        if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                        {
                            UnityEngine.Debug.Log(string.Format("_DepthFirstBuildOneAssetBundleItem, error {0}", assetItem.AssetRelativePathStartWithAssets));
                        }
                    }
                }
            }

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_DepthFirstBuildOneAssetBundleItem, end");
            }
        }

        protected virtual void _BuildOneAssetBundleItem(AssetItemV2 assetItem)
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_BuildOneAssetBundleItem, start");
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
                    if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                    {
                        UnityEngine.Debug.Log("_BuildOneAssetBundleItem, AssetBundle count is zero");
                    }
                }
            }

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_BuildOneAssetBundleItem, end");
            }
        }

        protected void _OutDetailOneAssetBundleInfo(AssetBundleItemV2 assetBundleItem)
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_OutDetailAssetBundleInfo, start");
                UnityEngine.Debug.Log(string.Format("Main Asset: {0}", assetBundleItem.GetAssetBundlePath()));

                for (int index = 0; index < assetBundleItem.AssetItemList.Count; ++index)
                {
                    UnityEngine.Debug.Log(string.Format("Child Asset: {0}", assetBundleItem.AssetItemList[index].AssetRelativePathStartWithAssets));
                }

                UnityEngine.Debug.Log("_OutDetailAssetBundleInfo, end");
            }
        }

        protected void _OutDetailAssetBundleInfo()
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_OutDetailAssetBundleInfo, start");
            }

            for (int index = 0; index < this._AssetBundleItemList.Count; ++index)
            {
                this._OutDetailOneAssetBundleInfo(this._AssetBundleItemList[index]);
            }

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_OutDetailAssetBundleInfo, start");
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
            if (!this._IsExcludeAssetBundleFileExtNameList(AssetBundleBuilderUtilV2.GetFileExtName(fullPath)))
            {
                if (this._IsIncludeInCollectList(fullPath))
                {
                    AssetItemV2 assetItem = new AssetItemV2();
                    assetItem.AssetRelativePathStartWithAssets = AssetBundleBuilderUtilV2.GetRelativePathStartWithAsset(fullPath);
                    assetItem.IsIncludeAssetBundleItem = this._IsIncludeAssetBundleItemList(assetItem);
                    this._AddAssetItem(assetItem);

                    if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                    {
                        UnityEngine.Debug.Log(string.Format("_OnFileHandle, {0}", assetItem.AssetRelativePathStartWithAssets));
                    }
                }
            }
        }
        
        protected void _CollectAssetListByRootDir(string rootPath)
        {
            if (Directory.Exists(rootPath))
            {
                AssetBundleBuilderUtilV2.TraverseDir(rootPath, true, this._OnFileHandle);
            }
            else
            {
                if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                {
                    UnityEngine.Debug.Log(string.Format("_CollectAssetListByRootDir, {0} path not exist", rootPath));
                }
            }
        }

        protected void _CollectAllAssetList()
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_CollectAssetList, start");
            }

            string rootPath = "";

            for (int index = 0; index < this._CollectRootPathList.Count; ++index)
            {
                rootPath = this._CollectRootPathList[index];
                this._CollectAssetListByRootDir(rootPath);
            }

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_CollectAssetList, end");
            }
        }

        protected void _CollectAssetDependency()
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_CollectAssetDependency, start");
            }

            AssetItemV2 assetItem = null;
            int listLen = this._CollectAllAssetItemList.Count;
            int index = 0;

            for (; index < listLen; ++index)
            {
                assetItem = this._CollectAllAssetItemList[index];
                this._FindDependency(assetItem);
            }

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_CollectAssetDependency, end");
            }
        }

        protected virtual void _BuildAssetBundleItemList()
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_BuildAssetBundleList, start");
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

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_BuildAssetBundleList, end");
            }
        }

        protected void _BuildAssetBundleBuildList()
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_BuildAssetBundleList, start");
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
                    assetBundleBuild.assetNames[indexItem] = assetBundleItem.AssetItemList[indexItem].AssetRelativePathStartWithAssets;
                }

                this._AssetBundleBuildList.Add(assetBundleBuild);
            }

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_BuildAssetBundleList, end");
            }
        }

        protected void _BuildAssetBundleImpl()
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_BuildAssetBundleImpl, start");
            }

            AssetBundleBuilderUtilV2.BuildAssetBundle(this);

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_BuildAssetBundleImpl, end");
            }
        }

        public virtual void OutAssetManifest()
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("OutAssetManifest, start");
            }

            this._CollectAllAssetList();
            this._CollectAssetDependency();
            this._BuildAssetBundleItemList();
            this._CheckAssetCorrect();
            this._WriteAllAssetManifest();

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("OutAssetManifest, end");
            }
        }

        public virtual void BuildAssetBundleItemInfo()
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("BuildAssetBundleItemInfo, start");
            }

            this._CollectAllAssetList();
            this._CollectAssetDependency();
            this._BuildAssetBundleItemList();
            this._CheckAssetCorrect();
            this._WriteAllAssetManifest();

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("BuildAssetBundleItemInfo, end");
            }
        }

        public void BuildAssetBundle()
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("BuildAssetBundle, start");
            }

            this._CollectAllAssetList();
            this._CollectAssetDependency();
            this._BuildAssetBundleItemList();
            this._CheckAssetCorrect();
            this._BuildAssetBundleBuildList();
            this._BuildAssetBundleImpl();
            this._WriteAllAssetManifest();

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("BuildAssetBundle, end");
            }
        }
    }

    public class AssetBundleBuilderSingleDependencyContextV2 : AssetBundleBuilderContextV2
    {
        public AssetBundleBuilderSingleDependencyContextV2()
        {

        }
    }

    public class AssetBundleBuilderSingleFileContextV2 : AssetBundleBuilderContextV2
    {
        public AssetBundleBuilderSingleFileContextV2()
        {

        }

        protected override void _BuildOneAssetBundleItem(AssetItemV2 assetItem)
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_BuildOneAssetBundleItem, start");
            }

            if (!assetItem.IsAddedAssetBundleBuild)
            {
                AssetBundleItemV2 assetBundleItemV2 = new AssetBundleItemV2();
                this._AssetBundleItemList.Add(assetBundleItemV2);
                assetBundleItemV2.AssetItemList.Add(assetItem);
                assetBundleItemV2.InitAssetBundleName(this);
            }

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_BuildOneAssetBundleItem, end");
            }
        }

        protected override void _BuildAssetBundleItemList()
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_BuildAssetBundleList, start");
            }

            AssetItemV2 assetItemV2 = null;

            for (int index = 0; index < this._CollectAllAssetItemList.Count; ++index)
            {
                assetItemV2 = this._CollectAllAssetItemList[index];
                this._BuildOneAssetBundleItem(assetItemV2);
            }

            this._OutDetailAssetBundleInfo();

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("_BuildAssetBundleList, end");
            }
        }

        public override void BuildAssetBundleItemInfo()
        {
            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("BuildAssetBundleItemInfo, start");
            }

            this._CollectAllAssetList();
            this._CollectAssetDependency();
            this._BuildAssetBundleItemList();

            if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
            {
                UnityEngine.Debug.Log("BuildAssetBundleItemInfo, end");
            }
        }
    }
}