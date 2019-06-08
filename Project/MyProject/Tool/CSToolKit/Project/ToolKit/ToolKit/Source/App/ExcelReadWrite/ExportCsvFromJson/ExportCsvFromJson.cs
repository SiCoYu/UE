using SDK.Lib;

namespace ToolSet
{
    public class ExportCsvFromJson : ExportCustom
    {
        protected ExportCsvFromJsonData mExportCsvFromJsonData;
        protected MFileStream mFileStream;
        protected string mOutJsonPath;
        protected string mOutOldVersionJsonPath;
        protected string mOutNewVersionJsonPath;
        protected string mOutDataBaseVersionJsonPath;

        public ExportCsvFromJson()
        {
            this.mExportCsvFromJsonData = new ExportCsvFromJsonData();
        }

        public override string getRootPath()
        {
            return @"F:\File\Work\Bak\newdata";
        }

        public override string getExportDirName()
        {
            return "server_csv";
        }

        protected void _setPath()
        {
            this.mRootPath = this.getRootPath();
            this.mJsonOutPath = UtilFileIO.combine(this.mRootPath, this.getExportDirName());
            UtilFileIO.clearOrCreateDirectory(this.mJsonOutPath);

            this.mOutJsonPath = UtilFileIO.combine(this.mJsonOutPath, "LianXianInfo.csv");
            this.mOutOldVersionJsonPath = UtilFileIO.combine(this.mJsonOutPath, "LianXianInfo_OldVersion.csv");
            this.mOutNewVersionJsonPath = UtilFileIO.combine(this.mJsonOutPath, "LianXianInfo_NewVersion.csv");
            this.mOutDataBaseVersionJsonPath = UtilFileIO.combine(this.mJsonOutPath, "LianXianInfo_DataBaseVersion.csv");
        }

        protected void _readAllTable()
        {
            int index = 0;
            int listLen = 32;
            string fileName = "";

            while (index < listLen)
            {
                fileName = (index + 1).ToString() + ".xls";

                this.onFileHandle(
                    //UtilFileIO.combine(this.mRootPath, (index + 1).ToString(), "store.xls"),
                    UtilFileIO.combine(this.mRootPath, fileName),
                    fileName,
                    ""
                );

                index += 1;
            }
        }

        protected void _exportNormal()
        {
            int index = 0;
            int listLen = 32;

            // 序列化输出
            System.Console.Write("Write Normal Csv start" + " \n");

            string rowJsonStr = "";
            OnePlayerInfo onePlayerInfo = null;

            if (null == this.mFileStream)
            {

                this.mFileStream = new MFileStream(this.mOutJsonPath, null, MFileMode.eCreate, MFileAccess.eWrite);
                this.mFileStream.open();
            }

            rowJsonStr = this.mExportCsvFromJsonData.toCsvHead();
            this.mFileStream.writeLine(rowJsonStr);

            index = 0;
            listLen = this.mExportCsvFromJsonData.count();

            while (index < listLen)
            {
                onePlayerInfo = this.mExportCsvFromJsonData.getPlayerInfo(index);
                rowJsonStr = onePlayerInfo.toCsv();
                this.mFileStream.writeLine(rowJsonStr);

                index += 1;
            }

            this.mFileStream.dispose();
            this.mFileStream = null;

            System.Console.Write("Write Normal Csv end" + " \n");
        }

        protected void _exportOldVersion()
        {
            int index = 0;
            int listLen = 0;

            // 序列化输出
            System.Console.Write("Write OldVersion Csv start" + " \n");

            string rowJsonStr = "";
            OnePlayerInfo onePlayerInfo = null;

            if (null == this.mFileStream)
            {

                this.mFileStream = new MFileStream(this.mOutOldVersionJsonPath, null, MFileMode.eCreate, MFileAccess.eWrite);
                this.mFileStream.open();
            }

            rowJsonStr = this.mExportCsvFromJsonData.toOldCsvHead();
            this.mFileStream.writeLine(rowJsonStr);

            index = 0;
            listLen = this.mExportCsvFromJsonData.count();

            while (index < listLen &&
                   !this.mExportCsvFromJsonData.isOldVersionCountGreatMax())
            {
                onePlayerInfo = this.mExportCsvFromJsonData.getPlayerInfo(index);

                if (!onePlayerInfo.isNewVersion())
                {
                    rowJsonStr = onePlayerInfo.toOldCsv();
                    this.mFileStream.writeLine(rowJsonStr);
                    this.mExportCsvFromJsonData.incCurOldVersionCount();
                }

                index += 1;
            }

            this.mFileStream.dispose();
            this.mFileStream = null;

            System.Console.Write("Write OldVersion Csv end" + " \n");
        }

        protected void _exportNewVersion()
        {
            int index = 0;
            int listLen = 0;

            // 序列化输出
            System.Console.Write("Write NewVersion Csv start" + " \n");

            string rowJsonStr = "";
            OnePlayerInfo onePlayerInfo = null;

            if (null == this.mFileStream)
            {

                this.mFileStream = new MFileStream(this.mOutNewVersionJsonPath, null, MFileMode.eCreate, MFileAccess.eWrite);
                this.mFileStream.open();
            }

            rowJsonStr = this.mExportCsvFromJsonData.toNewCsvHead();
            this.mFileStream.writeLine(rowJsonStr);

            index = 0;
            listLen = this.mExportCsvFromJsonData.count();

            while (index < listLen && 
                   !this.mExportCsvFromJsonData.isNewVersionCountGreatMax())
            {
                onePlayerInfo = this.mExportCsvFromJsonData.getPlayerInfo(index);

                if (onePlayerInfo.isNewVersion())
                {
                    rowJsonStr = onePlayerInfo.toNewCsv();
                    this.mFileStream.writeLine(rowJsonStr);
                    this.mExportCsvFromJsonData.incCurNewVersionCount();
                }

                index += 1;
            }

            this.mFileStream.dispose();
            this.mFileStream = null;

            System.Console.Write("Write NewVersion Csv end" + " \n");
        }

        protected void _exportDataBase()
        {
            int index = 0;
            int listLen = 0;

            // 序列化输出
            System.Console.Write("Write DataBase Csv start" + " \n");

            string rowJsonStr = "";
            OnePlayerInfo onePlayerInfo = null;

            if (null == this.mFileStream)
            {

                this.mFileStream = new MFileStream(this.mOutDataBaseVersionJsonPath, null, MFileMode.eCreate, MFileAccess.eWrite);
                this.mFileStream.open();
            }

            rowJsonStr = this.mExportCsvFromJsonData.toDataBaseHead();
            this.mFileStream.writeLine(rowJsonStr);

            index = 0;
            listLen = this.mExportCsvFromJsonData.count();

            while (index < listLen)
            {
                onePlayerInfo = this.mExportCsvFromJsonData.getPlayerInfo(index);

                if (onePlayerInfo.isTestId())
                {
                    rowJsonStr = onePlayerInfo.toDataBase();
                    this.mFileStream.writeLine(rowJsonStr);
                }

                index += 1;
            }

            this.mFileStream.dispose();
            this.mFileStream = null;

            System.Console.Write("Write DataBase Csv end" + " \n");
        }

        override public void export()
        {
            this._setPath();
            this._readAllTable();

            //this._exportNormal();
            //this._exportOldVersion();
            //this._exportNewVersion();
            this._exportDataBase();
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
                    if (UtilFileIO.existFile(srcFullPath))
                    {
                        ExportSheetToCsvFromJson exportSheetToCsv = new ExportSheetToCsvFromJson();
                        exportSheetToCsv.setOutJsonPath(outJsonFile);
                        exportSheetToCsv.setInTablePath(srcFullPath);
                        exportSheetToCsv.setTableSheetName("");
                        exportSheetToCsv.setSheetHeadMode(SheetHeadMode.eA_Type);
                        exportSheetToCsv.setExportCsvFromJsonData(this.mExportCsvFromJsonData);
                        exportSheetToCsv.export();
                        exportSheetToCsv.dispose();
                        exportSheetToCsv = null;
                    }
                    else
                    {
                        System.Console.Write(srcFullPath + " not exist\n");
                    }
                }
                else
                {
                    System.Console.Write(srcFullPath + " is excel bak file\n");
                }
            }
            else
            {
                System.Console.Write(srcFullPath + " not excel file\n");
            }

            System.Console.Write(srcFullPath + " End \n");
        }
    }
}