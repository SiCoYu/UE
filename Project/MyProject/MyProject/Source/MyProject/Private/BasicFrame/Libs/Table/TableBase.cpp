#include "MyProject.h"
#include "TableBase.h"

#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryAlloc.h"

TableBase::TableBase(std::string resname, std::string tablename)
{
	this->mResName = resname;
	this->mTableName = tablename;

	this->mList = MY_NEW std::vector<TableItemBase*>();
	this->mByteBuffer = nullptr;
}