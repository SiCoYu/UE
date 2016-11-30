#ifndef __RefCount_H
#define __RefCount_H

#include "Platform.h"

/**
 * @brief 脚本引用计数
 */
class RefCount
{
protected:
	uint32 m_refNum;                // 引用计数

public:
	RefCount();
	uint32 getRefNum();
	void setRefNum(int32 value);
	void reset();
	void incRef();
	void decRef();
	bool bNoRef();
    void copyFrom(RefCount* rhv);
};

#endif