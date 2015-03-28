#ifndef __TableID_H_
#define __TableID_H_

#include <map>
#include "TableID.h"

class TableBase;
class TableItemBase;

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
	std::map<TableID, TableBase*> m_dicTable;
	IResItem m_res;
	ByteBuffer* m_byteBuffer;

	TableSys();
    // 返回一个表
	List<TableItemBase*> getTable(TableID tableID);
    // 返回一个表中一项，返回的时候表中数据全部加载到 Item 中
	TableItemBase getItem(TableID tableID, uint itemID);
    // 加载一个表
	void loadOneTable(TableID tableID);
    // 加载一个表完成
	void onloaded(IDispatchObject resEvt);
    // 根据路径查找表的 ID
	TableID getTableIDByPath(std::string path);
    // 加载一个表中一项的所有内容
	void loadOneTableOneItemAll(TableID tableID, TableBase* table, TableItemBase* itemBase);
    // 获取一个表的名字
	string getTableName(TableID tableID);
    // 读取一个表，仅仅读取表头
	void readTable(TableID tableID, ByteBuffer* bytes);
    // 查找表中的一项
	static TableItemBase* findDataItem(TableBase* table, uint32 id);
};

#endif