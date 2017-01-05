#ifndef __TableSys_H_
#define __TableSys_H_

#include <map>
#include <vector>
#include <string>
#include "HAL/Platform.h"
#include "TableID.h"

class TableBase;
class TableItemBase;
class ByteBuffer;

/**
    * @brief 添加一个表的步骤总共分 4 步
    * // 添加一个表的步骤一
    * // 添加一个表的步骤二
    * // 添加一个表的步骤三
    * // 添加一个表的步骤四
    */
class TableSys
{
	typedef std::map<TableID::TableID, TableBase*>::iterator TableMapIte;

private:
	std::map<TableID::TableID, TableBase*> mDicTable;
	ByteBuffer* mByteBuffer;
	TArray<uint8> mArrayBuffer;

public:
	TableSys();
	~TableSys();

public:
	void init();
	void dispose();

    // 返回一个表
	std::vector<TableItemBase*>* getTable(TableID::TableID tableID);
    // 返回一个表中一项，返回的时候表中数据全部加载到 Item 中
	TableItemBase* getItem(TableID::TableID tableID, uint32 itemID);
    // 加载一个表
	void loadOneTable(TableID::TableID tableID);
    // 加载一个表完成
	//void onloaded(IDispatchObject resEvt);
    // 根据路径查找表的 ID
	TableID::TableID getTableIDByPath(std::string& path);
    // 加载一个表中一项的所有内容
	void loadOneTableOneItemAll(TableID::TableID tableID, TableBase* table, TableItemBase* itemBase);
    // 获取一个表的名字
	std::string& getTableName(TableID::TableID tableID);
    // 读取一个表，仅仅读取表头
	void readTable(TableID::TableID tableID, ByteBuffer* bytes);
    // 查找表中的一项
	static TableItemBase* findDataItem(TableBase* table, uint32 id);
};

#endif