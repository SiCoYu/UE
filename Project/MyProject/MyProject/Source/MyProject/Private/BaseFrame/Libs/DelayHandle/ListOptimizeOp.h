#pragma once

#include "MClassInfo.h"
#include "MClassMacros.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 列表线性数据结构优化保存的数据，主要是索引
 */
class ListOptimizeOp : public GObject
{
	M_DECLARE_CLASS(ListOptimizeOp, GObject)

public:
	int mIndex;
};

MY_END_NAMESPACE