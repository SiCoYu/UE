#ifndef __TableID_H_
#define __TableID_H_

#include <map>

/**
    * @brief 添加一个表的步骤总共分 4 步
    * // 添加一个表的步骤一
    * // 添加一个表的步骤二
    * // 添加一个表的步骤三
    * // 添加一个表的步骤四
    */
class TableSys
{
private:
	std::map<TableID, TableBase> m_dicTable;
	IResItem m_res;
    ByteArray m_byteArray;

	public TableSys();
    // 返回一个表
	public List<TableItemBase> getTable(TableID tableID);
    // 返回一个表中一项，返回的时候表中数据全部加载到 Item 中
	public TableItemBase getItem(TableID tableID, uint itemID);
    // 加载一个表
	public void loadOneTable(TableID tableID);
    // 加载一个表完成
	public void onloaded(IDispatchObject resEvt);
    // 根据路径查找表的 ID
	protected TableID getTableIDByPath(std::string path);
    // 加载一个表中一项的所有内容
	public void loadOneTableOneItemAll(TableID tableID, TableBase table, TableItemBase itemBase);
    // 获取一个表的名字
	public string getTableName(TableID tableID);
    // 读取一个表，仅仅读取表头
	private void readTable(TableID tableID, ByteBuffer* bytes);
    // 查找表中的一项
	static public TableItemBase findDataItem(TableBase table, uint32 id);
};

#endif