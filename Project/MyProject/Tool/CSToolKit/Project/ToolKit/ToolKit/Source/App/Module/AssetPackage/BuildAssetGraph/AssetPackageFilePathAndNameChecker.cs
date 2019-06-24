using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace ToolSet
{
    public class PlatformAssetBundleBuilderChecker
    {
        protected string _RootPath;
        protected List<string> _MaxLengthInvalidFileNameList;
        protected List<string> _MaxLengthInvalidFilePathList;
        protected List<string> _HasSpaceInvalidFilePathList;

        protected List<string> _StagePrefabAssetPath;

        public PlatformAssetBundleBuilderChecker()
        {

        }

        public void Init()
        {
            this._MaxLengthInvalidFileNameList = new List<string>();
            this._MaxLengthInvalidFilePathList = new List<string>();
            this._HasSpaceInvalidFilePathList = new List<string>();
            this._StagePrefabAssetPath = new List<string>();
        }

        public void Dispose()
        {
            this._MaxLengthInvalidFileNameList.Clear();
            this._MaxLengthInvalidFileNameList = null;
            this._MaxLengthInvalidFilePathList.Clear();
            this._MaxLengthInvalidFilePathList = null;
            this._HasSpaceInvalidFilePathList.Clear();
            this._HasSpaceInvalidFilePathList = null;
        }

        public void SetRootPath(string value)
        {
            this._RootPath = value;
        }

        protected void _WriteMaxLengthInvalidFileNameManifest(string fileName)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteInvalidFileNameManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetPackageUtil.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "MaxLengthInvalidFileNameManifest");
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

                byteArray = Encoding.UTF8.GetBytes(string.Format("Total Count is {0}\n\n", this._MaxLengthInvalidFileNameList.Count));
                fileStream.Write(byteArray, 0, byteArray.Length);

                int indexX = 0;
                for (; indexX < this._MaxLengthInvalidFileNameList.Count; ++indexX)
                {
                    byteArray = Encoding.UTF8.GetBytes(string.Format("{0}\n", this._MaxLengthInvalidFileNameList[indexX]));
                    fileStream.Write(byteArray, 0, byteArray.Length);

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
                UtilDebug.Log(string.Format("_WriteInvalidFileNameManifest, end"));
            }
        }

        protected void _WriteMaxLengthInvalidFilePathManifest(string fileName)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteInvalidFilePathManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetPackageUtil.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "MaxLengthInvalidFilePathManifest");
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

                byteArray = Encoding.UTF8.GetBytes(string.Format("Total Count is {0}\n\n", this._MaxLengthInvalidFilePathList.Count));
                fileStream.Write(byteArray, 0, byteArray.Length);

                int indexX = 0;
                for (; indexX < this._MaxLengthInvalidFilePathList.Count; ++indexX)
                {
                    byteArray = Encoding.UTF8.GetBytes(string.Format("{0}\n", this._MaxLengthInvalidFilePathList[indexX]));
                    fileStream.Write(byteArray, 0, byteArray.Length);

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
                UtilDebug.Log(string.Format("_WriteInvalidFilePathManifest, end"));
            }
        }

        protected void _WriteHasSpaceInvalidFilePathManifest(string fileName)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteHasSpaceInvalidFilePathManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetPackageUtil.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "HasSpaceInvalidFilePathManifest");
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

                byteArray = Encoding.UTF8.GetBytes(string.Format("Total Count is {0}\n\n", this._HasSpaceInvalidFilePathList.Count));
                fileStream.Write(byteArray, 0, byteArray.Length);

                int indexX = 0;
                for (; indexX < this._HasSpaceInvalidFilePathList.Count; ++indexX)
                {
                    byteArray = Encoding.UTF8.GetBytes(string.Format("{0}\n", this._HasSpaceInvalidFilePathList[indexX]));
                    fileStream.Write(byteArray, 0, byteArray.Length);

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
                UtilDebug.Log(string.Format("_WriteHasSpaceInvalidFilePathManifest, end"));
            }
        }

        protected void _WriteStageAssetFilePathManifest(string fileName)
        {
            if (AssetPackageUtil.ENABLE_COMMON_LOG)
            {
                UtilDebug.Log(string.Format("_WriteStageAssetFilePathManifest, start"));
            }

            if (string.IsNullOrEmpty(fileName))
            {
                fileName = AssetPackageUtil.GetOrCreateAssetManifestDirectory();
                fileName = string.Format("{0}/{1}.txt", fileName, "StageAssetFilePathManifest");
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
                int indexX = 0;
                for (; indexX < this._StagePrefabAssetPath.Count; ++indexX)
                {
                    byteArray = Encoding.UTF8.GetBytes(string.Format("{0}\n", this._StagePrefabAssetPath[indexX]));
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
                UtilDebug.Log(string.Format("_WriteStageAssetFilePathManifest, end"));
            }
        }

        protected void _OnMaxLengthInvalidFileNameHandle(string fullPath)
        {
            if ("meta" != AssetPackageUtil.GetFileExtName(fullPath))
            {
                string fileName = AssetPackageUtil.GetRelativePathStartWithAsset(fullPath);
                if (AssetPackageUtil.GetAssetBundleFileNameLengthByFilePath(fileName) > 100)
                {
                    this._MaxLengthInvalidFileNameList.Add(fileName);
                }
            }
        }

        protected void _CollectMaxLengthInvalidFileNameByRootDir(string rootPath)
        {
            if (Directory.Exists(rootPath))
            {
                AssetPackageUtil.TraverseDir(rootPath, true, this._OnMaxLengthInvalidFileNameHandle);
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("_CollectInvalidFileNameByRootDir, {0} path not exist", rootPath));
                }
            }
        }

        protected void _OnMaxLengthInvalidFilePathHandle(string fullPath)
        {
            if ("meta" != AssetPackageUtil.GetFileExtName(fullPath))
            {
                if (AssetPackageUtil.GetAssetBundleFilePathLengthByFilePath(fullPath) > 255)
                {
                    string fileName = AssetPackageUtil.GetRelativePathStartWithAsset(fullPath);
                    this._MaxLengthInvalidFilePathList.Add(fileName);
                }
            }
        }

        protected void _CollectMaxLengthInvalidFilePathByRootDir(string rootPath)
        {
            if (Directory.Exists(rootPath))
            {
                AssetPackageUtil.TraverseDir(rootPath, true, this._OnMaxLengthInvalidFilePathHandle);
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("_CollectInvalidFilePathByRootDir, {0} path not exist", rootPath));
                }
            }
        }

        protected void _OnHasSpaceInvalidFilePathHandle(string fullPath)
        {
            if ("meta" != AssetPackageUtil.GetFileExtName(fullPath))
            {
                if (AssetPackageUtil.HasSpceInPath(fullPath))
                {
                    string fileName = AssetPackageUtil.GetRelativePathStartWithAsset(fullPath);
                    this._HasSpaceInvalidFilePathList.Add(fileName);
                }
            }
        }

        protected void _OnStageAssetFilePathHandle(string fullPath)
        {
            if ("prefab" == AssetPackageUtil.GetFileExtName(fullPath))
            {
                string fileName = AssetPackageUtil.GetRelativePathStartWithAsset(fullPath);
                fileName = AssetPackageUtil.GetFileNameNoExt(fileName);
                fileName = fileName.Substring("Assets/AsbRes/".Length);
                fileName = string.Format("pathList.Add(\"{0}\");", fileName);
                this._StagePrefabAssetPath.Add(fileName);
            }
        }

        protected void _CollectHasSpaceInvalidFilePathByRootDir(string rootPath)
        {
            if (Directory.Exists(rootPath))
            {
                AssetPackageUtil.TraverseDir(rootPath, true, this._OnHasSpaceInvalidFilePathHandle);
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("_CollectHasSpaceInvalidFilePathByRootDir, {0} path not exist", rootPath));
                }
            }
        }

        protected void _CollectStageAssetFilePathByRootDir(string rootPath)
        {
            if (Directory.Exists(rootPath))
            {
                AssetPackageUtil.TraverseDir(rootPath, true, this._OnStageAssetFilePathHandle);
            }
            else
            {
                if (AssetPackageUtil.ENABLE_COMMON_LOG)
                {
                    UtilDebug.Log(string.Format("_CollectHasSpaceInvalidFilePathByRootDir, {0} path not exist", rootPath));
                }
            }
        }

        public void CollectMaxLengthInvalidFileName()
        {
            string fullPath = AssetPackageUtil.GetFullPathByRelativePathStartWithAsset(this._RootPath);
            this._CollectMaxLengthInvalidFileNameByRootDir(fullPath);
            this._WriteMaxLengthInvalidFileNameManifest("");
        }

        public void CollectMaxLengthInvalidFilePath()
        {
            string fullPath = AssetPackageUtil.GetFullPathByRelativePathStartWithAsset(this._RootPath);
            this._CollectMaxLengthInvalidFilePathByRootDir(fullPath);
            this._WriteMaxLengthInvalidFilePathManifest("");
        }

        public void CollectHasSpaceInvalidFilePath()
        {
            string fullPath = AssetPackageUtil.GetFullPathByRelativePathStartWithAsset(this._RootPath);
            this._CollectHasSpaceInvalidFilePathByRootDir(fullPath);
            this._WriteHasSpaceInvalidFilePathManifest("");
        }

        public void CollectStageAssetFilePath()
        {
            string fullPath = AssetPackageUtil.GetFullPathByRelativePathStartWithAsset(this._RootPath);
            this._CollectStageAssetFilePathByRootDir(fullPath);
            this._WriteStageAssetFilePathManifest("");
        }
    }
}