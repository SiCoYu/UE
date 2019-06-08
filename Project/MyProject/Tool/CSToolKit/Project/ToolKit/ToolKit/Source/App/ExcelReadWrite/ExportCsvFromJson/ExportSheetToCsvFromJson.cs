using SDK.Lib;

namespace ToolSet
{
    public class ExportSheetToCsvFromJson : ExportSheetToCuctom
    {
        protected ExportCsvFromJsonData mExportCsvFromJsonData;

        public ExportSheetToCsvFromJson()
        {

        }

        public void setExportCsvFromJsonData(ExportCsvFromJsonData value)
        {
            this.mExportCsvFromJsonData = value;
        }

        //override public void _exportImpl()
        //{
        //    if(null == this.mFileStream)
        //    {
        //        this.mFileStream = new MFileStream(this.mOutJsonPath, null, MFileMode.eCreate, MFileAccess.eWrite);
        //        this.mFileStream.open();
        //    }

        //    int rowIndex = 0;
        //    int rowLen = this.mTableSheet.getTableBodyRowCount();

        //    int columnIndex = 0;
        //    int columnLen = this.mTableSheet.getTableBodyColumnCount();

        //    AuxPropertyBase property = null;
        //    TableHeadItem tableHeadItem = null;

        //    string rowJsonStr = "";
        //    string propertyStr = "";

        //    JObject jsonObj = null;
        //    int index = 0;
        //    int listLen = 11;
        //    string key = "";

        //    JToken token = null;
        //    int packId = 0;
        //    int levelId = 0;

        //    while (rowIndex < rowLen)
        //    {
        //        columnIndex = 0;
        //        rowJsonStr = "";

        //        while (columnIndex < columnLen)
        //        {
        //            tableHeadItem = this.mTableSheet.getTableHeadItemByColumnIndex(columnIndex);

        //            property = this.mTableSheet.getPropertyByIndex(
        //                rowIndex,
        //                columnIndex
        //            );

        //            if (columnIndex + 1 < columnLen)
        //            {
        //                if (0 == columnIndex)
        //                {
        //                    rowJsonStr += property.toStrValue() + ",";
        //                }
        //            }
        //            else
        //            {
        //                if (1 == columnIndex)
        //                {
        //                    index = 0;

        //                    propertyStr = property.toStrValue();
        //                    propertyStr = UtilSysLibWrap.decodeURIParam(propertyStr);
        //                    jsonObj = UtilJson.convertStrToJson(propertyStr);

        //                    while(index < listLen)
        //                    {
        //                        key = "aa-" + index;
        //                        token = jsonObj.GetValue(key);

        //                        if (null != token)
        //                        {
        //                            packId = UtilJson.getJsonAttrIntFromTokenByName(token, "PackId");
        //                            levelId = UtilJson.getJsonAttrIntFromTokenByName(token, "LevelId");

        //                            rowJsonStr += packId + "=" + levelId;
        //                        }
        //                        else
        //                        {
        //                            rowJsonStr += "0=0";
        //                        }

        //                        if(index + 1 < listLen)
        //                        {
        //                            rowJsonStr += ",";
        //                        }

        //                        index += 1;
        //                    }
        //                }
        //            }

        //            columnIndex += 1;
        //        }

        //        if (rowIndex + 1 < rowLen)
        //        {

        //        }
        //        else
        //        {

        //        }

        //        this.mFileStream.writeLine(rowJsonStr);

        //        rowIndex += 1;
        //    }

        //    this.mFileStream.dispose();
        //    this.mFileStream = null;
        //}

        override public void _exportImpl()
        {
            //if (null == this.mFileStream)
            //{
            //    this.mFileStream = new MFileStream(this.mOutJsonPath, null, MFileMode.eCreate, MFileAccess.eWrite);
            //    this.mFileStream.open();
            //}

            int rowIndex = 0;
            int rowLen = this.mTableSheet.getTableBodyRowCount();

            int columnIndex = 0;
            int columnLen = this.mTableSheet.getTableBodyColumnCount();

            AuxPropertyBase property = null;
            TableHeadItem tableHeadItem = null;

            //string rowJsonStr = "";
            string propertyStr = "";
            string appId = "";
            string openId = "";
            string key = "";
            string value = "";
            string updateTime = "";

            //int index = 0;
            //int listLen = 0;

            //ExportCsvFromJsonData exportCsvFromJsonData = new ExportCsvFromJsonData();
            //OnePlayerInfo onePlayerInfo = null;

            while (rowIndex < rowLen)
            {
                //System.Console.Write("rowIndex = " + rowIndex + " \n");

                columnIndex = 0;
                //rowJsonStr = "";

                while (columnIndex < columnLen)
                {
                    //System.Console.Write("columnIndex = " + columnIndex + " \n");

                    tableHeadItem = this.mTableSheet.getTableHeadItemByColumnIndex(columnIndex);

                    property = this.mTableSheet.getPropertyByIndex(
                        rowIndex,
                        columnIndex
                    );

                    propertyStr = property.toStrValue();
                    propertyStr = UtilSysLibWrap.decodeURIParam(propertyStr);

                    if (0 == columnIndex)   // appId
                    {
                        appId = propertyStr;
                    }
                    if (1 == columnIndex)   // OpenId
                    {   
                        openId = propertyStr;
                    }
                    else if(2 == columnIndex)   // key
                    {
                        key = propertyStr;
                    }
                    else if (3 == columnIndex)  // value
                    {
                        value = propertyStr;
                    }
                    else if (5 == columnIndex)  // updateTime
                    {
                        updateTime = propertyStr;
                    }

                    columnIndex += 1;
                }

                // 保存数据
                if(!string.IsNullOrEmpty(openId) && 
                   !string.IsNullOrEmpty(key) &&
                   !string.IsNullOrEmpty(value))
                {
                    if(SerializeKey.BaseLevelInfo == key ||
                       SerializeKey.DailyLevelInfo == key ||
                       SerializeKey.Gold == key ||
                       SerializeKey.Star == key ||
                       SerializeKey.UpdateTime == key ||
                       SerializeKey.VersionAndGameId == key)
                    {
                        this.mExportCsvFromJsonData.addPlayerKeyValue(openId, key, value);
                        this.mExportCsvFromJsonData.addPlayerKeyValue(openId, SerializeKey.UpdateTime, updateTime);
                    }
                }

                rowIndex += 1;
            }

            // 序列化输出
            //rowJsonStr = exportCsvFromJsonData.toCsvHead();
            //this.mFileStream.writeLine(rowJsonStr);

            //index = 0;
            //listLen = exportCsvFromJsonData.count();

            //while(index < listLen)
            //{
            //    onePlayerInfo = exportCsvFromJsonData.getPlayerInfo(index);
            //    rowJsonStr = onePlayerInfo.toCsv();
            //    this.mFileStream.writeLine(rowJsonStr);

            //    index += 1;
            //}

            //this.mFileStream.dispose();
            //this.mFileStream = null;
        }
    }
}