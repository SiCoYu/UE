#ifndef __RefCountResLoadResultNotify_H
#define __RefCountResLoadResultNotify_H

#include "ResLoadResultNotify.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class RefCount;

/**
 * @brief 引用计数资源加载结果通知
 */
class RefCountResLoadResultNotify : public ResLoadResultNotify
{
protected:
	RefCount* mRefCount;                  // 引用计数

public:
	RefCountResLoadResultNotify();
	virtual ~RefCountResLoadResultNotify();

	void init();
	void dispose();

	RefCount* getRefCount();
	void setRefCount(RefCount* value);
	virtual void copyFrom(ResLoadResultNotify* rhv) override;
};

MY_END_NAMESPACE

#endif