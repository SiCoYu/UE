#ifndef __DataResItem_H
#define __DataResItem_H

#include "ResItem.h"

class LoadItem;

class DataResItem : public ResItem
{
protected:
    std::string m_localPath;

public:
	virtual void init(LoadItem* item) override;
};

#endif