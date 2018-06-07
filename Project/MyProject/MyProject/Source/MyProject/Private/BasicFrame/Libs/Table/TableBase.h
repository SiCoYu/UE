#ifndef __TableBase_H_
#define __TableBase_H_

#include <string>
#include "MList.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class TableItemBase;
class MByteBuffer;

class TableBase : public GObject
{
public:
	std::string mResName;
	std::string mTableName;      // 表的名字

	MList<TableItemBase*>* mList;
    MByteBuffer* mByteBuffer;      // 整个表格所有的原始数据

public:
	TableBase(std::string resname, std::string tablename);
};

MY_END_NAMESPACE

#endif