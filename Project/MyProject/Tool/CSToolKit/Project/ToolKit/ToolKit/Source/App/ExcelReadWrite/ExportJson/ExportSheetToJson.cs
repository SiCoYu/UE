using SDK.Lib;

namespace ToolSet
{
    public class ExportSheetToJson : ExportSheetToCuctom
    {
        protected bool mIsExportNumNeedQuotation;     // 就是是否导出数字的时候是否加引号

        public ExportSheetToJson()
        {
            this.mIsExportNumNeedQuotation = true;
        }

        public bool isExportNumNeedQuotation()
        {
            return this.mIsExportNumNeedQuotation;
        }

        public void setIsExportNumNeedQuotation(bool value)
        {
            this.mIsExportNumNeedQuotation = value;
        }

        override public void _exportImpl()
        {
            if(null == this.mFileStream)
            {
                this.mFileStream = new MFileStream(this.mOutJsonPath, null, MFileMode.eCreate, MFileAccess.eWrite);
                this.mFileStream.open();
            }

            // 这个工具检查这种 json 是正确的，但是 js 解析错误
            // https://www.bejson.com/jsonviewernew/
            // {"Items":[{"keyA":"valueIntA", "keyB":"valueStrB",}, {"keyC":"valueIntC", "keyD":"valueStrD",},]}
            // js 需要改写成如下
            // {"Items":[{"keyA":"valueIntA", "keyB":"valueStrB"}, {"keyC":"valueIntC", "keyD":"valueStrD"}]}
            //this.mFileStream.writeLine("{\"Items\":[");
            this.mFileStream.writeLine("{\"" + this.mTableSheet.getTableFileNameNoExt() + "\":[");

            int rowIndex = 0;
            int rowLen = this.mTableSheet.getTableBodyRowCount();

            int columnIndex = 0;
            int columnLen = this.mTableSheet.getTableBodyColumnCount();

            AuxPropertyBase property = null;
            TableHeadItem tableHeadItem = null;

            string rowJsonStr = "";

            while (rowIndex < rowLen)
            {
                columnIndex = 0;
                rowJsonStr = "{";

                while (columnIndex < columnLen)
                {
                    tableHeadItem = this.mTableSheet.getTableHeadItemByColumnIndex(columnIndex);

                    property = this.mTableSheet.getPropertyByIndex(
                        rowIndex,
                        columnIndex
                    );

                    if (columnIndex + 1 < columnLen)
                    {
                        if (tableHeadItem.isNumFieldType())
                        {
                            if(this.mIsExportNumNeedQuotation)
                            {
                                rowJsonStr += ("\"" + tableHeadItem.getFieldName() + "\":\"" + property.toStrValue() + "\",");
                            }
                            else
                            {
                                rowJsonStr += ("\"" + tableHeadItem.getFieldName() + "\":" + property.toStrValue() + ",");
                            }
                        }
                        else
                        {
                            rowJsonStr += ("\"" + tableHeadItem.getFieldName() + "\":\"" + property.toStrValue() + "\",");
                        }
                    }
                    else
                    {
                        if (tableHeadItem.isNumFieldType())
                        {
                            if(this.mIsExportNumNeedQuotation)
                            {
                                rowJsonStr += ("\"" + tableHeadItem.getFieldName() + "\":\"" + property.toStrValue() + "\"");
                            }
                            else
                            {
                                rowJsonStr += ("\"" + tableHeadItem.getFieldName() + "\":" + property.toStrValue() + "");
                            }
                        }
                        else
                        {
                            rowJsonStr += ("\"" + tableHeadItem.getFieldName() + "\":\"" + property.toStrValue() + "\"");
                        }
                    }

                    columnIndex += 1;
                }

                if (rowIndex + 1 < rowLen)
                {
                    rowJsonStr += "},";
                }
                else
                {
                    rowJsonStr += "}";
                }

                this.mFileStream.writeLine(rowJsonStr);

                rowIndex += 1;
            }

            this.mFileStream.writeText("]}");

            this.mFileStream.dispose();
            this.mFileStream = null;
        }
    }
}