#pragma once

#include "MClassInfo.h"
#include "MClassMacros.h"

//***************** 各种接口 ************
// 接口不能有虚函数，不能有任何内容，内容都定义在 GObject 里面，为了做到和 C 内存布局兼容，减少 RTTI \ dynamic_cast 依赖

#include "ITickedObject.h"
#include "IDispatchObject.h"
#include "INoOrPriorityObject.h"
#include "IDelayHandleItem.h"

#include "TickMode.h"

//***************************************

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class GObjectBase : public ITickedObject, public IDispatchObject, public INoOrPriorityObject, public IDelayHandleItem
{
	M_DECLARE_ROOT_CLASS(GObjectBase)

public:
	GObjectBase();

	// ITickedObject
	virtual void onTick(float delta, TickMode tickMode);

	// IDispatchObject

	// INoOrPriorityObject

	// IDelayHandleItem

protected:
	virtual ~GObjectBase();
};

MY_END_NAMESPACE