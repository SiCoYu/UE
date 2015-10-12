#include "MyProject.h"
#include "TableBase.h"

TableBase::TableBase(std::string resname, std::string tablename)
{
    m_resName = resname;
    m_tableName = tablename;

	m_List = new std::vector<TableItemBase*>();
	m_byteBuffer = nullptr;
}