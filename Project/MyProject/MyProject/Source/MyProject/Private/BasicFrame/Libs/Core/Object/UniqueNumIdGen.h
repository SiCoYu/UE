#pragma once

#include <string>
#include "TypeDef.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class UniqueNumIdGen : public GObject
{
	M_DECLARE_CLASS(UniqueNumIdGen, GObject)

protected:
	uint mBaseId;
	uint mPreIdx;
	uint mCurId;

public:
	UniqueNumIdGen(uint baseUniqueId);
	
	uint genNewId();
	uint getCurId();
};

MY_END_NAMESPACE