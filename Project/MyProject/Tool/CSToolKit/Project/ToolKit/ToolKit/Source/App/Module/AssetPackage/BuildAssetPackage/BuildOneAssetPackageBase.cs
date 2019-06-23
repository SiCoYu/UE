using SDK.Lib;
using System.Collections.Generic;
using System.Diagnostics;

namespace ToolSet
{
	public class BuildOneAssetPackageBase
	{
		protected string mUE4EngineRootPath;    // UE4 Engine 根目录
		protected string mProjectRootPath;      // Project 根目录

		protected string mPakOutPath;
		protected bool mIsBuildPakSuccess;
		protected bool mIsEncrypt;
		protected bool mIsCompress;
		protected bool mIsExportDependencies;
		protected bool mIsEnableAbslog;
		protected bool mIsEnableOrder;
		protected bool mIsWindowsPlatform;
		protected bool mIsTest;
		protected bool mIsList;
		protected bool mIsExtract;
		protected string mPakOtherParams;

		public BuildOneAssetPackageBase()
		{
			this.mIsBuildPakSuccess = false;
			this.mIsEncrypt = false;
			this.mIsCompress = false;
			this.mIsExportDependencies = true;
			this.mIsEnableAbslog = true;
			this.mIsEnableOrder = false;
			this.mIsWindowsPlatform = true;
			this.mIsTest = false;
			this.mIsList = false;
			this.mIsExtract = false;

			this.mPakOtherParams = " -UTF8Output";
		}

		public virtual void init()
		{
			this.mUE4EngineRootPath = CtxExt.msExtInstance.mProjectConfig.getEngineRootPath();
			this.mProjectRootPath = CtxExt.msExtInstance.mProjectConfig.getProjectRootPath();
			this.mPakOutPath = CtxExt.msExtInstance.mProjectConfig.getPakOutPath();

			this._initCommandLineParams();
		}

		public virtual void dispose()
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

		protected void _initCommandLineParams()
		{
			string logFile = string.Format("{0}/Pak.log", this.mPakOutPath);
			string exportDependenciesFile = string.Format("{0}/DependenciesFile.txt", this.mPakOutPath);
			string orderFile = string.Format("{0}/Order.txt", this.mPakOutPath);
			string extractPath = string.Format("{0}/Extract", this.mPakOutPath);

			if (this.mIsEncrypt)
			{
				this.mPakOtherParams = string.Format("{0} {1}", this.mPakOtherParams, "-encrypt");
			}
			if (this.mIsCompress)
			{
				this.mPakOtherParams = string.Format("{0} {1}", this.mPakOtherParams, "-compress");
			}
			if (this.mIsExportDependencies)
			{
				this.mPakOtherParams = string.Format("{0} -ExportDependencies={1} -NoAssetRegistryCache -ForceDependsGathering", this.mPakOtherParams, exportDependenciesFile);
			}
			if (this.mIsEnableAbslog)
			{
				this.mPakOtherParams = string.Format("{0} -abslog={1}", this.mPakOtherParams, logFile);
			}
			if (this.mIsEnableOrder)
			{
				this.mPakOtherParams = string.Format("{0} -order={1}", this.mPakOtherParams, orderFile);
			}
			if (this.mIsWindowsPlatform)
			{
				this.mPakOtherParams = string.Format("{0} -platform={1}", this.mPakOtherParams, "Windows");
			}
			if (this.mIsTest)
			{
				this.mPakOtherParams = string.Format("{0} -Test", this.mPakOtherParams);
			}
			if (this.mIsList)
			{
				this.mPakOtherParams = string.Format("{0} -List={1}", this.mPakOtherParams, "Windows");
			}
			if (this.mIsExtract)
			{
				if (UtilFileIO.existDirectory(extractPath))
				{
					UtilFileIO.createDirectory(extractPath, true);
				}

				this.mPakOtherParams = string.Format("{0} -Extract {1}", this.mPakOtherParams, extractPath);
			}
		}

		public string getPakOutPath()
		{
			return this.mPakOutPath;
		}

		public void setPakOutPath(string value)
		{
			this.mPakOutPath = value;
		}

		public virtual string getOutAssetPackageAbsolutePath()
		{
			return "";
		}

		public virtual string getOutAssetPackageParams()
		{
			return "";
		}

		protected void _buildMultiAssetToOnePak()
		{
			string cmdParams = this.getOutAssetPackageParams();

			if (!UtilFileIO.existDirectory(this.mPakOutPath))
			{
				UtilFileIO.createDirectory(this.mPakOutPath, true);
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

		public void buildAssetPackage()
		{
			// 检查选中的引擎根目录,其目录下是否包含有[UnrealPak.exe]文件
			string unrealPakPath = string.Format("{0}/{1}", this.mUE4EngineRootPath, "Engine/Binaries/Win64/UnrealPak-Win64-Debug.exe");

			if (!UtilFileIO.existFile(unrealPakPath))
			{
				this.mIsBuildPakSuccess = false;
			}
			else
			{
				this._buildMultiAssetToOnePak();
				System.Console.WriteLine("Pak Success");
			}
		}
	}
}