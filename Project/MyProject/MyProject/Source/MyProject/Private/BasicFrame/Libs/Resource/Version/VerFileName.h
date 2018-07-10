#pragma once

#include <string>
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class VerFileName
{
public:
    static std::string VER_R = "Version_R.txt";
    static std::string VER_S = "Version_P.txt";       // "Version_S.txt"， 统一使用 "Version_P.txt"，方便制作版本
    static std::string VER_P = "Version_P.txt";
    static std::string VER_MINI = "Version_Mini.txt";
};

MY_END_NAMESPACE