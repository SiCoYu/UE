#include "MyProject.h"
#include "TableBase.h"

TableBase::TableBase(std::string resname, std::string tablename, std::string prefabname)
{
    m_resName = resname;
    m_tableName = tablename;
    m_prefabName = prefabname;

	m_List = new std::vector<TableItemBase>();
}