#include "MyProject.h"
#include "LevelResItem.h"
#include "LoadItem.h"
#include "RefCountResLoadResultNotify.h"
#include "ResEventDispatch.h"

LevelResItem::LevelResItem()
{
	
}
	
LevelResItem::~LevelResItem()
{
	
}

void LevelResItem::init(LoadItem* item)
{
	ResItem::init(item);
	this->mRefCountResLoadResultNotify->getLoadResEventDispatch()->dispatchEvent(this);
}

void LevelResItem::setLevelName(std::string lvlName)
{

}