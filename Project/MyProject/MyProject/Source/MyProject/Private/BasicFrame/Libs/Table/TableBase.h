#ifndef __TableBase_H_
#define __TableBase_H_

#include "string"
#include "vector"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class TableItemBase;
class MByteBuffer;

class TableBase
{
public:
	std::string mResName;
	std::string mTableName;      // 表的名字

	std::vector<TableItemBase*>* mList;
    MByteBuffer* mByteBuffer;      // 整个表格所有的原始数据

public:
	TableBase(std::string resname, std::string tablename);
};

MY_END_NAMESPACE

#endif