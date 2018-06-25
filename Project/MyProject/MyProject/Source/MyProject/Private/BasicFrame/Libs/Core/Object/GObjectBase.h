#pragma once

#include "MClassInfo.h"
#include "MClassMacros.h"

//***************** ���ֽӿ� ************
// �ӿڲ������麯�����������κ����ݣ����ݶ������� GObject ���棬Ϊ�������� C �ڴ沼�ּ��ݣ����� RTTI \ dynamic_cast ����

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