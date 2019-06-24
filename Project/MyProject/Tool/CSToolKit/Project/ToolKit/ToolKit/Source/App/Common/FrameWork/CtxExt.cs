using SDK.Lib;

namespace ToolSet
{
    public class CtxExt : Ctx
    {
		static public CtxExt msExtInstance;

		public ProjectConfig mProjectConfig;
		public ExcelCtx mExcelCtx;
		public AssetPackageCtx mAssetPackageCtx;
		public TestMain mTestMain;

        public CtxExt()
        {
			this.mProjectConfig = new ProjectConfig();
			this.mTestMain = new TestMain();
		}

        public static Ctx instance()
        {
            if (null == Ctx.msInstance)
            {
				CtxExt.msExtInstance = new CtxExt();
				Ctx.msInstance = CtxExt.msExtInstance;
			}

            return Ctx.msInstance;
        }

        override protected void _preInit()
        {
            base._preInit();

            this.mExcelCtx = new ExcelCtx();
            this.mExcelCtx._preInit();

			this.mAssetPackageCtx = new AssetPackageCtx();
		}

        override protected void _execInit()
        {
            base._execInit();

			this.mProjectConfig.init();

			this.mExcelCtx._execInit();
			this.mAssetPackageCtx.init();
			this.mTestMain.init();
		}

        override protected void _postInit()
        {
            base._postInit();
        }

        override protected void _preDispose()
        {
            base._preDispose();
        }

        override protected void _execDispose()
        {
            base._execDispose();

			this.mProjectConfig.dispose();
			this.mProjectConfig = null;

			this.mExcelCtx._execDispose();
            this.mExcelCtx = null;

			this.mAssetPackageCtx.dispose();
			this.mAssetPackageCtx = null;

			this.mTestMain.dispose();
			this.mTestMain = null;
		}

        override protected void _postDispose()
        {
            base._postDispose();
        }

        override public void run()
        {
            base.run();

			//this.mExcelCtx.mExportJson.export();
			//this.mExcelCtx.mExportCsv.export();
			this.mAssetPackageCtx.mSingleDependencyGraph.AddCollectRootPath(
				UtilUE4EngineWrap.ProjectContentDir()
			);
			this.mAssetPackageCtx.mSingleDependencyGraph.AddIncludeAssetBundlePath(
				UtilUE4EngineWrap.DEFAULT_MOUNT_POINT
			);
			this.mAssetPackageCtx.mSingleDependencyGraph.AddExcludeAssetBundleFileExtName(
				"txt"
			);
			this.mAssetPackageCtx.mSingleDependencyGraph.AddExcludeAssetBundleFileExtName(
				"zip"
			);
			this.mAssetPackageCtx.mSingleDependencyGraph.AddExcludeAssetBundleFileExtName(
				"lua"
			);
			this.mAssetPackageCtx.mSingleDependencyGraph.AddExcludeAssetBundleFileExtName(
				 "py"
			);
			this.mAssetPackageCtx.mSingleDependencyGraph.AddExcludeAssetBundleFileExtName(
				  "pak"
			);
			//this.mAssetPackageCtx.mSingleDependencyGraph.OutAssetManifest();
			this.mAssetPackageCtx.mSingleDependencyGraph.BuildAssetBundle();
			this.mTestMain.run();
		}
    }
}