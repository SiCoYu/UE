using SDK.Lib;

namespace ToolSet
{
    public class ExportJson : ExportCustom
    {
        protected bool mIsExportNumNeedQuotation;     // 就是是否导出数字的时候是否加引号

        public ExportJson()
        {
            //this.mIsExportNumNeedQuotation = true;
            this.mIsExportNumNeedQuotation = false;
        }

        public bool isExportNumNeedQuotation()
        {
            return this.mIsExportNumNeedQuotation;
        }

        public void setIsExportNumNeedQuotation(bool value)
        {
            this.mIsExportNumNeedQuotation = value;
        }

        public override string getRootPath()
        {
            //return base.getRootPath();
            return @"F:\File\Work\Client-FlowFree-20180521\Design\QQPlay版配表";
        }

        override public void onFileHandle(string srcFullPath, string fileName, string destFullPath)
        {
            string fileNameNoExt = UtilFileIO.getFileNameNoExt(fileName);
            string outJsonFile = UtilFileIO.combine(this.mJsonOutPath, fileNameNoExt + ".json");

            System.Console.Write(srcFullPath + " Start" + " \n");

            if (UtilExcel.isExcelFile(fileName))
            {
                if (!UtilExcel.isExcelBakFile(fileName))
                {
                    ExportSheetToJson exportSheetToJson = new ExportSheetToJson();
                    exportSheetToJson.setOutJsonPath(outJsonFile);
                    exportSheetToJson.setInTablePath(srcFullPath);
                    exportSheetToJson.setTableSheetName("");
                    exportSheetToJson.setSheetHeadMode(SheetHeadMode.eA_Type_B_Name);
                    exportSheetToJson.setIsExportNumNeedQuotation(this.mIsExportNumNeedQuotation);
                    exportSheetToJson.export();
                    exportSheetToJson.dispose();
                    exportSheetToJson = null;
                }
            }

            System.Console.Write(srcFullPath + " End \n");
        }
    }
}