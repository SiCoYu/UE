#ifndef __TableBase_H_
#define __TableBase_H_

#include "string"
#include "vector"

class TableItemBase;
class ByteBuffer;

class TableBase
{
public:
	std::string m_resName;
	std::string m_tableName;      // 表的名字

	std::vector<TableItemBase*>* m_List;
    ByteBuffer* m_byteBuffer;      // 整个表格所有的原始数据

public:
	TableBase(std::string resname, std::string tablename);
};

#endif