#include "MyProject.h"
#include "TableBase.h"

TableBase::TableBase(std::string resname, std::string tablename)
{
	this->mResName = resname;
	this->mTableName = tablename;

	this->mList = MY_NEW std::vector<TableItemBase*>();
	this->mByteBuffer = nullptr;
}