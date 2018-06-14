#ifndef __LevelResItem_H
#define __LevelResItem_H

#include "ResItem.h"
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class LoadItem;

class LevelResItem : public ResItem
{
	M_DECLARE_CLASS(LevelResItem, ResItem)

protected:
    std::string mLocalPath;

public:
	LevelResItem();
	virtual ~LevelResItem();

	virtual void initWithLoad(LoadItem* item) override;
	void setLevelName(std::string lvlName);
};

MY_END_NAMESPACE

#endif