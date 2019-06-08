using SDK.Lib;

namespace ToolSet
{
    public class ExportCsv : ExportCustom
    {
        public ExportCsv()
        {

        }

        override public void onFileHandle(string srcFullPath, string fileName, string destFullPath)
        {
            string fileNameNoExt = UtilFileIO.getFileNameNoExt(fileName);
            string outJsonFile = UtilFileIO.combine(this.mJsonOutPath, fileNameNoExt + ".csv");

            System.Console.Write(srcFullPath + " Start" + " \n");

            if (UtilExcel.isExcelFile(fileName))
            {
                if (!UtilExcel.isExcelBakFile(fileName))
                {
                    ExportSheetToCsv exportSheetToCsv = new ExportSheetToCsv();
                    exportSheetToCsv.setOutJsonPath(outJsonFile);
                    exportSheetToCsv.setInTablePath(srcFullPath);
                    exportSheetToCsv.setTableSheetName("");
                    exportSheetToCsv.export();
                    exportSheetToCsv.dispose();
                    exportSheetToCsv = null;
                }
            }

            System.Console.Write(srcFullPath + " End \n");
        }
    }
}