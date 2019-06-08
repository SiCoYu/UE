using SDK.Lib;

namespace ToolSet
{
    public class CtxExt : Ctx
    {
		static public CtxExt msExtInstance;

		public ProjectConfig mProjectConfig;
		public ExcelCtx mExcelCtx;
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
        }

        override protected void _execInit()
        {
            base._execInit();

			this.mProjectConfig.init();

			this.mExcelCtx._execInit();
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
			this.mTestMain.run();
		}
    }
}