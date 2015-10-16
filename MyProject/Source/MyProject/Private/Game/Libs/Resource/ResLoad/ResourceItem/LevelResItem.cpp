#include "MyProject.h"
#include "LevelResItem.h"
#include "LoadItem.h"

void LevelResItem::init(LoadItem* item)
{
	ResItem::init(item);
	m_refCountResLoadResultNotify->getLoadResEventDispatch()->dispatchEvent(this);
}

void LevelResItem::setLevelName(std::string lvlName)
{

}