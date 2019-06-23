namespace ToolSet
{
	public static class UtilUE4EngineWrap
	{
		public const string DEFAULT_MOUNT_POINT = "/Game";
		public const string DEFAULT_PHYSICS_FOLDER = "Content";
		public const string DEFAULT_PHYSICS_FOLDER_WITH_SLASH_PREFIX = "/Content";
		public const string DEFAULT_PHYSICS_FOLDER_WITH_SLASH_SUFFIX = "Content/";
		public const string ASSET_DOT_EXT = ".uasset";
		public const string ASSET_EXT = "uasset";
		public const string MAP_DOT_EXT = ".umap";
		public const string MAP_EXT = "umap";
		public const string DOT = ".";

		public static string ProjectSavedDir()
		{
			string ret = string.Format("{0}/Saved", CtxExt.msExtInstance.mProjectConfig.getProjectRootPath());
			return ret;
		}

		public static string ProjectContentDir()
		{
			string ret = string.Format("{0}/{1}", CtxExt.msExtInstance.mProjectConfig.getProjectRootPath(), DEFAULT_PHYSICS_FOLDER);
			return ret;
		}

		public static string ProjectDir()
		{
			string ret = string.Format("{0}", CtxExt.msExtInstance.mProjectConfig.getProjectRootPath());
			return ret;
		}

		public static bool TryConvertLongPackageNameToFilename(ref string InLongPackageName, ref string OutFilename)
		{
			string noPrefixPackageName = InLongPackageName.Substring(DEFAULT_MOUNT_POINT.Length + 1);
			OutFilename = string.Format("{0}/{1}/{2}.{3}", CtxExt.msExtInstance.mProjectConfig.getProjectRootPath(), DEFAULT_PHYSICS_FOLDER, noPrefixPackageName, ASSET_EXT);
			return true;
		}

		public static string ConvertFilenameToLongPackageName(ref string InAbsolutePackagePath)
		{
			string noMountPointPackageName = InAbsolutePackagePath.Substring(CtxExt.msExtInstance.mProjectConfig.getProjectRootPath().Length + 1);
			noMountPointPackageName = noMountPointPackageName.Substring(DEFAULT_PHYSICS_FOLDER.Length + 1);
			int index = noMountPointPackageName.LastIndexOf(DOT);
			if (-1 != index)
			{
				noMountPointPackageName = noMountPointPackageName.Substring(0, index);
			}
			string OutFilename = string.Format("{0}/{1}", DEFAULT_MOUNT_POINT, noMountPointPackageName);
			return OutFilename;
		}

		public static bool TryConvertFilenameToLongPackageName(ref string InAbsolutePackagePath, ref string OutFilename)
		{
			OutFilename = UtilUE4EngineWrap.ConvertFilenameToLongPackageName(ref InAbsolutePackagePath);
			return true;
		}
	}
}