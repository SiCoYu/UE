#ifndef __LevelResItem_H
#define __LevelResItem_H

#include "ResItem.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class LoadItem;

class LevelResItem : public ResItem
{
protected:
    std::string mLocalPath;

public:
	LevelResItem();
	virtual ~LevelResItem();

	virtual void init(LoadItem* item) override;
	void setLevelName(std::string lvlName);
};

MY_END_NAMESPACE

#endif