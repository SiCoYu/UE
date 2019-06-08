using SDK.Lib;

namespace ToolSet
{
    /**
     * @brief Excel 工具
     */
    public class UtilExcel
    {
        // 传入的是文件名字，没有目录
        public static bool isExcelFile(string fileName)
        {
            bool ret = false;

            string fileExtName = UtilFileIO.getFileExt(fileName);

            if ("xls" == fileExtName || "xlsx" == fileExtName)
            {
                ret = true;
            }

            return ret;
        }

        // 传入的是文件名字，没有目录
        public static bool isExcelBakFile(string fileName)
        {
            bool ret = false;

            // Excel 如果打开会生成一个前缀是 ~$ 的备份文件，这个文件也不要导出
            string prefixFileName = "";
            prefixFileName = fileName.Substring(0, 2);

            if ("~$" == prefixFileName)
            {
                ret = true;
            }

            return ret;
        }
    }
}