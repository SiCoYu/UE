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
    m_dicTable[TableID::TABLE_OBJECT] = new TableBase("ObjectBase_client.bytes", "ObjectBase_client");
    m_dicTable[TableID::TABLE_CARD] = new TableBase("CardBase_client.bytes", "CardBase_client");
    m_dicTable[TableID::TABLE_SKILL] = new TableBase("SkillBase_client.bytes", "SkillBase_client");    // 添加一个表的步骤三

	m_byteBuffer = new ByteBuffer();
}

// 返回一个表
std::vector<TableItemBase*>* TableSys::getTable(TableID::TableID tableID)
{
	TableBase* table = m_dicTable[tableID];
	if (nullptr == table)
	{
		loadOneTable(tableID);
		table = m_dicTable[tableID];
	}
	return table->m_List;
}
		
// 返回一个表中一项，返回的时候表中数据全部加载到 Item 中
TableItemBase* TableSys::getItem(TableID::TableID tableID, uint32 itemID)
{
    TableBase* table = m_dicTable[tableID];
	if (nullptr == table->m_byteBuffer)
	{
		loadOneTable(tableID);
		table = m_dicTable[tableID];
	}
    TableItemBase* ret = TableSys::findDataItem(table, itemID);

	if (nullptr != ret && nullptr == ret->m_itemBody)
    {
        loadOneTableOneItemAll(tableID, table, ret);
    }

    if (nullptr == ret)
    {
		g_pLogSys->log(UtilStr::Format("table name: {0}, table Item {1} 加载失败", (int)tableID, itemID));
    }

	return ret;
}
		
// 加载一个表
void TableSys::loadOneTable(TableID::TableID tableID)
{
	m_byteBuffer->clear();
	m_arrayBuffer.Empty();
	TableBase* table = m_dicTable[tableID];

	FString Filename = FString::Printf(TEXT("%s%s%s%s"), *FPaths::GameContentDir(), TEXT("/Table/"), ANSI_TO_TCHAR(table->m_tableName.c_str()), TEXT(".txt"));

	if (FFileHelper::LoadFileToArray(m_arrayBuffer, *Filename))
	{
		m_byteBuffer->setLength(m_arrayBuffer.GetAllocatedSize());
		m_byteBuffer->writeBytes((char*)(m_arrayBuffer.GetData()), 0, m_arrayBuffer.GetAllocatedSize());
		m_byteBuffer->setPos(0);
		readTable(tableID, m_byteBuffer);
	}
}

// 根据路径查找表的 ID
TableID::TableID TableSys::getTableIDByPath(std::string& path)
{
	TableMapIte beginIte = m_dicTable.begin();
	TableMapIte endIte = m_dicTable.end();
	for(; beginIte != endIte; ++beginIte)
    {
		if (beginIte->second->m_resName == path)
        {
			return beginIte->first;
        }
    }

	return (TableID::TableID)0;
}

// 加载一个表中一项的所有内容
void TableSys::loadOneTableOneItemAll(TableID::TableID tableID, TableBase* table, TableItemBase* itemBase)
{
    if (TableID::TABLE_OBJECT == tableID)
    {
		itemBase->parseBodyByteBuffer<TableObjectItemBody>(table->m_byteBuffer, itemBase->m_itemHeader->m_offset);
    }
    else if (TableID::TABLE_CARD == tableID)
    {
		itemBase->parseBodyByteBuffer<TableCardItemBody>(table->m_byteBuffer, itemBase->m_itemHeader->m_offset);
    }
	else if (TableID::TABLE_SKILL == tableID)  // 添加一个表的步骤四
    {
		itemBase->parseBodyByteBuffer<TableSkillItemBody>(table->m_byteBuffer, itemBase->m_itemHeader->m_offset);
    }
}
		
// 获取一个表的名字
std::string& TableSys::getTableName(TableID::TableID tableID)
{
	TableBase* table = m_dicTable[tableID];
	if (nullptr != table)
	{
		return table->m_tableName;
	}			
	return UtilStr::m_sDefaultStr;
}

// 读取一个表，仅仅读取表头
void TableSys::readTable(TableID::TableID tableID, ByteBuffer* bytes)
{
    TableBase* table = m_dicTable[tableID];
	table->m_byteBuffer = bytes;

	bytes->setEndian(eLITTLE_ENDIAN);
	uint32 len = 0;
	bytes->readUnsignedInt32(len);
    uint32 i = 0;
    TableItemBase* item = nullptr;
    for (i = 0; i < len; i++)
    {
        //if (TableID.TABLE_OBJECT == tableID)
        //{
        //    item = new TableItemObject();
        //}
        item = new TableItemBase();
        item->parseHeaderByteBuffer(bytes);
        // 加载完整数据
        //loadOneTableOneItemAll(tableID, table, item);
        //if (TableID.TABLE_OBJECT == tableID)
        //{
            //item.parseAllByteArray<TableObjectItemBody>(bytes);
        //}
        table->m_List->push_back(item);
    }
}

// 查找表中的一项
TableItemBase* TableSys::findDataItem(TableBase* table, uint32 id)
{
	int size = table->m_List->size();
	int low = 0;
	int high = size - 1;
	int middle = 0;
	uint32 idCur = 0;
			
	while (low <= high)
	{
		middle = (low + high) / 2;
        idCur = (*(table->m_List))[middle]->m_itemHeader->m_uID;
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
        return (*(table->m_List))[middle];
	}
	return nullptr;
}