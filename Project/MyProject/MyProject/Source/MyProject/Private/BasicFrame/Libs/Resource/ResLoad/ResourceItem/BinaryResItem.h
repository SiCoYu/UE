#ifndef __BinaryResItem_H
#define __BinaryResItem_H

#include "ResItem.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @brief 文本或者二进制数据
 */
class BinaryResItem : public ResItem
{
public:
	BinaryResItem();
	virtual ~BinaryResItem();
};

MY_END_NAMESPACE

#endif