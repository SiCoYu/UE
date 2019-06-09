using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;

namespace ToolSet
{
    /**
     * @brief AssetBundle 打包
     */
    public static class AssetBundleBuilderUtilV2
    {
        public const bool ENABLE_COMMON_LOG = false;
        public const bool ENABLE_ERROR_LOG = true;
        public const bool ENABLE_PROFILE_LOG = false;

        public static string GetOrCreateAssetManifestDirectory(bool isCreateDirectory = true)
        {
            string rootPath = Application.dataPath;
            rootPath = rootPath.Replace("\\", "/");
            rootPath = rootPath.Substring(0, Application.dataPath.IndexOf("/Asset"));
            string outputPath = string.Format("{0}/Output/AssetBundlesV2/Windows", rootPath);

            if (isCreateDirectory)
            {
                if (!Directory.Exists(outputPath))
                {
                    try
                    {
                        Directory.CreateDirectory(outputPath);

                        if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                        {
                            UnityEngine.Debug.Log(string.Format("_GetAssetDependencyManifestFullFileName, create directory {0}", outputPath));
                        }
                    }
                    catch (System.Exception exp)
                    {
                        if (AssetBundleBuilderUtilV2.ENABLE_ERROR_LOG)
                        {
                            UnityEngine.Debug.LogError(string.Format("_GetAssetDependencyManifestFullFileName, create error {0}", exp.Message));
                        }
                    }
                }
                else
                {
                    if (AssetBundleBuilderUtilV2.ENABLE_COMMON_LOG)
                    {
                        UnityEngine.Debug.Log(string.Format("_GetAssetDependencyManifestFullFileName, {0} directory exist", outputPath));
                    }
                }
            }

            return outputPath;
        }

        public static void TraverseDir(string baseDir, bool isRecursive, System.Action<string> handle)
        {
            if (Directory.Exists(baseDir))
            {
                DirectoryInfo dirInfo = new DirectoryInfo(baseDir);
                FileInfo[] fileInfoArray = dirInfo.GetFiles();

                if (null != handle)
                {
                    for (int index = 0; index < fileInfoArray.Length; ++index)
                    {
                        handle(fileInfoArray[index].FullName);
                    }
                }

                if (isRecursive)
                {
                    DirectoryInfo[] subDirArray = dirInfo.GetDirectories();
                    for (int index = 0; index < subDirArray.Length; ++index)
                    {
                        AssetBundleBuilderUtilV2.TraverseDir(subDirArray[index].FullName, isRecursive, handle);
                    }
                }
            }
        }

        public static string NormalPath(string filePath)
        {
            filePath = filePath.Replace("\\", "/");
            return filePath;
        }

        public static string GetRelativePathStartWithAsset(string fullPath)
        {
            fullPath = AssetBundleBuilderUtilV2.NormalPath(fullPath);
            int index = fullPath.IndexOf("Asset");
            return fullPath.Substring(index);
        }

        public static string GetFileExtName(string fullPath)
        {
            int index = fullPath.LastIndexOf(".");
            string extName = "";

            if (-1 != index)
            {
                extName = fullPath.Substring(index + 1);
            }

            return extName;
        }

        public static string GetFileNameNoExt(string fullPath)
        {
            int index = fullPath.LastIndexOf(".");
            if (-1 != index)
            {
                fullPath = fullPath.Substring(0, index);
            }
            return fullPath;
        }

        public static string GetFileNameNoPathAndExt(string fullPath)
        {
            fullPath = AssetBundleBuilderUtilV2.NormalPath(fullPath);
            int index = fullPath.LastIndexOf(".");
            string ret = fullPath;

            if (-1 != index)
            {
                ret = fullPath.Substring(0, index);
            }

            index = ret.LastIndexOf("/");
            if (-1 != index)
            {
                ret = ret.Substring(index + 1);
            }

            return ret;
        }

        public static string GetFilePathNoFileName(string fullPath)
        {
            fullPath = AssetBundleBuilderUtilV2.NormalPath(fullPath);
            int index = fullPath.LastIndexOf("/");
            string ret = "";

            if (-1 != index)
            {
                ret = fullPath.Substring(0, index);
            }

            return ret;
        }

        public static bool HasSpceInPath(string filePath)
        {
            bool ret = false;

            if (!string.IsNullOrEmpty(filePath))
            {
                for (int index = 0; index < filePath.Length; ++index)
                {
                    if (filePath[index] == ' ')
                    {
                        ret = true;
                        break;
                    }
                }
            }

            return ret;
        }

        public static int GetAssetBundleFilePathLengthByFilePath(string filePath)
        {
            string filePathNoFileName = AssetBundleBuilderUtilV2.GetFilePathNoFileName(filePath);
            string fileNameNoExtName = AssetBundleBuilderUtilV2.GetFileNameNoPathAndExt(filePath);
            string fileExtName = AssetBundleBuilderUtilV2.GetFileExtName(filePath);
            int assetBundleFileNameLen = 0;

            if (string.IsNullOrEmpty(fileExtName))
            {
                assetBundleFileNameLen = filePathNoFileName.Length + "/".Length + fileNameNoExtName.Length + "_".Length + 32 + ".unity3d".Length;
            }
            else
            {
                assetBundleFileNameLen = filePathNoFileName.Length + "/".Length + fileNameNoExtName.Length + "_".Length + fileExtName.Length + "_".Length + 32 + ".unity3d".Length;
            }

            return assetBundleFileNameLen;
        }

        public static int GetAssetBundleFileNameLengthByFilePath(string filePath)
        {
            string fileNameNoExtName = AssetBundleBuilderUtilV2.GetFileNameNoPathAndExt(filePath);
            string fileExtName = AssetBundleBuilderUtilV2.GetFileExtName(filePath);
            int assetBundleFileNameLen = 0;

            if (string.IsNullOrEmpty(fileExtName))
            {
                assetBundleFileNameLen = fileNameNoExtName.Length + "_".Length + 32 + ".unity3d".Length;
            }
            else
            {
                assetBundleFileNameLen = fileNameNoExtName.Length + "_".Length + fileExtName.Length + "_".Length + 32 + ".unity3d".Length;
            }

            return assetBundleFileNameLen;
        }

        public static int GetAssetBundleFileNameLength(string fileNameNoExtName, string fileExtName)
        {
            int assetBundleFileNameLen = 0;

            if (string.IsNullOrEmpty(fileExtName))
            {
                assetBundleFileNameLen = fileNameNoExtName.Length + "_".Length + 32 + ".unity3d".Length;
            }
            else
            {
                assetBundleFileNameLen = fileNameNoExtName.Length + "_".Length + fileExtName.Length + "_".Length + 32 + ".unity3d".Length;
            }

            return assetBundleFileNameLen;
        }

        public static bool IsSameParentDir(string aPath, string bPath)
        {
            bool ret = false;

            string aParent = AssetBundleBuilderUtilV2.GetFilePathNoFileName(aPath);
            string bParent = AssetBundleBuilderUtilV2.GetFilePathNoFileName(bPath);
            ret = aParent.Equals(bParent, System.StringComparison.CurrentCultureIgnoreCase);

            return ret;
        }

        public static string GetFullPathFromSeparate(string pathNoFileName, string fileNameNoExt, string extName)
        {
            System.Text.StringBuilder ret = new System.Text.StringBuilder();

            if (string.IsNullOrEmpty(pathNoFileName) ||
                string.IsNullOrEmpty(fileNameNoExt))
            {
                UnityEngine.Debug.LogError(string.Format("pathNoFileName or fileNameNoExt or extName is null"));
            }
            else
            {
                ret.Append(pathNoFileName);
                ret.Append("/");
                ret.Append(fileNameNoExt);
                if (!string.IsNullOrEmpty(extName))
                {
                    ret.Append(".");
                    ret.Append(extName);
                }
            }

            return ret.ToString();
        }

        public static string ReplaceExtNameToAssetBundle(string assetPath)
        {
            string assetBundlePath = AssetBundleBuilderUtilV2.GetFileNameNoExt(assetPath) + ".unity3d";
            return assetBundlePath;
        }

        public static string ChangeExtNameDotToUnderlineAndAddAssetBundleExt(string assetPath)
        {
            string fileExtName = AssetBundleBuilderUtilV2.GetFileExtName(assetPath);
            string fileNameNoExtName = AssetBundleBuilderUtilV2.GetFileNameNoExt(assetPath);
            string assetBundlePath = "";;

            if (string.IsNullOrEmpty(fileExtName))
            {
                assetBundlePath = string.Format("{0}.unity3d", fileNameNoExtName);
            }
            else
            {
                assetBundlePath = string.Format("{0}_{1}.unity3d", fileNameNoExtName, fileExtName);
            }

            return assetBundlePath;
        }

        public static string GetAsbShortName(string assetPath)
        {
            string fileExtName = AssetBundleBuilderUtilV2.GetFileExtName(assetPath);
            string fileNameNoExtName = AssetBundleBuilderUtilV2.GetFileNameNoExt(assetPath);
            fileNameNoExtName = fileNameNoExtName.Substring(AssetBundleBuilderUtilV2.ASB_RES_PATH_SLASH.Length);
            string asbShortName = "";

            if (string.IsNullOrEmpty(fileExtName))
            {
                asbShortName = fileNameNoExtName;
            }
            else
            {
                asbShortName = string.Format("{0}_{1}", fileNameNoExtName, fileExtName);
            }

            return asbShortName;
        }

        public static string GetFullPathByRelativePathStartWithAsset(string relativeAssetPathWithAsset)
        {
            UnityEngine.Debug.Assert(0 == relativeAssetPathWithAsset.IndexOf("Asset"), "GetFullPathByRelativePathWithAsset, name error");
            string fullPathBeforeAsset = Application.dataPath;
            fullPathBeforeAsset = fullPathBeforeAsset.Replace("\\", "/");
            fullPathBeforeAsset = fullPathBeforeAsset.Substring(0, fullPathBeforeAsset.LastIndexOf("/Asset"));
            return string.Format("{0}/{1}", fullPathBeforeAsset, relativeAssetPathWithAsset);
        }

        public static void BuildAssetEntityBySingleDependencyPolicy(List<StreamingAssetBundleEntry> assetEntryList, StreamingAssetBundleEntry assetEntity)
        {
            if (null != assetEntity)
            {
                List<string> assetNameList = new List<string>();
                StreamingAssetBundleEntry addEntity = null;
                AssetBundleItemV2 assetBundleItem = null;
                string path = "";
                AssetBundleBuilderSingleDependencyContextV2 assetBuildContext = new AssetBundleBuilderSingleDependencyContextV2();
                assetBuildContext.AddCollectRootPath("Assets/AsbRes");
                assetBuildContext.AddExcludeAssetBundleFileExtName("meta");
                assetBuildContext.AddExcludeAssetBundleFileExtName("DS_Store");

                for (int index = 0; index < assetEntity.assetPathList.Count; ++index)
                {
                    path = assetEntity.assetPathList[index];

                    if (Directory.Exists(path))
                    {
                        assetBuildContext.AddIncludeAssetBundlePath(path);
                    }
                    else
                    {
                        // 只支持顶级目录设置
                        UnityEngine.Debug.LogError(string.Format("BuildAssetEntityBySingleDependencyPolicy, error, {0} is file", path));
                    }
                }

                assetBuildContext.BuildAssetBundleItemInfo();
                List<AssetBundleItemV2> assetBundleItemList = assetBuildContext.GetAssetBundleItemList();

                for (int indexY = 0; indexY < assetBundleItemList.Count; ++indexY)
                {
                    assetBundleItem = assetBundleItemList[indexY];

                    addEntity = new StreamingAssetBundleEntry();
                    addEntity.name = assetBundleItem.GetAsbShortName();
                    addEntity.unloadMode = assetEntity.unloadMode;
                    addEntity.downloadMode = assetEntity.downloadMode;
                    addEntity.patterns = assetEntity.patterns;
                    addEntity.dontExtractShared = assetEntity.dontExtractShared;
                    //addEntity.markForCheck = assetEntity.markForCheck;

                    assetBundleItem = assetBundleItemList[indexY];
                    addEntity.assetPathList = assetBundleItem.GetAssetNameList();

                    assetEntryList.Add(addEntity);
                }

                assetBuildContext.Dispose();
                assetBuildContext = null;
            }
        }

        public static bool IsSingleDependencyPolicy(string name, List<string> assetEntryList)
        {
            bool ret = false;

            for (int index = 0; index < assetEntryList.Count; ++index)
            {
                if (0 == name.IndexOf(assetEntryList[index]))
                {
                    ret = true;
                    break;
                }
            }

            return ret;
        }

        public static void PreProcessAssetEntityByNewPolicy(List<StreamingAssetBundleEntry> assetEntryList, ref StreamingAssetBundleEntry outAssetBundleEntity)
        {
            //List<string> nameList = new List<string>();
            //nameList.Add("Stage/Stage_Sakura_Streaming");
            //nameList.Add("Stage/Stage_Memory_Sakura");
            //nameList.Add("Stage/Stage_Memory_Sakura_Castle");
            //nameList.Add("_shared/");
            //nameList.Add("Effect/");

            List<string> collectPathList = new List<string>();
            //collectPathList.Add("Assets/AsbRes/Stage/Stage_Sakura_Streaming");
            //collectPathList.Add("Assets/AsbRes/Stage/Stage_Memory_Sakura");
            //collectPathList.Add("Assets/AsbRes/Stage/Stage_Memory_Sakura_Castle");
            //collectPathList.Add("Assets/AsbRes/_shared");
            //collectPathList.Add("Assets/AsbRes/Effect");

            StreamingAssetBundleEntry assetBundleEntity = null;
            StreamingAssetBundleEntry curAssetBundleEntity = null;

            for (int index = assetEntryList.Count - 1; index >= 0; --index)
            {
                curAssetBundleEntity = assetEntryList[index];

                // eSingleDependency 策略打包
#if USE_NEW_ASSETSYSTEM
                if (AssetBundleBuildPolicy.eSingleDependency == curAssetBundleEntity.AssetBuildPolicy)
#endif
                {
                    collectPathList.AddRange(curAssetBundleEntity.assetPathList);

                    if (null == assetBundleEntity)
                    {
                        assetBundleEntity = curAssetBundleEntity;
                        assetBundleEntity.assetPathList = collectPathList;

                        outAssetBundleEntity = assetBundleEntity;
                    }

                    assetEntryList.RemoveAt(index);
                }
            }
        }

        public static void BuildAssetEntityByNewPolicy(List<StreamingAssetBundleEntry> assetEntryList)
        {
            float startTime = Time.realtimeSinceStartup;

            StreamingAssetBundleEntry assetEntity = null;

            AssetBundleBuilderUtilV2.PreProcessAssetEntityByNewPolicy(assetEntryList, ref assetEntity);
            AssetBundleBuilderUtilV2.BuildAssetEntityBySingleDependencyPolicy(assetEntryList, assetEntity);

            Debug.Log("BuildAssetEntityByNewPolicy total time " + System.TimeSpan.FromSeconds(Time.realtimeSinceStartup - startTime));
        }

        #region Asset Config Util
        public static bool IsAsbAsset(string path)
        {
            bool ret = AssetBundleTool.IsAsbAsset(path);
            return ret;
        }

        public static bool IsParentOrChildPathAlreadyAdded(ref string error, List<StreamingAssetBundleEntry> assetEntityList, string path)
        {
            bool ret = false;

            for (int aIndex = assetEntityList.Count - 1; aIndex >= 0; --aIndex)
            {
                for (int bIndex = assetEntityList[aIndex].assetPathList.Count - 1; bIndex >= 0; --bIndex)
                {
                    if (!AssetBundleBuilderUtilV2.IsSameParentDir(assetEntityList[aIndex].assetPathList[bIndex], path))
                    {
                        if (assetEntityList[aIndex].assetPathList[bIndex].StartsWith(path, System.StringComparison.CurrentCultureIgnoreCase) ||
                            path.StartsWith(assetEntityList[aIndex].assetPathList[bIndex], System.StringComparison.CurrentCultureIgnoreCase))
                        {
                            error = assetEntityList[aIndex].assetPathList[bIndex];
                            ret = true;
                            break;
                        }
                    }
                }

                if (ret)
                {
                    break;
                }
            }

            return ret;
        }

        // 单依赖打包策略添加到 Asb 配置文件
        public static void AddToAsbConfigWithSingleDependencyPolicy()
        {
            if (Selection.assetGUIDs == null || Selection.assetGUIDs.Length == 0)
            {
                Debug.LogError("[AddToConfig] 请选择一个文件夹进行此操作");
                return;
            }

            if (Selection.assetGUIDs.Length == 1)
            {
                var path = AssetDatabase.GUIDToAssetPath(Selection.assetGUIDs[0]);
                if (!AssetDatabase.IsValidFolder(path))
                {
                    Debug.LogError("[AddToConfig] 请选择一个文件夹进行此操作");
                    return;
                }
                if (!AssetBundleBuilderUtilV2.IsAsbAsset(path))
                {
                    Debug.LogErrorFormat("[AddToConfig] 请选择一个\"{0}\"下的文件夹进行此操作", ASB_RES_PATH_SLASH);
                    return;
                }
            }

            var asbEntries = StreamingAssetBundleEntry.LoadConfig();

            foreach (var guid in Selection.assetGUIDs)
            {
                var path = AssetDatabase.GUIDToAssetPath(guid);

                if (!AssetDatabase.IsValidFolder(path))
                    continue;

                if (!AssetBundleBuilderUtilV2.IsAsbAsset(path))
                    continue;

                var name = path.Substring(ASB_RES_PATH_SLASH.Length);

                if (asbEntries.Exists(a => string.Compare(a.name, name, true) == 0))
                {
                    Debug.LogErrorFormat("[AddToConfig] 包名\"{0}\"已存在", name);
                    continue;
                }
                if (asbEntries.Exists(a => a.assetPathList.Contains(path, System.StringComparer.CurrentCultureIgnoreCase)))
                {
                    Debug.LogErrorFormat("[AddToConfig] 路径\"{0}\"已存在", path);
                    continue;
                }

                string error = "";
                if (AssetBundleBuilderUtilV2.IsParentOrChildPathAlreadyAdded(ref error, asbEntries, path))
                {
                    Debug.LogErrorFormat("[AddToConfig] 路径\"{0}\"的父或子目录{1}已存在，当前 Single Dependency Policy 不支持", path, error);
                    continue;
                }

                var entry = new StreamingAssetBundleEntry()
                {
                    name = name,
                    assetPathList = new List<string>() { path },
#if USE_NEW_ASSETSYSTEM
                    AssetBuildPolicy = AssetBundleBuildPolicy.eSingleDependency,
#endif
                };

                var index = -1;
                if (name.Contains('/'))
                {
                    var bestMatch = 0;
                    for (int i = asbEntries.Count - 1; i >= 0; i--)
                    {
                        var match = 0;
                        for (; match < name.Length && match < asbEntries[i].name.Length; match++)
                        {
                            if (char.ToLower(name[match]) != char.ToLower(asbEntries[i].name[match]))
                                break;
                        }
                        if (match > bestMatch)
                        {
                            bestMatch = match;
                            index = i + 1;
                        }
                        if (match == bestMatch && string.Compare(asbEntries[i].name, name, true) > 0)
                        {
                            bestMatch = match;
                            index = i;
                        }
                    }
                }

                if (index != -1)
                {
                    asbEntries.Insert(index, entry);
                }
                else
                {
                    asbEntries.Add(entry);
                }

                Debug.Log("[AddToConfig] 添加成功: " + entry.ToConfigString());
            }

            using (var writer = new StreamWriter(StreamingAssetBundleUtility.ASB_RES_FILE_PATH))
            {
                string line = "";
                writer.WriteLine(StreamingAssetBundleEntry.HeaderLine);
                for (int i = 0; i < asbEntries.Count; i++)
                {
                    line = asbEntries[i].ToConfigString();
                    writer.WriteLine(line);
                }
            }

            AssetDatabase.Refresh();
        }

        // 单依赖打包策略添加到 Asb 配置文件
        public static void RemoveSelfAndChildFormASBConfig()
        {
            if (Selection.assetGUIDs == null || Selection.assetGUIDs.Length == 0)
            {
                Debug.LogError("[AddToConfig] 请选择一个文件夹进行此操作");
                return;
            }

            if (Selection.assetGUIDs.Length == 1)
            {
                var path = AssetDatabase.GUIDToAssetPath(Selection.assetGUIDs[0]);
                if (!AssetDatabase.IsValidFolder(path))
                {
                    Debug.LogError("[AddToConfig] 请选择一个文件夹进行此操作");
                    return;
                }
                if (!IsAsbAsset(path))
                {
                    Debug.LogErrorFormat("[AddToConfig] 请选择一个\"{0}\"下的文件夹进行此操作", ASB_RES_PATH_SLASH);
                    return;
                }
            }

            var asbEntries = StreamingAssetBundleEntry.LoadConfig();
            StreamingAssetBundleEntry oneAsbEntry = null;

            foreach (var guid in Selection.assetGUIDs)
            {
                var path = AssetDatabase.GUIDToAssetPath(guid);

                if (!AssetDatabase.IsValidFolder(path))
                    continue;

                if (!IsAsbAsset(path))
                    continue;

                bool isFind = false;

                for (int aIndex = asbEntries.Count - 1; aIndex >= 0; --aIndex)
                {
                    oneAsbEntry = asbEntries[aIndex];

                    for (int bIndex = oneAsbEntry.assetPathList.Count - 1; bIndex >= 0; --bIndex)
                    {
                        if (oneAsbEntry.assetPathList[bIndex].StartsWith(path, System.StringComparison.CurrentCultureIgnoreCase))
                        {
                            UnityEngine.Debug.Log(string.Format("RemoveSelfAndChild EntityName {0}, AssetPath {1}", oneAsbEntry.name, oneAsbEntry.assetPathList[bIndex]));

                            isFind = true;
                            oneAsbEntry.assetPathList.RemoveAt(bIndex);
                        }
                    }

                    if (oneAsbEntry.assetPathList.Count == 0)
                    {
                        asbEntries.Remove(oneAsbEntry);
                    }
                }

                if (!isFind)
                {
                    Debug.LogErrorFormat("[AddToConfig] 路径\"{0}\"不存在", path);
                    continue;
                }

                Debug.Log("[AddToConfig] 删除成功: " + path);
            }

            using (var writer = new StreamWriter(StreamingAssetBundleUtility.ASB_RES_FILE_PATH))
            {
                writer.WriteLine(StreamingAssetBundleEntry.HeaderLine);
                for (int i = 0; i < asbEntries.Count; i++)
                {
                    writer.WriteLine(asbEntries[i].ToConfigString());
                }
            }

            AssetDatabase.Refresh();
        }
        #endregion
    }
}