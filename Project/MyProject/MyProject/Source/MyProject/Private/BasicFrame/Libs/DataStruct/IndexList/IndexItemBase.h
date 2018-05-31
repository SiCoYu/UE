#pragma once

#include "GObject.h"

class IndexItemBase : public GObject
{
protected:
	int mIndex;   // 索引

public:
	IndexItemBase()
    {
        this.mIndex = -1;
    }

    void init()
    {

    }

    void dispose()
    {

    }

    int getIndex()
    {
        return this.mIndex;
    }

    void setIndex(int value)
    {
        this.mIndex = value;
    }

    void resetIndex()
    {
        this.mIndex = -1;
    }
};