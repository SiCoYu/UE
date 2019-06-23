using SDK.Lib;
using System.Collections.Generic;
using System.Diagnostics;

namespace ToolSet
{
	public class BuildOneAssetPackageByFile : BuildOneAssetPackageBase
	{
		protected List<string> mBuildPakFileList;   // 打包文件列表

		public BuildOneAssetPackageByFile()
		{
			this.mBuildPakFileList = new List<string>();
		}

		public override void init()
		{
			base.init();

			this.addPakFile("BaseMaterial.uasset");
			this.addPakFile("GrayMaterial.uasset");
			this.addPakFile("UFO.uasset");
		}

		public override void dispose()
		{
			base.dispose();
		}

		public void addPakFile(string fileName)
		{
			string fullFileName = string.Format("{0}/{1}/{2}", this.mProjectRootPath, @"Content/MyAsset/MyFly/Flying/Meshes", fileName);
			this.mBuildPakFileList.Add(fullFileName);
		}

		public override string getOutAssetPackageAbsolutePath()
		{
			string ret = string.Format("{0}/{1}.pak", this.mPakOutPath, "MultiOne");
			return ret;
		}

		public override string getOutAssetPackageParams()
		{
			int index = 0;
			int listLen = this.mBuildPakFileList.Count;
			string outPath = this.getOutAssetPackageAbsolutePath();
			string cmdParams = outPath;
			string assetFullName = "";

			while (index < listLen)
			{
				assetFullName = UtilFileIO.normalPath(this.mBuildPakFileList[index]);
				cmdParams = string.Format("{0} {1}", cmdParams, @assetFullName);

				index += 1;
			}

			return cmdParams;
		}
	}
}