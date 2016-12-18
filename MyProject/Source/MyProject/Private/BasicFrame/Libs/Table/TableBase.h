#ifndef __TableBase_H_
#define __TableBase_H_

#include "string"
#include "vector"

class TableItemBase;
class ByteBuffer;

class TableBase
{
public:
	std::string mResName;
	std::string mTableName;      // 表的名字

	std::vector<TableItemBase*>* mList;
    ByteBuffer* mByteBuffer;      // 整个表格所有的原始数据

public:
	TableBase(std::string resname, std::string tablename);
};

#endif