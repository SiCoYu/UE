#ifndef __TableSys_H
#define __TableSys_H

#include "MDictionary.h"
#include "MList.h"
#include <string>
#include "HAL/Platform.h"
#include "TableId.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

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
	typedef typename MDictionary<TableId, TableBase*>::Iterator TableMapIte;

private:
	MDictionary<TableId, TableBase*> mDicTable;
	MByteBuffer* mByteBuffer;
	TArray<uint8> mArrayBuffer;

public:
	TableSys();
	~TableSys();

public:
	void init();
	void dispose();

    // 返回一个表
	MList<TableItemBase*>* getTable(TableId tableId);
    // 返回一个表中一项，返回的时候表中数据全部加载到 Item 中
	TableItemBase* getItem(TableId tableId, uint32 itemID);
    // 加载一个表
	void loadOneTable(TableId tableId);
    // 加载一个表完成
	//void onloaded(IDispatchObject resEvt);
    // 根据路径查找表的 Id
	TableId getTableIDByPath(std::string& path);
    // 加载一个表中一项的所有内容
	void loadOneTableOneItemAll(TableId tableId, TableBase* table, TableItemBase* itemBase);
    // 获取一个表的名字
	std::string& getTableName(TableId tableId);
    // 读取一个表，仅仅读取表头
	void readTable(TableId tableId, MByteBuffer* bytes);
    // 查找表中的一项
	static TableItemBase* findDataItem(TableBase* table, uint32 id);
};

MY_END_NAMESPACE

#endif