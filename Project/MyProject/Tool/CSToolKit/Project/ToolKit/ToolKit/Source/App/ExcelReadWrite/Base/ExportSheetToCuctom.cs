using SDK.Lib;

namespace ToolSet
{
    public class ExportSheetToCuctom
    {
        protected TableSheet mTableSheet;
        protected MFileStream mFileStream;
        protected string mOutJsonPath;

        public ExportSheetToCuctom()
        {
            this.mTableSheet = new TableSheet();
            this.mFileStream = null;
            this.mOutJsonPath = "G:/File/opensource/unity-game-git/MaYun/UnityGameOne/Tools/CSExcelExport/ExcelExport/Excel/aaa.json";
        }

        public void init()
        {
            this.mTableSheet.init();
        }

        public void dispose()
        {
            this.mTableSheet.dispose();
            this.mTableSheet = null;
        }

        public void setOutJsonPath(string value)
        {
            this.mOutJsonPath = value;
        }

        public void setInTablePath(string value)
        {
            this.mTableSheet.setTablePath(value);
        }

        public void setTableSheetName(string value)
        {
            this.mTableSheet.setTableSheetName(value);
        }

        public void setSheetHeadMode(SheetHeadMode value)
        {
            this.mTableSheet.setSheetHeadMode(value);
        }

        virtual public void _exportImpl()
        {
            
        }

        public void export()
        {
            System.Console.Write("openTable" + " \n");
            this.mTableSheet.openTable();
            System.Console.Write("readTable" + " \n");
            this.mTableSheet.readTable();

            System.Console.Write("_exportImpl" + " \n");
            this._exportImpl();
        }
    }
}