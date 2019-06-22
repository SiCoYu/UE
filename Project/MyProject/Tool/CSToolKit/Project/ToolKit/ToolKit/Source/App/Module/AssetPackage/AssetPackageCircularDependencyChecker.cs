using System.Collections.Generic;
using System.IO;

namespace ToolSet
{
    public enum CDCUsetData
    {
        eAssetBundleItem = 0,
    }

    public class CDCAssetBundleItemV2
    {
        protected AssetBundleBuildPolicy _AssetBundleBuildPolicy;
        protected string _AssetBundleShortName;
        protected List<string> _AssetPathList;
        protected List<AssetItemV2> _AssetItemList;
        public bool IsCollectedDependency = false;
        public bool IsFindCircularDependency = false;

        public List<CDCAssetBundleItemV2> ChildDependencyList;
        public Dictionary<string, CDCAssetBundleItemV2> AssetPath2ChildAssetDic;
        public List<CDCAssetBundleItemV2> ParentReferenceList;
        public Dictionary<string, CDCAssetBundleItemV2> AssetPath2ParentAssetDic;

        public CDCAssetBundleItemV2()
        {
            this.ChildDependencyList = new List<CDCAssetBundleItemV2>();
            this.AssetPath2ChildAssetDic = new Dictionary<string, CDCAssetBundleItemV2>();
            this.ParentReferenceList = new List<CDCAssetBundleItemV2>();
            this.AssetPath2ParentAssetDic = new Dictionary<string, CDCAssetBundleItemV2>();
            // Item 和 SpriteOutput/StigmataFigures 可能为空，因此为了统一，默认有个一值
            this._AssetItemList = new List<AssetItemV2>();
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
        }

        public int GetChildDepencencyNum()
        {
            return this.ChildDependencyList.Count;
        }

        public int GetParentReferenceNum()
        {
            return this.ParentReferenceList.Count;
        }

        public void AddChild(CDCAssetBundleItemV2 childAssetBundleItem)
        {
            if (!this.AssetPath2ChildAssetDic.ContainsKey(childAssetBundleItem.GetAsbShortName()) &&
                childAssetBundleItem != this)
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("AddChild, Parent {0} , Child {1}", this._AssetBundleShortName, childAssetBundleItem.GetAsbShortName()));
                }

                this.ChildDependencyList.Add(childAssetBundleItem);
                this.AssetPath2ChildAssetDic.Add(childAssetBundleItem.GetAsbShortName(), childAssetBundleItem);
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("AddChild, {0} already exist", childAssetBundleItem.GetAsbShortName()));
                }
            }
        }

        public void AddParent(CDCAssetBundleItemV2 parentAssetBundleItem)
        {
            if (!this.AssetPath2ParentAssetDic.ContainsKey(parentAssetBundleItem.GetAsbShortName()))
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("AddParent, Parent {0} , Child {1}", this._AssetBundleShortName, parentAssetBundleItem.GetAsbShortName()));
                }

                this.ParentReferenceList.Add(parentAssetBundleItem);
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("AddParent, {0} already exist", parentAssetBundleItem.GetAsbShortName()));
                }
            }
        }

        public List<CDCAssetBundleItemV2> GetDependencyList()
        {
            return this.ChildDependencyList;
        }

        public void InitDependency()
        {
            AssetItemV2 assetItem = null;
            AssetItemV2 dependencyAssetItem = null;
            CDCAssetBundleItemV2 dependencyAssetBundleItem = null;

            // Item 和 SpriteOutput/StigmataFigures 这两个可能为空
            if (null != this._AssetItemList)
            {
                for (int aIndex = 0; aIndex < this._AssetItemList.Count; ++aIndex)
                {
                    assetItem = this._AssetItemList[aIndex];

                    for (int bIndex = 0; bIndex < assetItem.ChildDependencyList.Count; ++bIndex)
                    {
                        dependencyAssetItem = assetItem.ChildDependencyList[bIndex];
                        dependencyAssetBundleItem = dependencyAssetItem.GetUserData((int)CDCUsetData.eAssetBundleItem) as CDCAssetBundleItemV2;

                        this.AddChild(dependencyAssetBundleItem);
                    }
                }
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("assetItemlist is null, {0}", this._AssetBundleShortName));
                }
            }
        }

        public void SetAsbShortName(string value)
        {
            this._AssetBundleShortName = value;
        }

        public string GetAsbShortName()
        {
            return this._AssetBundleShortName;
        }

        public List<AssetItemV2> GetAssetItemList()
        {
            return this._AssetItemList;
        }

        public void SetAssetPathList(List<string> assetPathList)
        {
            this._AssetPathList = assetPathList;
        }

        public void SetAssetBundleBuildPolicy(AssetBundleBuildPolicy policy)
        {
            this._AssetBundleBuildPolicy = policy;
        }

        public void InitWithAssetBundleItemV2(AssetBundleItemV2 assetBundleItemV2)
        {
            this._AssetBundleShortName = assetBundleItemV2.GetAsbShortName();
            this._AssetItemList = assetBundleItemV2.AssetItemList;

            for (int index = 0; index < this._AssetItemList.Count; ++index)
            {
                this._AssetItemList[index].AddUserData((int)CDCUsetData.eAssetBundleItem, this);
            }
        }

        public void AddAssetItem(AssetItemV2 assetItemV2)
        {
            if (null == this._AssetItemList)
            {
                this._AssetItemList = new List<AssetItemV2>();
            }

            if (!this._AssetItemList.Contains(assetItemV2))
            {
                this._AssetItemList.Add(assetItemV2);
                assetItemV2.AddUserData((int)CDCUsetData.eAssetBundleItem, this);
            }
            else
            {
                if (AssetPackageUtil.ENABLE_ERROR_LOG)
                {
                    UtilDebug.Log(string.Format("{0} already in {1}", assetItemV2.AssetRelativePathStartWithAssets, this._AssetBundleShortName));
                }
            }
        }

        public string GetMatchPath(AssetItemV2 assetItemV2)
        {
            string ret = "";

            for (int index = 0; index < this._AssetPathList.Count; ++index)
            {
                if(assetItemV2.AssetRelativePathStartWithAssets.Equals(this._AssetPathList[index], System.StringComparison.CurrentCultureIgnoreCase))
                {
                    ret = this._AssetPathList[index];
                    break;
                }
                else if (!AssetPackageUtil.IsSameParentDir(assetItemV2.AssetRelativePathStartWithAssets, this._AssetPathList[index]))
                {
                    if (assetItemV2.AssetRelativePathStartWithAssets.StartsWith(this._AssetPathList[index], System.StringComparison.CurrentCultureIgnoreCase))
                    {
                        ret = this._AssetPathList[index];
                        break;
                    }
                }
            }

            return ret;
        }

        public string GetContentString()
        {
            System.Text.StringBuilder stringBuilder = new System.Text.StringBuilder();
            stringBuilder.Append("AssetBundle\n");
            stringBuilder.Append(this.GetAsbShortName());
            stringBuilder.Append("\n");
            stringBuilder.Append("asset\n");

            if (null != this._AssetItemList)
            {
                for (int index = 0; index < this._AssetItemList.Count; ++index)
                {
                    stringBuilder.Append(this._AssetItemList[index].AssetRelativePathStartWithAssets);
                    stringBuilder.Append("\n");
                }
            }
            else
            {
                if (AssetPackageUtil.ENABLE_ERROR_LOG)
                {
                    UtilDebug.LogError(string.Format("_AssetItemList is null"));
                }
            }

            stringBuilder.Append("\n");

            return stringBuilder.ToString();
        }
    }

    public class CircularDependencyStackItemV2
    {
        public CDCAssetBundleItemV2 FirstAssetBundleItem;
        public CDCAssetBundleItemV2 NextAssetBundleItem;
        public List<string> CircularOrigAssetPathList;
        public List<string> CircularDependencyAssetPathList;

        public CircularDependencyStackItemV2()
        {
            this.CircularOrigAssetPathList = new List<string>();
            this.CircularDependencyAssetPathList = new List<string>();
        }

        public string GetContentString()
        {
            System.Text.StringBuilder stringBuilder = new System.Text.StringBuilder();
            stringBuilder.Append("AssetBundle\n");
            stringBuilder.Append(this.FirstAssetBundleItem.GetAsbShortName());
            stringBuilder.Append("\n");
            stringBuilder.Append(this.NextAssetBundleItem.GetAsbShortName());
            stringBuilder.Append("\n");
            stringBuilder.Append("circular dependency asset\n");

            for (int index = 0; index < this.CircularDependencyAssetPathList.Count; ++index)
            {
                stringBuilder.Append("Asset-");
                stringBuilder.Append(index);
                stringBuilder.Append("\n");
                stringBuilder.Append(this.CircularOrigAssetPathList[index]);
                stringBuilder.Append("\n");
                stringBuilder.Append(this.CircularDependencyAssetPathList[index]);
                stringBuilder.Append("\n");
            }

            return stringBuilder.ToString();
        }
    }

    public class CircularDependencyItemV2
    {
        protected List<CDCAssetBundleItemV2> _CircularDependencyAssetBundleItemList;
        protected List<CircularDependencyStackItemV2> _CircularDependencyAssetPathList;

        public CircularDependencyItemV2()
        {
            this._CircularDependencyAssetBundleItemList = new List<CDCAssetBundleItemV2>();
            this._CircularDependencyAssetPathList = new List<CircularDependencyStackItemV2>();
        }

        public string GetContentString()
        {
            System.Text.StringBuilder stringBuilder = new System.Text.StringBuilder();
            stringBuilder.Append("-------------------------------------------------\n");

            for (int index = 0; index < this._CircularDependencyAssetPathList.Count; ++index)
            {
                stringBuilder.Append("(");
                stringBuilder.Append(index);
                stringBuilder.Append(")");
                stringBuilder.Append("\n");
                stringBuilder.Append(this._CircularDependencyAssetPathList[index].GetContentString());
                stringBuilder.Append("\n");
            }

            return stringBuilder.ToString();
        }

        protected void CalcCircularDependencyAssetPathList(
            List<string> circularOrigAssetPathList,
            List<string> circularDependencyAssetPathList,
            CDCAssetBundleItemV2 firstAssetBundleItem, 
            CDCAssetBundleItemV2 nextAssetBundleItem
            )
        {
            List<AssetItemV2> firstAssetItemList = firstAssetBundleItem.GetAssetItemList();
            List<AssetItemV2> nextAssetItemList = nextAssetBundleItem.GetAssetItemList();
            List<AssetItemV2> nextAssetItemDependencyList = null;

            for (int aIndex = 0; aIndex < nextAssetItemList.Count; ++aIndex)
            {
                for (int bIndex = 0; bIndex < firstAssetItemList.Count; ++bIndex)
                {
                    nextAssetItemDependencyList = firstAssetItemList[bIndex].ChildDependencyList;

                    for (int cIndex = 0; cIndex < nextAssetItemDependencyList.Count; ++cIndex)
                    {
                        if (nextAssetItemList[aIndex].AssetRelativePathStartWithAssets == nextAssetItemDependencyList[cIndex].AssetRelativePathStartWithAssets)
                        {
                            if (!circularDependencyAssetPathList.Contains(nextAssetItemList[aIndex].AssetRelativePathStartWithAssets))
                            {
                                circularDependencyAssetPathList.Add(nextAssetItemList[aIndex].AssetRelativePathStartWithAssets);

                                //if (!circularOrigAssetPathList.Contains(firstAssetItemList[bIndex].AssetRelativePathStartWithAssets))
                                //{
                                // circularDependencyAssetPathList 添加， circularOrigAssetPathList 必须也添加，一个资源依赖多个资源
                                circularOrigAssetPathList.Add(firstAssetItemList[bIndex].AssetRelativePathStartWithAssets);
                                //}
                                //else
                                //{
                                //    if (AssetPackageUtil.ENABLE_ERROR_LOG)
                                //    {
                                //        UtilDebug.LogError(string.Format("error already exist orig"));
                                //    }
                                //}
                            }
                            else
                            {
                                if (AssetPackageUtil.ENABLE_ERROR_LOG)
                                {
                                    //UtilDebug.LogError(string.Format("error already exist"));
                                    UtilDebug.Log(string.Format("error already exist"));
                                }
                            }
                        }
                    }
                }
            }
        }

        protected void _FindCircularDependencyAssetPath()
        {
            if (this._CircularDependencyAssetBundleItemList.Count >= 2)
            {
                CDCAssetBundleItemV2 firstAssetBundleItem = null;
                CDCAssetBundleItemV2 nextAssetBundleItem = null;

                CircularDependencyStackItemV2 circularDependencyStackItem = null;

                for (int index = 0; index < this._CircularDependencyAssetBundleItemList.Count - 1; ++index)
                {
                    circularDependencyStackItem = new CircularDependencyStackItemV2();
                    this._CircularDependencyAssetPathList.Add(circularDependencyStackItem);

                    firstAssetBundleItem = this._CircularDependencyAssetBundleItemList[index];
                    nextAssetBundleItem = this._CircularDependencyAssetBundleItemList[index + 1];

                    circularDependencyStackItem.FirstAssetBundleItem = firstAssetBundleItem;
                    circularDependencyStackItem.NextAssetBundleItem = nextAssetBundleItem;

                    this.CalcCircularDependencyAssetPathList(
                        circularDependencyStackItem.CircularOrigAssetPathList,
                        circularDependencyStackItem.CircularDependencyAssetPathList,
                        firstAssetBundleItem, 
                        nextAssetBundleItem
                        );
                }

                circularDependencyStackItem = new CircularDependencyStackItemV2();
                this._CircularDependencyAssetPathList.Add(circularDependencyStackItem);

                firstAssetBundleItem = this._CircularDependencyAssetBundleItemList[this._CircularDependencyAssetBundleItemList.Count - 1];
                nextAssetBundleItem = this._CircularDependencyAssetBundleItemList[0];

                circularDependencyStackItem.FirstAssetBundleItem = firstAssetBundleItem;
                circularDependencyStackItem.NextAssetBundleItem = nextAssetBundleItem;

                this.CalcCircularDependencyAssetPathList(
                    circularDependencyStackItem.CircularOrigAssetPathList,
                    circularDependencyStackItem.CircularDependencyAssetPathList,
                    firstAssetBundleItem, 
                    nextAssetBundleItem
                    );
            }
            else
            {
                if (AssetPackageUtil.ENABLE_ERROR_LOG)
                {
                    UtilDebug.LogError(string.Format("error < 2"));
                }
            }
        }

        public void AddCircularDependencyFirstAssetBundleItem(CDCAssetBundleItemV2 firstAssetBundleItem, Stack<CDCAssetBundleItemV2> stack)
        {
            CDCAssetBundleItemV2[] array = stack.ToArray();
            bool isFind = false;

            // 堆栈 0 索引最后入栈的， 因此需要逆序
            for (int index = array.Length - 1; index >= 0; --index)
            {
                if (array[index] == firstAssetBundleItem)
                {
                    isFind = true;
                    this._CircularDependencyAssetBundleItemList.Clear();
                }

                if (isFind)
                {
                    this._CircularDependencyAssetBundleItemList.Add(array[index]);
                }
            }

            this._FindCircularDependencyAssetPath();
        }
    }

    /**
     * @brief 循环依赖检查， CDC CircularDependencyChecker
     */
    public class CircularDependencyChecker
    {
        // 所有的资源列表
        protected List<AssetItemV2> _CollectAllAssetItemList;
        protected List<AssetItemV2> _FolderPolicyAssetItemList;
        protected List<AssetItemV2> _SingleDependencyAssetItemList;
        // Path 到资源的映射
        protected Dictionary<string, AssetItemV2> _CollectAssetPath2AssetDic;
        // CDCAssetBundleItemV2 列表
        protected List<CDCAssetBundleItemV2> _AllAssetBundleItemList;
        protected List<CDCAssetBundleItemV2> _FolderPolicyAssetBundleItemList;
        protected List<CDCAssetBundleItemV2> _SingleDependencyAssetBundleItemList;
        // 基本数据
        protected AssetPackageGraphSingleDependency _AssetBuildContext;

        protected List<CircularDependencyItemV2> _CircularDependencyItemList;

        public CircularDependencyChecker()
        {
            this._AllAssetBundleItemList = new List<CDCAssetBundleItemV2>();
            this._FolderPolicyAssetBundleItemList = new List<CDCAssetBundleItemV2>();
            this._SingleDependencyAssetBundleItemList = new List<CDCAssetBundleItemV2>();
            this._CircularDependencyItemList = new List<CircularDependencyItemV2>();
        }

        public void Init()
        {

        }

        public void Dispose()
        {
            this._CollectAllAssetItemList.Clear();
            this._CollectAllAssetItemList = null;
            this._FolderPolicyAssetItemList.Clear();
            this._FolderPolicyAssetItemList = null;
            this._SingleDependencyAssetItemList.Clear();
            this._SingleDependencyAssetItemList = null;
            this._CollectAssetPath2AssetDic.Clear();
            this._CollectAssetPath2AssetDic = null;
            this._AllAssetBundleItemList.Clear();
            this._AllAssetBundleItemList = null;
            this._FolderPolicyAssetBundleItemList.Clear();
            this._FolderPolicyAssetBundleItemList = null;
            this._SingleDependencyAssetBundleItemList.Clear();
            this._SingleDependencyAssetBundleItemList = null;
            this._AssetBuildContext.Dispose();
            this._AssetBuildContext = null;
            this._CircularDependencyItemList.Clear();
            this._CircularDependencyItemList = null;
        }

        public void _WriteCircularDependencyManifest(string fileName)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteCircularDependencyManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetPackageUtil.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "CircularDependencyManifest");
            }

            using (var writer = new StreamWriter(fileName))
            {
                string line = string.Format("total {0}", this._CircularDependencyItemList.Count);
                writer.WriteLine(line);
                writer.WriteLine();

                for (int index = 0; index < this._CircularDependencyItemList.Count; ++index)
                {
                    writer.WriteLine(this._CircularDependencyItemList[index].GetContentString());
                    writer.WriteLine();
                }
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteCircularDependencyManifest, end"));
            }
        }

        public void _WriteCircularDependencyAssetBundleManifest(string fileName)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteCircularDependencyAssetBundleManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetPackageUtil.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "CircularDependencyAssetBundleManifest");
            }

            using (var writer = new StreamWriter(fileName))
            {
                string line = string.Format("total {0}", this._AllAssetBundleItemList.Count);
                writer.WriteLine(line);
                writer.WriteLine();

                for (int index = 0; index < this._AllAssetBundleItemList.Count; ++index)
                {
                    writer.WriteLine(this._AllAssetBundleItemList[index].GetContentString());
                    writer.WriteLine();
                }
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteCircularDependencyAssetBundleManifest, end"));
            }
        }

        protected void _InitAssetEntity()
        {
            
        }

        protected bool _IsCircularDependency(CDCAssetBundleItemV2 assetBundleItem, Stack<CDCAssetBundleItemV2> stack)
        {
            bool ret = false;

            ret = stack.Contains(assetBundleItem);

            return ret;
        }

        protected void _CollectAllAssetAndDependencyList()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_CollectAllAssetAndDependencyList, start"));
            }

            string rootPath = "Assets/AsbRes";
            this._AssetBuildContext = new AssetPackageGraphSingleDependency();
            this._AssetBuildContext.AddCollectRootPath(rootPath);
            this._AssetBuildContext.AddExcludeAssetBundleFileExtName("meta");
            this._AssetBuildContext.AddExcludeAssetBundleFileExtName("DS_Store");

            //string path = "";

            //if (null != this._SingleDependencyAssetEntity)
            //{
            //    for (int index = 0; index < this._SingleDependencyAssetEntity.assetPathList.Count; ++index)
            //    {
            //        path = this._SingleDependencyAssetEntity.assetPathList[index];

            //        if (Directory.Exists(path))
            //        {
            //            this._AssetBuildContext.AddIncludeAssetBundlePath(path);
            //        }
            //        else
            //        {
            //            // 只支持顶级目录设置
            //            UtilDebug.LogError(string.Format("BuildAssetEntityBySingleDependencyPolicy, error, {0} is file", path));
            //        }
            //    }
            //}

            this._AssetBuildContext.OutAssetManifest();

            this._CollectAllAssetItemList = this._AssetBuildContext.GetAllAssetItemList();
            this._SingleDependencyAssetItemList = this._AssetBuildContext.GetIncludeAssetItemList();
            this._FolderPolicyAssetItemList = this._AssetBuildContext.GetExcludeAssetItemList();
            this._CollectAssetPath2AssetDic = this._AssetBuildContext.GetAssetPath2AssetDic();

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_CollectAllAssetAndDependencyList, end"));
            }
        }

        protected void _AddOneAssetItemToFolderPolicyAssetBundleItem(AssetItemV2 assetItem)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_AddOneAssetItemToFolderPolicyAssetBundleItem, start"));
            }

            CDCAssetBundleItemV2 curAssetBundleItem = null;
            CDCAssetBundleItemV2 bestMatchAssetBundleItem = null;
            string curMatchPath = "";
            string bestMatchPath = "";

            for (int index = 0; index < this._FolderPolicyAssetBundleItemList.Count; ++index)
            {
                curAssetBundleItem = this._FolderPolicyAssetBundleItemList[index];
                curMatchPath = curAssetBundleItem.GetMatchPath(assetItem);

                if (bestMatchPath.Length < curMatchPath.Length)
                {
                    bestMatchPath = curMatchPath;
                    bestMatchAssetBundleItem = curAssetBundleItem;
                }
            }

            if (null != bestMatchAssetBundleItem)
            {
                bestMatchAssetBundleItem.AddAssetItem(assetItem);

                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("{0} addto {1}", assetItem.AssetRelativePathStartWithAssets, bestMatchAssetBundleItem.GetAsbShortName()));
                }
            }
            else
            {
                if (AssetPackageUtil.ENABLE_ERROR_LOG)
                {
                    UtilDebug.LogError(string.Format("{0} not find assetbundleitem", assetItem.AssetRelativePathStartWithAssets));
                }
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_AddOneAssetItemToFolderPolicyAssetBundleItem, end"));
            }
        }

        protected void _FindAssetBundleItemDependency(CDCAssetBundleItemV2 assetBundleItem)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_FindAssetBundleItemDependency, start"));
            }

            Stack<CDCAssetBundleItemV2> stack = new Stack<CDCAssetBundleItemV2>();
            this._DepthFirstFindAssetBundleItemDependency(assetBundleItem, stack);
            stack.Clear();

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_FindAssetBundleItemDependency, end"));
            }
        }

        protected void _AddOneCircularDependency(CDCAssetBundleItemV2 assetBundleItem, Stack<CDCAssetBundleItemV2> stack)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_AddOneCircularDependency, start");
            }

            CircularDependencyItemV2 item = new CircularDependencyItemV2();
            this._CircularDependencyItemList.Add(item);
            item.AddCircularDependencyFirstAssetBundleItem(assetBundleItem, stack);

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_AddOneCircularDependency, end");
            }
        }

        protected void _DepthFirstFindAssetBundleItemDependency(CDCAssetBundleItemV2 assetBundleItem, Stack<CDCAssetBundleItemV2> stack)
        {
            // 循环依赖检测
            //if (this._IsCircularDependency(assetBundleItem, stack))
            //{
            //    if (AssetPackageUtil.ENABLE_ERROR_LOG)
            //    {
            //        UtilDebug.LogError(string.Format("_DepthFirstFindDependency, CircularDependency {0}", assetBundleItem.GetAsbShortName()));
            //    }
            //}

            if (!assetBundleItem.IsCollectedDependency)
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("_DepthFirstFindAssetBundleItemDependency, {0}", assetBundleItem.GetAsbShortName()));
                }

                stack.Push(assetBundleItem);

                assetBundleItem.IsCollectedDependency = true;
                assetBundleItem.InitDependency();

                List<CDCAssetBundleItemV2> dependencyArray = assetBundleItem.GetDependencyList();
                CDCAssetBundleItemV2 depencyAssetBundleItem = null;

                for (int index = 0; index < dependencyArray.Count; ++index)
                {
                    depencyAssetBundleItem = dependencyArray[index];

                    if (assetBundleItem != depencyAssetBundleItem)
                    {
                        assetBundleItem.AddChild(depencyAssetBundleItem);
                        depencyAssetBundleItem.AddParent(assetBundleItem);
                        this._DepthFirstFindAssetBundleItemDependency(depencyAssetBundleItem, stack);
                    }
                    else
                    {
                        if (AssetPackageUtil.ENABLE_ERROR_LOG)
                        {
                            UtilDebug.LogError(string.Format("_DepthFirstFindAssetBundleItemDependency, {0} same dependency", dependencyArray[index].GetAsbShortName()));
                        }
                    }
                }

                CDCAssetBundleItemV2 assetBundleItemPop = stack.Pop();
                UtilDebug.Assert(assetBundleItemPop == assetBundleItem);
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_DepthFirstFindAssetBundleItemDependency, end");
            }
        }

        protected void _DepthFirstBuildOneAssetBundleItem(CDCAssetBundleItemV2 assetBundleItemV2, Stack<CDCAssetBundleItemV2> stack)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_DepthFirstBuildOneAssetBundleItem, start");
            }

            // 循环依赖检测
            if (this._IsCircularDependency(assetBundleItemV2, stack))
            {
                if (AssetPackageUtil.ENABLE_ERROR_LOG)
                {
                    //UtilDebug.LogError(string.Format("_DepthFirstFindDependency, CircularDependency {0}", assetBundleItemV2.GetAsbShortName()));
                }

                this._AddOneCircularDependency(assetBundleItemV2, stack);
            }

            if (!assetBundleItemV2.IsFindCircularDependency)
            {
                stack.Push(assetBundleItemV2);
                // 循环依赖成环，只要任意访问一个资源，就能检查是否循环依赖
                assetBundleItemV2.IsFindCircularDependency = true;

                CDCAssetBundleItemV2 dependencyAssetBundleItemV2 = null;

                for (int index = 0; index < assetBundleItemV2.ChildDependencyList.Count; ++index)
                {
                    dependencyAssetBundleItemV2 = assetBundleItemV2.ChildDependencyList[index];
                    this._DepthFirstBuildOneAssetBundleItem(dependencyAssetBundleItemV2, stack);
                }

                CDCAssetBundleItemV2 assetBundleItemPop = stack.Pop();
                UtilDebug.Assert(assetBundleItemPop == assetBundleItemV2);
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_DepthFirstBuildOneAssetBundleItem, end");
            }
        }

        protected virtual void _FindOneAssetBundleItemCircularDependency(CDCAssetBundleItemV2 assetBundleItem)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_FindOneAssetBundleItemCircularDependency, start");
            }

            if (!assetBundleItem.IsFindCircularDependency)
            {
                Stack<CDCAssetBundleItemV2> stack = new Stack<CDCAssetBundleItemV2>();
                this._DepthFirstBuildOneAssetBundleItem(assetBundleItem, stack);
                stack.Clear();
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_FindOneAssetBundleItemCircularDependency, end");
            }
        }

        private void _CheckIfAssetUniqueInAssetBundle()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_CheckIfAssetUniqueInAssetBundle, start");
            }

            Dictionary<string, AssetItemV2> uniqueAssetCheckerDic = new Dictionary<string, AssetItemV2>();
            CDCAssetBundleItemV2 curAssetBundleItem = null;
            List<AssetItemV2> curAssetItemList = null;
            AssetItemV2 assetItem = null;
            int totalFile = 0;

            for (int aIndex = 0; aIndex < this._AllAssetBundleItemList.Count; ++aIndex)
            {
                if (!this._AllAssetBundleItemList[aIndex].IsFindCircularDependency)
                {
                    if (AssetPackageUtil.ENABLE_ERROR_LOG)
                    {
                        UtilDebug.LogError(string.Format("{0} not FindCircularDependency", this._AllAssetBundleItemList[aIndex].GetAsbShortName()));
                    }
                }

                curAssetBundleItem = this._AllAssetBundleItemList[aIndex];
                curAssetItemList = curAssetBundleItem.GetAssetItemList();

                if (null != curAssetItemList)
                {
                    for (int bIndex = 0; bIndex < curAssetItemList.Count; ++bIndex)
                    {
                        assetItem = curAssetItemList[bIndex];

                        if (!uniqueAssetCheckerDic.ContainsKey(assetItem.AssetRelativePathStartWithAssets))
                        {
                            uniqueAssetCheckerDic.Add(assetItem.AssetRelativePathStartWithAssets, assetItem);
                        }
                        else
                        {
                            if (AssetPackageUtil.ENABLE_ERROR_LOG)
                            {
                                UtilDebug.LogError(string.Format("{0} in diff assetbundle", assetItem.AssetRelativePathStartWithAssets));
                            }
                        }

                        ++totalFile;
                    }
                }
                else
                {
                    if (AssetPackageUtil.ENABLE_ERROR_LOG)
                    {
                        UtilDebug.LogError(string.Format("{0} is null", curAssetBundleItem.GetAsbShortName()));
                    }
                }
            }

            if (totalFile != this._CollectAllAssetItemList.Count)
            {
                if (AssetPackageUtil.ENABLE_ERROR_LOG)
                {
                    UtilDebug.LogError(string.Format("{0} not equal {1}", totalFile, this._CollectAllAssetItemList.Count));
                }
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_CheckIfAssetUniqueInAssetBundle, end");
            }
        }

        protected void _BuildAssetBundleItemList()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_BuildAssetBundleItemList, start");
            }

            CDCAssetBundleItemV2 cdcAssetBundleItemV2 = null;

            // 生成 SingleDependency
            List<AssetBundleItemV2> list = this._AssetBuildContext.GetAssetBundleItemList();

            for (int index = 0; index < list.Count; ++index)
            {
                cdcAssetBundleItemV2 = new CDCAssetBundleItemV2();
                this._AllAssetBundleItemList.Add(cdcAssetBundleItemV2);
                this._SingleDependencyAssetBundleItemList.Add(cdcAssetBundleItemV2);
                cdcAssetBundleItemV2.SetAssetBundleBuildPolicy(AssetBundleBuildPolicy.eSingleDependency);
                cdcAssetBundleItemV2.InitWithAssetBundleItemV2(list[index]);
            }

            // 生成 Folder
            //for (int index = 0; index < this._AssetBundleEntryList.Count; ++index)
            //{
            //    cdcAssetBundleItemV2 = new CDCAssetBundleItemV2();
            //    this._AllAssetBundleItemList.Add(cdcAssetBundleItemV2);
            //    this._FolderPolicyAssetBundleItemList.Add(cdcAssetBundleItemV2);
            //    cdcAssetBundleItemV2.SetAssetBundleBuildPolicy(AssetBundleBuildPolicy.eFolder);
            //    cdcAssetBundleItemV2.SetAsbShortName(this._AssetBundleEntryList[index].name);
            //    cdcAssetBundleItemV2.SetAssetPathList(this._AssetBundleEntryList[index].assetPathList);
            //}

            // 遍历 Folder Policy
            for (int index = 0; index < this._FolderPolicyAssetItemList.Count; ++index)
            {
                this._AddOneAssetItemToFolderPolicyAssetBundleItem(this._FolderPolicyAssetItemList[index]);
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_BuildAssetBundleItemList, end");
            }
        }

        protected void _CollectAssetBundleItemDependency()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_CollectAssetBundleItemDependency, start");
            }

            CDCAssetBundleItemV2 assetBundleItem = null;
            int listLen = this._AllAssetBundleItemList.Count;
            int index = 0;

            for (; index < listLen; ++index)
            {
                assetBundleItem = this._AllAssetBundleItemList[index];
                this._FindAssetBundleItemDependency(assetBundleItem);
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_CollectAssetBundleItemDependency, end");
            }
        }

        protected void _CheckAssetBundleItemIsValid()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_CheckAssetBundleItemIsValid, start");
            }

            CDCAssetBundleItemV2 assetBundleItemV2 = null;

            for (int index = 0; index < this._AllAssetBundleItemList.Count; ++index)
            {
                assetBundleItemV2 = this._AllAssetBundleItemList[index];

                if (null == assetBundleItemV2.GetAssetItemList())
                {
                    if (AssetPackageUtil.ENABLE_ERROR_LOG)
                    {
                        UtilDebug.Log(string.Format("{0} error", assetBundleItemV2.GetAsbShortName()));
                    }
                }
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_CheckAssetBundleItemIsValid, end");
            }
        }

        protected virtual void _FindAssetBundleItemCircularDependency()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_FindAssetBundleItemCircularDependency, start");
            }

            CDCAssetBundleItemV2 assetBundleItemV2 = null;

            for (int index = 0; index < this._AllAssetBundleItemList.Count; ++index)
            {
                assetBundleItemV2 = this._AllAssetBundleItemList[index];

                if (0 == assetBundleItemV2.GetParentReferenceNum())
                {
                    this._FindOneAssetBundleItemCircularDependency(assetBundleItemV2);
                }
            }

            // 有些资源顶层就存在循环依赖，再次遍历
            for (int index = 0; index < this._AllAssetBundleItemList.Count; ++index)
            {
                assetBundleItemV2 = this._AllAssetBundleItemList[index];
                // 遍历顶层就存在循环引用的
                if (0 != assetBundleItemV2.GetParentReferenceNum())
                {
                    this._FindOneAssetBundleItemCircularDependency(assetBundleItemV2);
                }
            }

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_FindAssetBundleItemCircularDependency, end");
            }
        }

        private void _CheckAssetCorrect()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_CheckAssetCorrect, start");
            }

            this._CheckIfAssetUniqueInAssetBundle();

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_CheckAssetCorrect, end");
            }
        }

        private void _WriteManifest()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_WriteManifest, start");
            }

            this._WriteCircularDependencyManifest("");
            this._WriteCircularDependencyAssetBundleManifest("");

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("_WriteManifest, end");
            }
        }

        public void CheckCircularDependency()
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("CheckCircularDependency, start");
            }

            this._InitAssetEntity();
            this._CollectAllAssetAndDependencyList();
            this._BuildAssetBundleItemList();
            this._CollectAssetBundleItemDependency();
            this._CheckAssetBundleItemIsValid();
            this._FindAssetBundleItemCircularDependency();
            this._CheckAssetCorrect();
            this._WriteManifest();

            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log("CheckCircularDependency, end");
            }
        }
    }
}