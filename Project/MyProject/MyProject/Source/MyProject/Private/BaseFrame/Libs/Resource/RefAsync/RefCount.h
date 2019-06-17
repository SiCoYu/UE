#ifndef __RefCount_H
#define __RefCount_H

#include "Platform.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 脚本引用计数
 */
class RefCount : public GObject
{
protected:
	uint32 mRefNum;                // 引用计数

public:
	RefCount();

	void init();
	void dispose();

	uint32 getRefNum();
	void setRefNum(int32 value);
	void reset();
	void incRef();
	void decRef();
	bool isNoRef();
    void copyFrom(RefCount* rhv);
};

MY_END_NAMESPACE

#endif