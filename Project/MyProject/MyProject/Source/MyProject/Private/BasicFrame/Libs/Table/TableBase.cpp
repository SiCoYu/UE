#include "MyProject.h"
#include "TableBase.h"

TableBase::TableBase(std::string resname, std::string tablename)
{
    mResName = resname;
    mTableName = tablename;

	mList = new std::vector<TableItemBase*>();
	mByteBuffer = nullptr;
}