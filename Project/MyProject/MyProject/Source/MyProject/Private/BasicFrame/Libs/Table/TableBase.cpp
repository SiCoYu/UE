#include "MyProject.h"
#include "TableBase.h"

TableBase::TableBase(std::string resname, std::string tablename)
{
	this->mResName = resname;
	this->mTableName = tablename;

	this->mList = new std::vector<TableItemBase*>();
	this->mByteBuffer = nullptr;
}