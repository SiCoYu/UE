#include "MyProject.h"
#include "TableSys.h"
#include "TableBase.h"
#include "TableItemBase.h"
#include "UtilStr.h"
#include "MEndian.h"
#include "TableObject.h"
#include "TableCard.h"
#include "TableSkill.h"
#include "TableItemHeader.h"
#include "TableItemBodyBase.h"
#include "MByteBuffer.h"
#include "Prequisites.h"
#include "UtilConvert.h"

MY_BEGIN_NAMESPACE(MyNS)

TableSys::TableSys()
{
	TableBase* tableBase = nullptr;
	TableId tableId;

	tableBase = MY_NEW TableBase("ObjectBase_client.bytes", "ObjectBase_client");
	tableId = TableId::TABLE_OBJECT;
	this->mDicTable[tableId] = tableBase;
	tableBase->init();

	tableBase = MY_NEW TableBase("CardBase_client.bytes", "CardBase_client");
	tableId = TableId::TABLE_CARD;
	this->mDicTable[tableId] = tableBase;
	tableBase->init();

	tableBase = MY_NEW TableBase("SkillBase_client.bytes", "SkillBase_client");
	tableId = TableId::TABLE_SKILL;
	this->mDicTable[tableId] = tableBase;    // 添加一个表的步骤三
	tableBase->init();

	this->mByteBuffer = MY_NEW MByteBuffer();
}

TableSys::~TableSys()
{

}

void TableSys::init()
{

}

void TableSys::dispose()
{
	TableMapIte curIte = this->mDicTable.begin();
	TableMapIte endIte = this->mDicTable.end();

	while (curIte != endIte)
	{
		MY_SAFE_DISPOSE(curIte->second);

		++curIte;
	}

	this->mDicTable.clear();

	MY_SAFE_DISPOSE(this->mByteBuffer);
}

// 返回一个表
MList<TableItemBase*>* TableSys::getTable(TableId tableId)
{
	TableBase* table = this->mDicTable[tableId];

	if (nullptr == table)
	{
		this->loadOneTable(tableId);
		table = this->mDicTable[tableId];
	}

	return table->mList;
}
		
// 返回一个表中一项，返回的时候表中数据全部加载到 Item 中
TableItemBase* TableSys::getItem(TableId tableId, uint32 itemId)
{
    TableBase* table = this->mDicTable[tableId];

	if (nullptr == table->mByteBuffer)
	{
		this->loadOneTable(tableId);
		table = this->mDicTable[tableId];
	}

    TableItemBase* ret = TableSys::findDataItem(table, itemId);

	if (nullptr != ret && nullptr == ret->mItemBody)
    {
		this->loadOneTableOneItemAll(tableId, table, ret);
    }

    if (nullptr == ret)
    {
		GLogSys->log(
			UtilStr::Format(
				"table name: {0}, table Item {1} load fail", 
				UtilConvert::convInt2Str((int)tableId),
				UtilConvert::convInt2Str(itemId)
			)
		);
    }

	return ret;
}
		
// 加载一个表
void TableSys::loadOneTable(TableId tableId)
{
	this->mByteBuffer->clear();
	this->mArrayBuffer.Empty();
	TableBase* table = this->mDicTable[tableId];

	// UE 4.19.1 warning C4996: 'FPaths::GameContentDir': FPaths::GameContentDir() has been superseded by FPaths::ProjectContentDir(). Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
	//FString Filename = FString::Printf(TEXT("%s%s%s%s"), *FPaths::GameContentDir(), TEXT("/MyAsset/Table/"), ANSI_TO_TCHAR(table->mTableName.c_str()), TEXT(".txt"));
	FString Filename = FString::Printf(TEXT("%s%s%s%s"), *FPaths::ProjectContentDir(), TEXT("/MyAsset/Table/"), ANSI_TO_TCHAR(table->mTableName.c_str()), TEXT(".txt"));

	if (FFileHelper::LoadFileToArray(mArrayBuffer, *Filename))
	{
		this->mByteBuffer->setLength(mArrayBuffer.GetAllocatedSize());
		this->mByteBuffer->writeBytes((char*)(this->mArrayBuffer.GetData()), 0, this->mArrayBuffer.GetAllocatedSize());
		this->mByteBuffer->setPos(0);
		this->readTable(tableId, mByteBuffer);
	}
}

// 根据路径查找表的 Id
TableId TableSys::getTableIDByPath(std::string& path)
{
	TableMapIte beginIte = this->mDicTable.getData().begin();
	TableMapIte endIte = this->mDicTable.getData().end();

	for(; beginIte != endIte; ++beginIte)
    {
		if (beginIte->second->mResName == path)
        {
			return beginIte->first;
        }
    }

	return (TableId)0;
}

// 加载一个表中一项的所有内容
void TableSys::loadOneTableOneItemAll(TableId tableId, TableBase* table, TableItemBase* itemBase)
{
    if (TableId::TABLE_OBJECT == tableId)
    {
		itemBase->parseBodyByteBuffer<TableObjectItemBody>(table->mByteBuffer, itemBase->mItemHeader->mOffset);
    }
    else if (TableId::TABLE_CARD == tableId)
    {
		itemBase->parseBodyByteBuffer<TableCardItemBody>(table->mByteBuffer, itemBase->mItemHeader->mOffset);
    }
	else if (TableId::TABLE_SKILL == tableId)  // 添加一个表的步骤四
    {
		itemBase->parseBodyByteBuffer<TableSkillItemBody>(table->mByteBuffer, itemBase->mItemHeader->mOffset);
    }
}
		
// 获取一个表的名字
std::string& TableSys::getTableName(TableId tableId)
{
	TableBase* table = this->mDicTable[tableId];

	if (nullptr != table)
	{
		return table->mTableName;
	}			

	return UtilStr::msDefaultStr;
}

// 读取一个表，仅仅读取表头
void TableSys::readTable(TableId tableId, MByteBuffer* bytes)
{
    TableBase* table = this->mDicTable[tableId];
	table->mByteBuffer = bytes;

	bytes->setEndian(MEndian::eLITTLE_ENDIAN);
	uint32 len = 0;
	bytes->readUnsignedInt32(len);
    uint32 i = 0;
    TableItemBase* item = nullptr;

    for (i = 0; i < len; i++)
    {
        //if (TableId.TABLE_OBJECT == tableId)
        //{
        //    item = new TableItemObject();
        //}
        item = MY_NEW TableItemBase();
        item->parseHeaderByteBuffer(bytes);
        // 加载完整数据
        //loadOneTableOneItemAll(tableId, table, item);
        //if (TableId.TABLE_OBJECT == tableId)
        //{
            //item.parseAllByteArray<TableObjectItemBody>(bytes);
        //}
        table->mList->add(item);
    }
}

// 查找表中的一项
TableItemBase* TableSys::findDataItem(TableBase* table, uint32 id)
{
	int size = table->mList->count();
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

MY_END_NAMESPACE