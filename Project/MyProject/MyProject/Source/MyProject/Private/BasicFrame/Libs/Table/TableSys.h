#ifndef __TableSys_H
#define __TableSys_H

#include <map>
#include <vector>
#include <string>
#include "HAL/Platform.h"
#include "TableId.h"
#include "GObject.h"

class TableBase;
class TableItemBase;
class MByteBuffer;

/**
    * @brief 添加一个表的步骤总共分 4 步
    * // 添加一个表的步骤一
    * // 添加一个表的步骤二
    * // 添加一个表的步骤三
    * // 添加一个表的步骤四
    */
class TableSys : public GObject
{
	typedef std::map<TableId::TableId, TableBase*>::iterator TableMapIte;

private:
	std::map<TableId::TableId, TableBase*> mDicTable;
	MByteBuffer* mByteBuffer;
	TArray<uint8> mArrayBuffer;

public:
	TableSys();
	~TableSys();

public:
	void init();
	void dispose();

    // 返回一个表
	std::vector<TableItemBase*>* getTable(TableId::TableId tableID);
    // 返回一个表中一项，返回的时候表中数据全部加载到 Item 中
	TableItemBase* getItem(TableId::TableId tableID, uint32 itemID);
    // 加载一个表
	void loadOneTable(TableId::TableId tableID);
    // 加载一个表完成
	//void onloaded(IDispatchObject resEvt);
    // 根据路径查找表的 Id
	TableId::TableId getTableIDByPath(std::string& path);
    // 加载一个表中一项的所有内容
	void loadOneTableOneItemAll(TableId::TableId tableID, TableBase* table, TableItemBase* itemBase);
    // 获取一个表的名字
	std::string& getTableName(TableId::TableId tableID);
    // 读取一个表，仅仅读取表头
	void readTable(TableId::TableId tableID, MByteBuffer* bytes);
    // 查找表中的一项
	static TableItemBase* findDataItem(TableBase* table, uint32 id);
};

#endif