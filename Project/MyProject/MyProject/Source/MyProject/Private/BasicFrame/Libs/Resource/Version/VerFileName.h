#pragma once

#include <string>
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class VerFileName : public GObject
{
public:
    static std::string VER_R;
    static std::string VER_S;       // "Version_S.txt"， 统一使用 "Version_P.txt"，方便制作版本
    static std::string VER_P;
    static std::string VER_MINI;
};

MY_END_NAMESPACE