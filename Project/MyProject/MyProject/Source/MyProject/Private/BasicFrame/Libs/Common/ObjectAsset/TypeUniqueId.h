#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

GlobalNS.MLoader("Enum");

var M = GlobalNS.Enum();
M.clsName = "TypeUniqueId";
GlobalNS[M.clsName] = M;

M.eTypeUId_Prefab = 0;

MY_END_NAMESPACE