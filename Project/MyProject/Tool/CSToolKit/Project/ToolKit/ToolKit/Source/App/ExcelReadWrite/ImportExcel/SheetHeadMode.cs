namespace ToolSet
{
    public enum SheetHeadMode
    {
        eNull = 0,              // 没有表头
        eA_Type_B_Name = 1,     // 三行表头，第一行是表的符号名字，第二行是描述，第三行是类型
        eA_Type = 2,            // 第一行表头，一行是表的符号名字
    }
}