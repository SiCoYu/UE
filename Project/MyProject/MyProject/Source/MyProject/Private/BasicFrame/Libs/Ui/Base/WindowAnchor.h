#ifndef __WindowAnchor_H
#define __WindowAnchor_H

#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 *@brief 窗口定锚
 */
enum WindowAnchor
{
	LEFT = 0,       //居左
	CENTER = 1,     //居中(横向和纵向都用此值)
	RIGHT = 2,      //居右

	TOP = 0,        //居上
	BOTTOM = 2,     //居下
};

MY_END_NAMESPACE

#endif