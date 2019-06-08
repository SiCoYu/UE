using System.Collections.Generic;
using System.Data;
using System.Data.OleDb;

namespace ToolSet
{
    /**
     * @url http://www.jb51.net/article/74537.htm
     * 下面说明一下连接字符串
     * HDR=Yes，这代表第一行是标题，不做为数据使用（但是我在实际使用中，如果第一行存在复杂数值，那么读取得到的Datatable列标题会自动设置为F1、F2等方式命名，与实际应用不符，所以当时是通过HDR=No方式将所有内容读取到Datatable中，然后手动将第一行设置成标题的）；IMEX ( IMport EXport mode )设置
     * IMEX 有三种模式：
     * 0 is Export mode
     * 1 is Import mode
     * 2 is Linked mode (full update capabilities)
     * 我这里特别要说明的就是 IMEX 参数了，因为不同的模式代表著不同的读写行为：
     * 当 IMEX=0 时为“汇出模式”，这个模式开启的 Excel 档案只能用来做“写入”用途。
     * 当 IMEX=1 时为“汇入模式”，这个模式开启的 Excel 档案只能用来做“读取”用途。
     * 当 IMEX=2 时为“链接模式”，这个模式开启的 Excel 档案可同时支援“读取”与“写入”用途。
     * ---------------------------------
     * 另外，读取Excel2007版本的文件时，版本应该从8.0改为12.0，同时驱动不能再用Jet，而应该用ACE。负责会造成“找不到可安装的 ISAM”的错误。
     * @error 未在本地计算机上注册“Microsoft.ACE.OLEDB.12.0”提供程序
     * @url http://download.microsoft.com/download/7/0/3/703ffbcb-dc0c-4e19-b0da-1463960fdcdb/AccessDatabaseEngine.exe
     * @ref ExcelToLua工具
     * @url http://blog.csdn.net/u010223072/article/details/50184719
     * @ref 《Unity 3D游戏客户端基础框架》protobuf 导excel表格数据
     * @url http://blog.csdn.net/linshuhe1/article/details/52062969
     * @ref 将xls转成protobuf供Unity使用的流程
     * @url https://www.jianshu.com/p/b9b28f034cd8
     * @ref 我也贡献一个转表工具Excel=>protobuf二进制，json，xml，msgpack，javascript，lua
     * @brief 转表工具通过加载Excel和pb文件导出指定格式的数据。目前支持导出成protobuf二进制，msgpack二进制，javascript，xml，json和lua
     * @url http://www.cocoachina.com/bbs/read.php?tid=1679626
     * @error 如果后面添加的空行，也会算做内容，会导出表，如果表格单元中没有内容，必须填默认值
     * @brief 读取Excel，单元格内容大于255个字符自动被截取的问题
     * @url https://www.cnblogs.com/gskstudy/p/4223935.html
     * @error 受保护的视图， Office 已检测到此文件存在问题。编辑此文件可能会损害您的计算机。请单击查看详细信息。出现这个错误会导致数据不能读取，解决方法: 单击这行字，点击[仍然编辑受保护的视图]
     * @error External table is not in the expected format。 解决方法: 点击这句话-- 打开界面点击[仍然编辑]，一定要保存这个文件，否则还会有问题
     */
    public class ExcelReader
    {
        protected ExcelOpState mExcelOpState;   // 文件打开状态
        protected DataTable mDataTable;         // 数据表
        protected DataSet mDataSet;             // 数据集，所有数据表的集合
        protected OleDbConnection mOleDbConnection; // 数据库连接

        protected string mExcelFilePath;
        protected string mTableSheetName;
        protected string mErrorStr;
        protected bool mIsSequenceTableSheetName;   // 获取 Excel 中 Sheet 表名字的顺序，有些 Excel 中标的顺序是从前到后的，有些是从后到前的，不知道在哪可以设置表名字的顺序

        public ExcelReader()
        {
            this.mExcelOpState = ExcelOpState.eNull;
            this.mDataTable = null;
            this.mDataSet = null;
            this.mOleDbConnection = null;

            this.mExcelFilePath = "";
            this.mTableSheetName = "";
            this.mErrorStr = "";
            this.mIsSequenceTableSheetName = false;
        }

        public void init()
        {

        }

        public void dispose()
        {
            this.clear();
            //this.closeOleDbConnection();
        }

        public void clear()
        {
            this.mDataTable.Dispose();
            this.mDataTable = null;

            this.mDataSet.Dispose();
            this.mDataSet = null;
        }

        // 有错误
        public bool hasError()
        {
            return (!string.IsNullOrEmpty(this.mErrorStr));
        }

        protected string _getConnectionStringByExcelPath(string strExcelPath)
        {
            string connectionString = "";

            string strExtension = System.IO.Path.GetExtension(strExcelPath);

            switch (strExtension)
            {
                case ".xls":
                {
                    connectionString = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + strExcelPath + ";" + "Extended Properties=\"Excel 8.0;HDR=NO;IMEX=1;\"";

                    break;
                }
                case ".xlsx":
                {
                    connectionString = "Provider=Microsoft.ACE.OLEDB.12.0;Data Source=" + strExcelPath + ";" + "Extended Properties=\"Excel 12.0;HDR=NO;IMEX=1;\"";

                    break;
                }
                default:
                {
                    break;
                }
            }

            return connectionString;
        }

        public void openExcelTableByOleDB(string strExcelPath, string tableName)
        {
            try
            {
                this.mExcelFilePath = strExcelPath;

                this.mDataTable = new DataTable();
                this.mDataSet = new DataSet();

                //string oleDBTableName = string.Format("{0}$", tableName);
                string oleDBTableName = "";

                string strFileName = System.IO.Path.GetFileName(this.mExcelFilePath);
                string connectionString = "";
                connectionString = this._getConnectionStringByExcelPath(this.mExcelFilePath);

                if (!string.IsNullOrEmpty(connectionString))
                {
                    this.mOleDbConnection = new OleDbConnection(connectionString);

                    if (null != this.mOleDbConnection)
                    {
                        System.Console.Write("Open start" + " \n");

                        // 如果打开 Excel ，显示[受保护的视图 Office 已经检测到此文件存在问题。编辑此文件可能会损害您的计算机。请单机查看详细信息]，这个时候调用如下语句会抛出异常，异常信息系[External table is not in the expected format.], 解决方法: 点击这句话-- 打开界面点击[仍然编辑]，一定要保存这个文件，否则还会有问题
                        this.mOleDbConnection.Open();

                        System.Console.Write("Open end" + " \n");

                        if (string.IsNullOrEmpty(tableName))
                        {
                            // 默认获取第 0 个表单
                            List<string> sheetNameList = null;

                            if (this.mIsSequenceTableSheetName)
                            {
                                sheetNameList = this._getAllLegalSheetNameSequence();
                            }
                            else
                            {
                                sheetNameList = this._getAllLegalSheetNameInvertedSequence();
                            }

                            oleDBTableName = sheetNameList[0];
                            sheetNameList = null;
                        }
                        else
                        {
                            oleDBTableName = string.Format("{0}$", tableName);
                        }

                        System.Console.Write("TableName is " + oleDBTableName + " \n");

                        this.mTableSheetName = oleDBTableName;

                        string strSql = "select * from [" + oleDBTableName + "]\n";

                        //获取Excel指定Sheet表中的信息
                        OleDbCommand objCmd = new OleDbCommand(strSql, this.mOleDbConnection);
                        OleDbDataAdapter myData = new OleDbDataAdapter(strSql, this.mOleDbConnection);

                        System.Console.Write("Fill start" + " \n");

                        myData.Fill(this.mDataSet, oleDBTableName);      //填充数据
                        //this.mOleDbConnection.Close();    // 关闭的时候一起释放

                        System.Console.Write("Fill end" + " \n");

                        // this.mDataTable 即为 excel 文件中指定表中存储的信息
                        this.mDataTable = this.mDataSet.Tables[oleDBTableName];
                    }
                }
            }
            catch(System.Exception exp)
            {
                this.mErrorStr = exp.Message;
                // 打开失败
                System.Console.Write(exp.Message + " \n");
            }
        }

        /**
         * @brief 这个接口调用抛出异常
         * @bug Managed Debugging Assistant 'DisconnectedContext' has detected a problem in 'D:\File\Self\MaYun-UnityGameOne-git\UnityGameOne\Tools\CSExcelExport\ExcelExport\ExcelExport\bin\Debug\ConsoleApplication.vshost.exe'.

            Additional information: 针对此 RuntimeCallableWrapper 向 COM 上下文 0x1520d28 的转换失败，错误如下: 被调用的对象已与其客户端断开连接。 (异常来自 HRESULT:0x80010108 (RPC_E_DISCONNECTED))。原因通常是创建此 RuntimeCallableWrapper 的 COM 上下文 0x1520d28 已断开连接，或者该上下文正忙于执行其他操作。正在从当前 COM 上下文(COM 上下文 0x1520bb8)释放这些接口。这可能会导致损坏或数据丢失。要避免此问题，请确保在应用程序全部完成 RuntimeCallableWrapper (表示其内部的 COM 组件)之前，所有 COM 上下文/单元/线程都保持活动状态并可用于上下文转换。
         */
        public void closeOleDbConnection()
        {
            if (null != this.mOleDbConnection)
            {
                this.mOleDbConnection.Dispose();
                this.mOleDbConnection.Close();
                this.mOleDbConnection = null;
            }
        }

        public string getSheetNameByIndex(int index)
        {
            string sheetName = "";

            //获取Excel中所有Sheet表的信息
            System.Data.DataTable schemaTable = this.mOleDbConnection.GetOleDbSchemaTable(System.Data.OleDb.OleDbSchemaGuid.Tables, null);

            if (null != schemaTable &&
               schemaTable.Rows.Count > 0 &&
               schemaTable.Rows[0].ItemArray.Length > 2)
            {
                //获取Excel的第一个 Sheet 表名
                string tableName = schemaTable.Rows[0][2].ToString().Trim();
            }
            else
            {
                System.Console.Write("getSheetNameByIndex is 0" + " \n");
            }

            return sheetName;
        }

        // 获取合法的 Sheet 名字
        protected List<string> _getAllLegalSheetNameSequence()
        {
            // OleDbConnection 为读取 Excel 的链接，下面通过过滤来获取有效的Sheet页名称集合
            System.Data.DataTable schemaTable = this.mOleDbConnection.GetOleDbSchemaTable(System.Data.OleDb.OleDbSchemaGuid.Tables, null);

            List<string> sheetNameList = new List<string>();
            int index = 0;
            int listLen = schemaTable.Rows.Count;
            index = 0;

            // Excel 表中表单顺序好像与这里获取的索引的顺序是相反的，因此从后面向前面的遍历
            while (index < listLen)
            {
                string strSheetName = (string)schemaTable.Rows[index]["TABLE_NAME"];

                if (strSheetName.Contains("$") && !strSheetName.Replace("'", "").EndsWith("$"))
                {
                    // 过滤无效SheetName
                    continue;
                }
                if (!sheetNameList.Contains(strSheetName))
                {
                    sheetNameList.Add(strSheetName);
                }

                index += 1;
            }

            return sheetNameList;
        }

        protected List<string> _getAllLegalSheetNameInvertedSequence()
        {
            // OleDbConnection 为读取 Excel 的链接，下面通过过滤来获取有效的Sheet页名称集合
            System.Data.DataTable schemaTable = this.mOleDbConnection.GetOleDbSchemaTable(System.Data.OleDb.OleDbSchemaGuid.Tables, null);

            List<string> sheetNameList = new List<string>();
            int index = 0;
            int listLen = schemaTable.Rows.Count;
            index = listLen - 1;

            // Excel 表中表单顺序好像与这里获取的索引的顺序是相反的，因此从后面向前面的遍历
            while (index >= 0)
            {
                string strSheetName = (string)schemaTable.Rows[index]["TABLE_NAME"];

                if (strSheetName.Contains("$") && !strSheetName.Replace("'", "").EndsWith("$"))
                {
                    // 过滤无效SheetName
                    continue;
                }
                if (!sheetNameList.Contains(strSheetName))
                {
                    sheetNameList.Add(strSheetName);
                }

                index -= 1;
            }

            return sheetNameList;
        }

        public int getRowCount()
        {
            int ret = 0;

            DataRowCollection dataRowCollection = this.mDataTable.Rows;
            ret = dataRowCollection.Count;

            return ret;
        }

        public int getColumnCount()
        {
            int ret = 0;

            DataRowCollection dataRowCollection = this.mDataTable.Rows;

            if (dataRowCollection.Count > 0)
            {
                DataRow oneRowData = dataRowCollection[0];
                ret = oneRowData.ItemArray.Length;
            }
            else
            {
                System.Console.Write("getColumnCount is 0" + " \n");
            }

            return ret;
        }

        public object getGridDataByRowColumn(int row, int column)
        {
            object gridData = null;

            DataRowCollection dataRowCollection = this.mDataTable.Rows;

            if (dataRowCollection.Count > row)
            {
                DataRow oneRowData = dataRowCollection[row];

                if (oneRowData.ItemArray.Length > column)
                {
                    gridData = oneRowData[column];
                    //gridData = oneRowData.ItemArray[column];
                    //gridData = oneRowData[column, DataRowVersion.Original];
                }
                else
                {
                    System.Console.Write("getGridDataByRowColumn column 0" + " \n");
                }
            }
            else
            {
                System.Console.Write("getGridDataByRowColumn row 0" + " \n");
            }

            return gridData;
        }

        public string getExcelFirstTableName(OleDbConnection oleDbConnection)
        {
            string tableName = null;

            DataTable dt = oleDbConnection.GetOleDbSchemaTable(OleDbSchemaGuid.Tables, null);

            if (dt.Rows.Count > 0 && dt.Rows[0].ItemArray.Length > 2)
            {
                tableName = dt.Rows[0][2].ToString().Trim();
            }
            else
            {
                System.Console.Write("getExcelFirstTableName is 0" + " \n");
            }

            return tableName;
        }
    }
}