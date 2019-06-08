using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using SDK.Lib;

namespace ToolSet
{
	/**
     * @ref UE4资源热更新 
     * @url http://blog.csdn.net/liulong1567/article/details/71597892
	 * @url https://blog.csdn.net/or_7r_ccl/article/details/53053337
     */
	public class TestBuildOnePak : TestBase
	{
        protected string mUE4EngineRootPath;    // UE4 Engine 根目录
        protected string mProjectRootPath;      // Project 根目录
        protected string mPakOutPath;
        protected bool mIsBuildPakSuccess;
        protected List<string> mBuildPakFileList;   // 打包文件列表
		protected bool mIsEncrypt;
		protected bool mIsCompress;
		protected string mPakOtherParams;

		public TestBuildOnePak()
        {
            this.mIsBuildPakSuccess = false;
            this.mBuildPakFileList = new List<string>();
			this.mIsEncrypt = false;
			this.mIsCompress = false;
		}

        public override void init()
        {
			base.init();

			this.mUE4EngineRootPath = CtxExt.msExtInstance.mProjectConfig.getEngineRootPath();
			this.mProjectRootPath = CtxExt.msExtInstance.mProjectConfig.getProjectRootPath();
			this.mPakOutPath = CtxExt.msExtInstance.mProjectConfig.getPakOutPath();
			string logFile = string.Format("{0}/Pak.log", this.mPakOutPath);

			if (this.mIsCompress)
			{
				if (this.mIsEncrypt)
				{
					this.mPakOtherParams = string.Format(" -order={0} -UTF8Output {1} {2}", logFile, "-encrypt", "-compress");
				}
				else
				{
					this.mPakOtherParams = string.Format(" -order={0} -UTF8Output {1}", logFile, "-compress");
				}
			}
			else
			{
				if (this.mIsEncrypt)
				{
					this.mPakOtherParams = string.Format(" -order={0} -UTF8Output {1}", logFile, "-encrypt");
				}
				else
				{
					this.mPakOtherParams = string.Format(" -order={0} -UTF8Output", logFile);
				}
			}

			//this.mPakOtherParams = "";
			this.mPakOtherParams = " -UTF8Output";

			this.addPakFile("BaseMaterial.uasset");
            this.addPakFile("GrayMaterial.uasset");
            this.addPakFile("UFO.uasset");
        }

        public override void dispose()
        {
			base.dispose();
        }

		public override void run()
		{
			base.run();

			this.build();
		}

		public string getUE4EngineRootPath()
        {
            return this.mUE4EngineRootPath;
        }

        public void setUE4EngineRootPath(string value)
        {
            this.mUE4EngineRootPath = value;
        }

        public string getPakOutPath()
        {
            return this.mPakOutPath;
        }

        public void setPakOutPath(string value)
        {
            this.mPakOutPath = value;
        }

        public void addPakFile(string fileName)
        {
			string fullFileName = string.Format("{0}/{1}/{2}", this.mProjectRootPath, @"Content/MyAsset/MyFly/Flying/Meshes", fileName);
			this.mBuildPakFileList.Add(fullFileName);
        }

        public void build()
        {
			// 检查选中的引擎根目录,其目录下是否包含有[UnrealPak.exe]文件
			string unrealPakPath = string.Format("{0}/{1}", this.mUE4EngineRootPath, "Engine/Binaries/Win64/UnrealPak-Win64-Debug.exe");

			if (!File.Exists(unrealPakPath))
            {
                this.mIsBuildPakSuccess = false;
            }
            else
            {
                this._buildOneAssetToOnePak();
                this._buildMultiAssetToOnePak();
				this._buildOnePakFromConfig();

				System.Console.WriteLine("Pak Success");
			}
        }

        protected void _buildOneAssetToOnePak()
        {
            int index = 0;
            int listLen = this.mBuildPakFileList.Count;
            string assetFullName = "";
            string assetName = "";
            string outPath = "";

			while (index < listLen)
            {
                assetFullName = UtilFileIO.normalPath(this.mBuildPakFileList[index]);
                assetName = UtilFileIO.getFileNameNoExt(assetFullName);
				if (!UtilFileIO.existDirectory(this.mPakOutPath))
				{
					UtilFileIO.createDirectory(this.mPakOutPath, true);
				}
				outPath = string.Format("{0}/{1}.pak", this.mPakOutPath, assetName);

				//通过[Process]相关类来多次调用[UnrealPak.exe]程序来打包  
				using (Process process = new Process())
				{
					ProcessStartInfo processStartInfo = new ProcessStartInfo();
					processStartInfo.FileName = string.Format("{0}/{1}", this.mUE4EngineRootPath, "Engine/Binaries/Win64/UnrealPak-Win64-Debug.exe");
					processStartInfo.Arguments = string.Format("{0} {1}{2}", @outPath, @assetFullName, this.mPakOtherParams);
					processStartInfo.WindowStyle = ProcessWindowStyle.Minimized;
					processStartInfo.UseShellExecute = false;
					processStartInfo.RedirectStandardError = true;
					processStartInfo.RedirectStandardOutput = true;

					process.StartInfo = processStartInfo;
					process.Start();
					UtilSysLibWrap.writeConsoleFromProcess(process);
					process.WaitForExit();
				}
				
				index += 1;
            }
        }

		protected void _buildMultiAssetToOnePak()
        {
            int index = 0;
            int listLen = this.mBuildPakFileList.Count;
            string outPath = string.Format("{0}/{1}.pak", this.mPakOutPath, "MultiOne");
            string cmdParams = outPath;
            string assetFullName = "";

			if (!UtilFileIO.existDirectory(this.mPakOutPath))
			{
				UtilFileIO.createDirectory(this.mPakOutPath, true);
			}

			while (index < listLen)
            {
				assetFullName = UtilFileIO.normalPath(this.mBuildPakFileList[index]);
				cmdParams = string.Format("{0} {1}", cmdParams, @assetFullName);

                index += 1;
            }

            // 通过 [Process] 相关类来多次调用 [UnrealPak.exe] 程序来打包  
            ProcessStartInfo processStartInfo = new ProcessStartInfo();
			processStartInfo.FileName = string.Format("{0}/{1}", this.mUE4EngineRootPath, @"Engine/Binaries/Win64/UnrealPak-Win64-Debug.exe");
			processStartInfo.Arguments = string.Format("{0}{1}", cmdParams, this.mPakOtherParams);
			processStartInfo.WindowStyle = ProcessWindowStyle.Minimized;
			processStartInfo.UseShellExecute = false;
			processStartInfo.RedirectStandardError = true;
			processStartInfo.RedirectStandardOutput = true;

			Process process = Process.Start(processStartInfo);
			UtilSysLibWrap.writeConsoleFromProcess(process);
			process.WaitForExit();
		}

		protected void _buildOnePakFromConfig()
		{

		}
	}
}