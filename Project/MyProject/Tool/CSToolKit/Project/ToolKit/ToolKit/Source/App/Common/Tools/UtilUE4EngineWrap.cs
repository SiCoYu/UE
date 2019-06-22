namespace ToolSet
{
	public static class UtilUE4EngineWrap
	{
		public const string DEFAULT_MOUNT_POINT = "/Game";
		public const string DEFAULT_PHYSICS_FOLDER = "Content";
		public const string ASSET_DOT_EXT = ".uasset";
		public const string ASSET_EXT = "uasset";

		public static string ProjectSavedDir()
		{
			string ret = string.Format("{0}/Saved", CtxExt.msExtInstance.mProjectConfig.getProjectRootPath());
			return ret;
		}

		public static bool TryConvertLongPackageNameToFilename(ref string InLongPackageName, ref string OutFilename)
		{
			string noPrefixPackageName = InLongPackageName.Substring(DEFAULT_MOUNT_POINT.Length + 1);
			OutFilename = string.Format("{0}/{1}/{2}.{3}", CtxExt.msExtInstance.mProjectConfig.getProjectRootPath(), DEFAULT_PHYSICS_FOLDER, noPrefixPackageName, ASSET_EXT);
			return true;
		}

		public static bool TryConvertFilenameToLongPackageName(ref string InAbsolutePackagePath, ref string OutFilename)
		{
			string noMountPointPackageName = InAbsolutePackagePath.Substring(CtxExt.msExtInstance.mProjectConfig.getProjectRootPath().Length + 1);
			noMountPointPackageName = noMountPointPackageName.Substring(0, noMountPointPackageName.Length - ASSET_DOT_EXT.Length);
			OutFilename = string.Format("{0}/{1}", DEFAULT_MOUNT_POINT, noMountPointPackageName);
			return true;
		}
	}
}