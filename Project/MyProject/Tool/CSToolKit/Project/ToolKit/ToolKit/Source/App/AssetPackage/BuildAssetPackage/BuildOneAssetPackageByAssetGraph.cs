using SDK.Lib;

namespace ToolSet
{
	public class BuildOneAssetPackageByAssetGraph : BuildOneAssetPackageBase
	{
		protected AssetBundleBuild mAssetBundleBuild;

		public BuildOneAssetPackageByAssetGraph()
		{

		}

		public override void init()
		{
			this.mPakOutPath = this.mAssetBundleBuild.assetBundleName;
			base.init();
		}

		public override void dispose()
		{
			base.dispose();
		}

		public void SetAssetBundleBuild(AssetBundleBuild value)
		{
			this.mAssetBundleBuild = value;
		}

		public override string getOutAssetPackageAbsolutePath()
		{
			string ret = this.mAssetBundleBuild.assetBundleName;
			return ret;
		}

		public override string getOutAssetPackageParams()
		{
			int index = 0;
			int listLen = this.mAssetBundleBuild.assetNames.Length;
			string outPath = this.getOutAssetPackageAbsolutePath();
			string cmdParams = outPath;
			string assetFullName = "";

			while (index < listLen)
			{
				assetFullName = UtilFileIO.normalPath(this.mAssetBundleBuild.assetNames[index]);
				cmdParams = string.Format("{0} {1}", cmdParams, @assetFullName);

				index += 1;
			}

			return cmdParams;
		}
	}
}