using SDK.Lib;

namespace ToolSet
{
    public class CtxExt : Ctx
    {
        public ExcelCtx mExcelCtx;
		public TestMain mTestMain;

        public CtxExt()
        {
			this.mTestMain = new TestMain();
		}

        public static Ctx instance()
        {
            if (null == Ctx.msInstance)
            {
                Ctx.msInstance = new CtxExt();
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