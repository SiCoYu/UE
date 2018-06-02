#ifndef __MEncode_H
#define __MEncode_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

enum class MEncode
{
	eUTF8,		// utf8 
	eGB2312 = 1,
	eUnicode = 2,
	eDefault = 3,
};

MY_END_NAMESPACE

#endif