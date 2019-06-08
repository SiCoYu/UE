namespace ToolSet
{
    public class ExcelCtx
    {
        public FieldFactory mFieldFactory;
        public ExportJson mExportJson;
        public ExportCsv mExportCsv;

        public ExcelCtx()
        {

        }

        public void _preInit()
        {
            this.mFieldFactory = new FieldFactory();
            this.mExportJson = new ExportJson();
            this.mExportCsv = new ExportCsv();
        }

        public void _execInit()
        {
            this.mFieldFactory.init();
            this.mExportJson.init();
            this.mExportCsv.init();
        }

        public void _postInit()
        {

        }

        public void _preDispose()
        {

        }

        public void _execDispose()
        {
            this.mFieldFactory.dispose();
            this.mFieldFactory = null;
            this.mExportJson.dispose();
            this.mExportJson = null;
            this.mExportCsv.dispose();
            this.mExportCsv = null;
        }

        public void _postDispose()
        {

        }
    }
}
