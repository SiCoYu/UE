#include "MyProject.h"
#include "TableBase.h"

#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MyMemoryAlloc.h"

MY_BEGIN_NAMESPACE(MyNS)

TableBase::TableBase(std::string resname, std::string tablename)
{
	this->mResName = resname;
	this->mTableName = tablename;

	this->mList = MY_NEW MList<TableItemBase*>();
	this->mByteBuffer = nullptr;
}

void TableBase::init()
{

}

void TableBase::dispose()
{

}

MY_END_NAMESPACE