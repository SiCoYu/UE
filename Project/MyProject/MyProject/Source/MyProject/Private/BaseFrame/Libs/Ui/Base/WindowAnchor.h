#ifndef __WindowAnchor_H
#define __WindowAnchor_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 *@brief 窗口定锚
 */
enum class WindowAnchor
{
	eLEFT = 0,       //居左
	eCENTER = 1,     //居中(横向和纵向都用此值)
	eRIGHT = 2,      //居右

	eTOP = 0,        //居上
	eBOTTOM = 2,     //居下
};

MY_END_NAMESPACE

#endif