using SDK.Lib;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;

namespace ToolSet
{
    /**
     * @brief AssetBundle 打包
     */
    public static class AssetPackageUtil
	{
        public const bool ENABLE_COMMON_LOG = true;
        public const bool ENABLE_ERROR_LOG = true;
        public const bool ENABLE_PROFILE_LOG = false;

		public static void BuildAssetBundle(AssetPackageGraph assetPackageGraph)
		{

		}

		public static string GetOrCreateAssetManifestDirectory(bool isCreateDirectory = true)
        {
            string rootPath = UtilUE4EngineWrap.ProjectContentDir();
            rootPath = UtilFileIO.normalPath(rootPath);
            rootPath = rootPath.Substring(0, rootPath.IndexOf(UtilUE4EngineWrap.DEFAULT_PHYSICS_FOLDER_WITH_SLASH_PREFIX));
            string outputPath = string.Format("{0}/Output/AssetBundlesV2/Windows", rootPath);

            if (isCreateDirectory)
            {
                if (!Directory.Exists(outputPath))
                {
                    try
                    {
                        Directory.CreateDirectory(outputPath);

                        if (AssetPackageUtil.ENABLE_COMMON_LOG)
                        {
                            UtilDebug.Log(string.Format("_GetAssetDependencyManifestFullFileName, create directory {0}", outputPath));
                        }
                    }
                    catch (System.Exception exp)
                    {
                        if (AssetPackageUtil.ENABLE_ERROR_LOG)
                        {
                            UtilDebug.LogError(string.Format("_GetAssetDependencyManifestFullFileName, create error {0}", exp.Message));
                        }
                    }
                }
                else
                {
                    if (AssetPackageUtil.ENABLE_COMMON_LOG)
                    {
                        UtilDebug.Log(string.Format("_GetAssetDependencyManifestFullFileName, {0} directory exist", outputPath));
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
						AssetPackageUtil.TraverseDir(subDirArray[index].FullName, isRecursive, handle);
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
            fullPath = AssetPackageUtil.NormalPath(fullPath);
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
            fullPath = AssetPackageUtil.NormalPath(fullPath);
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
            fullPath = AssetPackageUtil.NormalPath(fullPath);
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
            string filePathNoFileName = AssetPackageUtil.GetFilePathNoFileName(filePath);
            string fileNameNoExtName = AssetPackageUtil.GetFileNameNoPathAndExt(filePath);
            string fileExtName = AssetPackageUtil.GetFileExtName(filePath);
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
            string fileNameNoExtName = AssetPackageUtil.GetFileNameNoPathAndExt(filePath);
            string fileExtName = AssetPackageUtil.GetFileExtName(filePath);
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

            string aParent = AssetPackageUtil.GetFilePathNoFileName(aPath);
            string bParent = AssetPackageUtil.GetFilePathNoFileName(bPath);
            ret = aParent.Equals(bParent, System.StringComparison.CurrentCultureIgnoreCase);

            return ret;
        }

        public static string GetFullPathFromSeparate(string pathNoFileName, string fileNameNoExt, string extName)
        {
            System.Text.StringBuilder ret = new System.Text.StringBuilder();

            if (string.IsNullOrEmpty(pathNoFileName) ||
                string.IsNullOrEmpty(fileNameNoExt))
            {
                UtilDebug.LogError(string.Format("pathNoFileName or fileNameNoExt or extName is null"));
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
            string assetBundlePath = AssetPackageUtil.GetFileNameNoExt(assetPath) + ".unity3d";
            return assetBundlePath;
        }

        public static string ChangeExtNameDotToUnderlineAndAddAssetBundleExt(string assetPath)
        {
            string fileExtName = AssetPackageUtil.GetFileExtName(assetPath);
            string fileNameNoExtName = AssetPackageUtil.GetFileNameNoExt(assetPath);
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

        public static string GetFullPathByRelativePathStartWithAsset(string relativeAssetPathWithAsset)
        {
			UtilDebug.Assert(0 == relativeAssetPathWithAsset.IndexOf("Asset"), "GetFullPathByRelativePathWithAsset, name error");
			string fullPathBeforeAsset = UtilUE4EngineWrap.ProjectContentDir();
            fullPathBeforeAsset = fullPathBeforeAsset.Replace("\\", "/");
            fullPathBeforeAsset = fullPathBeforeAsset.Substring(0, fullPathBeforeAsset.LastIndexOf("/Asset"));
            return string.Format("{0}/{1}", fullPathBeforeAsset, relativeAssetPathWithAsset);
        }
    }
}