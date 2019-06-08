using SDK.Lib;

namespace ToolSet
{
    public class TableSheet
    {
        protected TableHead mTableHead;
        protected TableBody mTableBody;

        protected ExcelReader mExcelReader;
        protected string mTablePath;
        protected string mTableSheetName;
        protected SheetHeadMode mSheetHeadMode;

        public TableSheet()
        {
            this.mTableHead = new TableHead();
            this.mTableBody = new TableBody();
            this.mExcelReader = new ExcelReader();

            this.mTablePath = "G:/File/opensource/unity-game-git/MaYun/UnityGame/Tools/CSExcelExport/ExcelExport/Excel/Test.xlsx";
            this.mTableSheetName = "TestSheet";
            this.mSheetHeadMode = SheetHeadMode.eA_Type_B_Name;
        }

        public void init()
        {
            this.mTableHead.init();
            this.mTableBody.init();
            this.mExcelReader.init();
        }

        public void dispose()
        {
            this.mTableHead.dispose();
            this.mTableHead = null;
            this.mTableBody.dispose();
            this.mTableBody = null;
            this.mExcelReader.dispose();
            this.mExcelReader = null;
        }

        public SheetHeadMode getSheetHeadMode()
        {
            return this.mSheetHeadMode;
        }

        public void setSheetHeadMode(SheetHeadMode value)
        {
            this.mSheetHeadMode = value;
        }

        public TableHead getTableHead()
        {
            return this.mTableHead;
        }

        public TableBody getTableBody()
        {
            return this.mTableBody;
        }

        public int getTableBodyRowCount()
        {
            return this.mTableBody.getRowCount();
        }

        public int getTableBodyColumnCount()
        {
            return this.mTableHead.getItemCount();
        }

        public AuxPropertyBase getPropertyByIndex(int rowIndex, int columnIndex)
        {
            return this.mTableBody.getPropertyByIndex(
                rowIndex,
                columnIndex
            );
        }

        public TableBodyRow getTableBodyRowByIndex(int rowIndex)
        {
            return this.mTableBody.getTableBodyRowByIndex(
                rowIndex
            );
        }

        public void addHeadItem(string fieldExplain, string fieldName, string fieldTypeName)
        {
            TableHeadItem item = new TableHeadItem();
            this.mTableHead.addTableHeadItem(item);

            item.setFieldExplain(fieldExplain);
            item.setFieldName(fieldName);
            item.setFieldTypeName(fieldTypeName);

            item.init();

            item.setFieldType(
                (CtxExt.msInstance as CtxExt).mExcelCtx.mFieldFactory.getFieldTypeByFieldTypeName(fieldTypeName)
                );
        }

        public void setTablePath(string path)
        {
            this.mTablePath = path;
        }

        public string getTableFileNameNoExt()
        {
            string ret = "";

            ret = UtilFileIO.getFileNameNoExt(this.mTablePath);

            return ret;
        }

        public void setTableSheetName(string path)
        {
            this.mTableSheetName = path;
        }

        public TableHeadItem getTableHeadItemByColumnIndex(int columnIndex)
        {
            TableHeadItem item = null;

            item = mTableHead.getTableHeadItemByColumnIndex(columnIndex);

            return item;
        }

        public void _readTableHead()
        {
            int columnCount = this.mExcelReader.getColumnCount();
            int index = 0;

            object checkFieldValue = null;  // 返回值需要检查
            string fieldExplain = "";
            string fieldName = "";
            string fieldTypeName = "";

            // 读取字段名字
            while (index < columnCount)
            {
                // 检查第一个值，有些列是添加的空白列，这些列是没有用的，直接忽略过去，只要检查最顶上的一行对应的当前列就行了，如果这个是空，就说明这一列是没有内容的
                checkFieldValue = this.mExcelReader.getGridDataByRowColumn(
                    0,
                    index
                );

                if (checkFieldValue != System.DBNull.Value)
                {
                    if (SheetHeadMode.eA_Type_B_Name == this.mSheetHeadMode)
                    {
                        // 列说明
                        fieldExplain = (string)this.mExcelReader.getGridDataByRowColumn(
                            2,
                            index
                        );

                        // 列字段名字
                        fieldName = (string)this.mExcelReader.getGridDataByRowColumn(
                            1,
                            index
                        );

                        // 列字段类型
                        fieldTypeName = (string)this.mExcelReader.getGridDataByRowColumn(
                            0,
                            index
                        );
                    }
                    else if (SheetHeadMode.eA_Type == this.mSheetHeadMode)
                    {
                        fieldExplain = "not define";
                        fieldTypeName = "not define";

                        // 列字段名字
                        fieldName = (string)this.mExcelReader.getGridDataByRowColumn(
                            0,
                            index
                        );
                    }
                    else
                    {
                        fieldExplain = "not define";
                        fieldName = "not define";
                        fieldTypeName = "not define";
                    }

                    this.addHeadItem(fieldExplain, fieldName, fieldTypeName);
                }
                else
                {
                    // 遇到表头第一个为 null 的，后面的就不要读取了，因为读取表数据的时候可能会发生错乱
                    System.Console.Write(index.ToString() + " is null, skip after all" + " \n");
                    break;
                }

                index += 1;
            }
        }

        public void _readTableBody()
        {
            // 去掉字段名字和字段类型两行
            int rowCount = this.mExcelReader.getRowCount();
            int rowIndex = 0;

            if (SheetHeadMode.eA_Type_B_Name == this.mSheetHeadMode)
            {
                // 跳过 3 行表头
                rowIndex = 3;
            }
            else if (SheetHeadMode.eA_Type == this.mSheetHeadMode)
            {
                // 跳过 1 行表头
                rowIndex = 1;
            }
            else
            {
                // 没有表头
                rowIndex = 0;
            }

            // 读取表格数据，不要从原始表中获取列数量，因为可能表里面有空列
            //int columnCount = this.mExcelReader.getColumnCount();
            int columnCount = this.getTableBodyColumnCount();
            int columnIndex = 0;

            string fieldValue = "";
            TableHeadItem tableHeadItem = null;
            AuxPropertyBase property = null;
            object gridValue = null;

            while (rowIndex < rowCount)
            {
                columnIndex = 0;

                while(columnIndex < columnCount)
                {
                    gridValue = this.mExcelReader.getGridDataByRowColumn(rowIndex, columnIndex);

                    tableHeadItem = this.getTableHeadItemByColumnIndex(columnIndex);

                    //if (!(gridValue is System.DBNull))
                    if (!(gridValue == System.DBNull.Value))
                    {
                        fieldValue = gridValue.ToString();      // 统一转换到字符串处理

                        property = (CtxExt.msInstance as CtxExt).mExcelCtx.mFieldFactory.getPropertyByFieldType(
                                tableHeadItem.getFieldType()
                            );

                        //this.mTableBody.addFieldByRowIndex(rowIndex, property);

                        if (FieldType.eInt == tableHeadItem.getFieldType())
                        {
                            property.setIntValue(MBitConverter.ToInt32(fieldValue));
                        }
                        else if (FieldType.eFloat == tableHeadItem.getFieldType())
                        {
                            property.setFloatValue(MBitConverter.ToSingle(fieldValue));
                        }
                        else if (FieldType.eStr == tableHeadItem.getFieldType())
                        {
                            property.setStrValue(fieldValue);
                        }
                    }
                    else
                    {
                        // 如果第一个 Key 没有，就跳过这一行
                        if(0 == columnIndex)
                        {
                            break;
                        }
                        else
                        {
                            // 加入属性默认值
                            property = (CtxExt.msInstance as CtxExt).mExcelCtx.mFieldFactory.getPropertyByFieldType(
                                tableHeadItem.getFieldType()
                            );

                            //this.mTableBody.addFieldByRowIndex(rowIndex, property);

                            // 默认属性值就行了

                            //columnIndex += 1;
                            //continue;
                        }
                    }

                    this.mTableBody.addFieldByRowIndex(rowIndex, property);
                    columnIndex += 1;
                }

                rowIndex += 1;
            }
        }

        public void openTable()
        {
            this.mExcelReader.openExcelTableByOleDB(this.mTablePath, this.mTableSheetName);
            //this.mExcelReader.getGridDataByRowColumn(2, 1);
            //this.mExcelReader.getGridDataByRowColumn(3, 1);
        }

        public void readTable()
        {
            this._readTableHead();
            this._readTableBody();
        }
    }
}