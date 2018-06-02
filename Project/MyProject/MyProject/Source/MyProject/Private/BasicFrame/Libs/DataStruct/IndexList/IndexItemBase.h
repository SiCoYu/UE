#pragma once

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class IndexItemBase : public GObject
{
protected:
	int mIndex;   // 索引

public:
	IndexItemBase();
	
    void init();
    void dispose();

    int getIndex();
    void setIndex(int value);
    void resetIndex();
};

MY_END_NAMESPACE