#ifndef __LevelResItem_H
#define __LevelResItem_H

#include "ResItem.h"

class LoadItem;

class LevelResItem : public ResItem
{
protected:
    std::string m_localPath;

public:
	virtual void init(LoadItem* item) override;
	void setLevelName(std::string lvlName);
};

#endif