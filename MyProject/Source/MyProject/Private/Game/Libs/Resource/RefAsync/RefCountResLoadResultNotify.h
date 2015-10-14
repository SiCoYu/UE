#ifndef __RefCountResLoadResultNotify_H
#define __RefCountResLoadResultNotify_H

#include "ResLoadResultNotify.h"

class RefCount;

/**
 * @brief 引用计数资源加载结果通知
 */
class RefCountResLoadResultNotify : public ResLoadResultNotify
{
protected:
	RefCount* m_refCount;                  // 引用计数

public:
	RefCountResLoadResultNotify();
	~RefCountResLoadResultNotify();

	RefCount* getRefCount();
	void setRefCount(RefCount* value);
	virtual void copyFrom(ResLoadResultNotify& rhv) override;
}

#endif