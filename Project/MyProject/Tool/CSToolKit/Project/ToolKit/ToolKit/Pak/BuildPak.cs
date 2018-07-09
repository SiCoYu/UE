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
        protected string mUE4EngineRootPath;
        protected string mOutPath;
        protected bool mIsBuildPakSuccess;
        protected List<string> mBuildPakFileList;   // 打包文件列表

        public BuildPak()
        {
            this.mUE4EngineRootPath = "";
            this.mOutPath = "";
            this.mIsBuildPakSuccess = false;
        }

        public void init()
        {

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

        public void build()
        {
            // 检查选中的引擎根目录,其目录下是否包含有UnrealPak.exe文件  
            if (!File.Exists(this.mUE4EngineRootPath + @"\Engine\Binaries\Win64\UnrealPak.exe"))
            {
                this.mIsBuildPakSuccess = false;
            }
            else
            {
                //根据多选框选中的文件来对文件进行打包  
                int index = 0;
                int listLen = this.mBuildPakFileList.Count;

                while(index < listLen)
                {
                    string assetFullName = this.mBuildPakFileList[index].Replace('\\', '/');
                    string[] assetArray = assetFullName.Split('/');
                    string assetName = assetArray[assetArray.Length - 1].Replace(".uasset", "");
                    string outPath = this.mOutPath + "\\" + assetName + ".pak";

                    //通过Process相关类来多次调用UnrealPak.exe程序来打包  
                    ProcessStartInfo info = new ProcessStartInfo();
                    info.FileName = this.mUE4EngineRootPath + @"\Engine\Binaries\Win64\UnrealPak.exe";
                    info.Arguments = @outPath + @" " + @assetFullName;
                    info.WindowStyle = ProcessWindowStyle.Minimized;
                    Process process = Process.Start(info);
                    process.WaitForExit();

                    index += 1;
                }
            }
        }
    }
}
