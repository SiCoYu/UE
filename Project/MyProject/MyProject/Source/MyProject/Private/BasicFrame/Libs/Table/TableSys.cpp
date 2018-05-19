#include "MyProject.h"
#include "TableSys.h"
#include "TableBase.h"
#include "TableItemBase.h"
#include "UtilStr.h"
#include "Endian.h"
#include "TableObject.h"
#include "TableCard.h"
#include "TableSkill.h"
#include "TableItemHeader.h"
#include "TableItemBodyBase.h"
#include "ByteBuffer.h"
#include "Common.h"

TableSys::TableSys()
{
	this->mDicTable[TableId::TABLE_OBJECT] = new TableBase("ObjectBase_client.bytes", "ObjectBase_client");
	this->mDicTable[TableId::TABLE_CARD] = new TableBase("CardBase_client.bytes", "CardBase_client");
	this->mDicTable[TableId::TABLE_SKILL] = new TableBase("SkillBase_client.bytes", "SkillBase_client");    // 添加一个表的步骤三

	this->mByteBuffer = new ByteBuffer();
}

TableSys::~TableSys()
{

}

void TableSys::init()
{

}

void TableSys::dispose()
{

}

// 返回一个表
std::vector<TableItemBase*>* TableSys::getTable(TableId::TableId tableID)
{
	TableBase* table = this->mDicTable[tableID];

	if (nullptr == table)
	{
		this->loadOneTable(tableID);
		table = this->mDicTable[tableID];
	}

	return table->mList;
}
		
// 返回一个表中一项，返回的时候表中数据全部加载到 Item 中
TableItemBase* TableSys::getItem(TableId::TableId tableID, uint32 itemID)
{
    TableBase* table = this->mDicTable[tableID];

	if (nullptr == table->mByteBuffer)
	{
		this->loadOneTable(tableID);
		table = this->mDicTable[tableID];
	}

    TableItemBase* ret = TableSys::findDataItem(table, itemID);

	if (nullptr != ret && nullptr == ret->mItemBody)
    {
		this->loadOneTableOneItemAll(tableID, table, ret);
    }

    if (nullptr == ret)
    {
		GLogSys->log(UtilStr::Format("table name: {0}, table Item {1} 加载失败", (int)tableID, itemID));
    }

	return ret;
}
		
// 加载一个表
void TableSys::loadOneTable(TableId::TableId tableID)
{
	this->mByteBuffer->clear();
	this->mArrayBuffer.Empty();
	TableBase* table = this->mDicTable[tableID];

	// UE 4.19.1 warning C4996: 'FPaths::GameContentDir': FPaths::GameContentDir() has been superseded by FPaths::ProjectContentDir(). Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//FString Filename = FString::Printf(TEXT("%s%s%s%s"), *FPaths::GameContentDir(), TEXT("/MyAsset/Table/"), ANSI_TO_TCHAR(table->mTableName.c_str()), TEXT(".txt"));
	FString Filename = FString::Printf(TEXT("%s%s%s%s"), *FPaths::ProjectContentDir(), TEXT("/MyAsset/Table/"), ANSI_TO_TCHAR(table->mTableName.c_str()), TEXT(".txt"));

	if (FFileHelper::LoadFileToArray(mArrayBuffer, *Filename))
	{
		this->mByteBuffer->setLength(mArrayBuffer.GetAllocatedSize());
		this->mByteBuffer->writeBytes((char*)(this->mArrayBuffer.GetData()), 0, this->mArrayBuffer.GetAllocatedSize());
		this->mByteBuffer->setPos(0);
		this->readTable(tableID, mByteBuffer);
	}
}

// 根据路径查找表的 Id
TableId::TableId TableSys::getTableIDByPath(std::string& path)
{
	TableMapIte beginIte = this->mDicTable.begin();
	TableMapIte endIte = this->mDicTable.end();

	for(; beginIte != endIte; ++beginIte)
    {
		if (beginIte->second->mResName == path)
        {
			return beginIte->first;
        }
    }

	return (TableId::TableId)0;
}

// 加载一个表中一项的所有内容
void TableSys::loadOneTableOneItemAll(TableId::TableId tableID, TableBase* table, TableItemBase* itemBase)
{
    if (TableId::TABLE_OBJECT == tableID)
    {
		itemBase->parseBodyByteBuffer<TableObjectItemBody>(table->mByteBuffer, itemBase->mItemHeader->mOffset);
    }
    else if (TableId::TABLE_CARD == tableID)
    {
		itemBase->parseBodyByteBuffer<TableCardItemBody>(table->mByteBuffer, itemBase->mItemHeader->mOffset);
    }
	else if (TableId::TABLE_SKILL == tableID)  // 添加一个表的步骤四
    {
		itemBase->parseBodyByteBuffer<TableSkillItemBody>(table->mByteBuffer, itemBase->mItemHeader->mOffset);
    }
}
		
// 获取一个表的名字
std::string& TableSys::getTableName(TableId::TableId tableID)
{
	TableBase* table = this->mDicTable[tableID];

	if (nullptr != table)
	{
		return table->mTableName;
	}			

	return UtilStr::msDefaultStr;
}

// 读取一个表，仅仅读取表头
void TableSys::readTable(TableId::TableId tableID, ByteBuffer* bytes)
{
    TableBase* table = this->mDicTable[tableID];
	table->mByteBuffer = bytes;

	bytes->setEndian(eLITTLE_ENDIAN);
	uint32 len = 0;
	bytes->readUnsignedInt32(len);
    uint32 i = 0;
    TableItemBase* item = nullptr;

    for (i = 0; i < len; i++)
    {
        //if (TableId.TABLE_OBJECT == tableID)
        //{
        //    item = new TableItemObject();
        //}
        item = new TableItemBase();
        item->parseHeaderByteBuffer(bytes);
        // 加载完整数据
        //loadOneTableOneItemAll(tableID, table, item);
        //if (TableId.TABLE_OBJECT == tableID)
        //{
            //item.parseAllByteArray<TableObjectItemBody>(bytes);
        //}
        table->mList->push_back(item);
    }
}

// 查找表中的一项
TableItemBase* TableSys::findDataItem(TableBase* table, uint32 id)
{
	int size = table->mList->size();
	int low = 0;
	int high = size - 1;
	int middle = 0;
	uint32 idCur = 0;
			
	while (low <= high)
	{
		middle = (low + high) / 2;
        idCur = (*(table->mList))[middle]->mItemHeader->mId;

		if (idCur == id)
		{
			break;
		}

		if (id < idCur)
		{
			high = middle - 1;
		}
		else
		{
			low = middle + 1;
		}
	}
			
	if (low <= high)
	{
        return (*(table->mList))[middle];
	}

	return nullptr;
}