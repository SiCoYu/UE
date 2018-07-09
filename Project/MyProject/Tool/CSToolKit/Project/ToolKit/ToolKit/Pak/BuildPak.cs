using System.Collections.Generic;
using System.Diagnostics;
using System.IO;

namespace ToolKit
{
    /**
     * @ref UE4资源热更新 
     * @url http://blog.csdn.net/liulong1567/article/details/71597892
     */
    public class BuildPak
    {
        protected string mUE4EngineRootPath;    // UE4 Engine 根目录
        protected string mProjectRootPath;      // Project 根目录
        protected string mOutPath;
        protected bool mIsBuildPakSuccess;
        protected List<string> mBuildPakFileList;   // 打包文件列表

        public BuildPak()
        {
            this.mUE4EngineRootPath = @"D:\File\Self\UE\UnrealEngine";
            this.mProjectRootPath = @"D:\File\Self\UE\UE\Project\MyProject\MyProject";
            this.mOutPath = @"D:\File\Self\UE\UE\Project\MyProject\Test";
            this.mIsBuildPakSuccess = false;
            this.mBuildPakFileList = new List<string>();
        }

        public void init()
        {
            this.addPakFile("BaseMaterial.uasset");
            this.addPakFile("GrayMaterial.uasset");
            this.addPakFile("UFO.uasset");
        }

        public void dispose()
        {

        }

        public string getUE4EngineRootPath()
        {
            return this.mUE4EngineRootPath;
        }

        public void setUE4EngineRootPath(string value)
        {
            this.mUE4EngineRootPath = value;
        }

        public string getOutPath()
        {
            return this.mOutPath;
        }

        public void setOutPath(string value)
        {
            this.mOutPath = value;
        }

        public void addPakFile(string fileName)
        {
            fileName = this.mProjectRootPath + "/" + @"Content\MyAsset\MyFly\Flying\Meshes" + "/" + fileName;
            this.mBuildPakFileList.Add(fileName);
        }

        public void build()
        {
            // 检查选中的引擎根目录,其目录下是否包含有[UnrealPak.exe]文件
            if (!File.Exists(this.mUE4EngineRootPath + @"\Engine\Binaries\Win64\UnrealPak.exe"))
            {
                this.mIsBuildPakSuccess = false;
            }
            else
            {
                this._buildOneToOne();
                this._buildMultiToOne();
            }
        }

        public void _buildOneToOne()
        {
            int index = 0;
            int listLen = this.mBuildPakFileList.Count;
            string assetFullName = "";
            string[] assetArray = null;
            string assetName = "";
            string outPath = "";

            while (index < listLen)
            {
                assetFullName = this.mBuildPakFileList[index].Replace('\\', '/');
                assetArray = assetFullName.Split('/');
                assetName = assetArray[assetArray.Length - 1].Replace(".uasset", "");
                outPath = this.mOutPath + "\\" + assetName + ".pak";

                //通过[Process]相关类来多次调用[UnrealPak.exe]程序来打包  
                ProcessStartInfo info = new ProcessStartInfo();
                info.FileName = this.mUE4EngineRootPath + @"\Engine\Binaries\Win64\UnrealPak.exe";
                info.Arguments = @outPath + @" " + @assetFullName;
                info.WindowStyle = ProcessWindowStyle.Minimized;
                Process process = Process.Start(info);
                process.WaitForExit();

                index += 1;
            }
        }

        public void _buildMultiToOne()
        {
            int index = 0;
            int listLen = this.mBuildPakFileList.Count;
            string outPath = this.mOutPath + "\\" + "MultiOne" + ".pak";
            string cmdParams = outPath;
            string assetFullName = "";

            while (index < listLen)
            {
                assetFullName = this.mBuildPakFileList[index].Replace('\\', '/');
                cmdParams = cmdParams + @" " + @assetFullName;

                index += 1;
            }

            //通过[Process]相关类来多次调用[UnrealPak.exe]程序来打包  
            ProcessStartInfo info = new ProcessStartInfo();
            info.FileName = this.mUE4EngineRootPath + @"\Engine\Binaries\Win64\UnrealPak.exe";
            info.Arguments = cmdParams;
            info.WindowStyle = ProcessWindowStyle.Minimized;
            Process process = Process.Start(info);
            process.WaitForExit();
        }
    }
}
