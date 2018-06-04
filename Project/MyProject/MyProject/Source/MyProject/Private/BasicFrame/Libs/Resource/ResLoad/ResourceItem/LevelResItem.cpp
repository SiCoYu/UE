#include "MyProject.h"
#include "LevelResItem.h"
#include "LoadItem.h"
#include "RefCountResLoadResultNotify.h"
#include "ResEventDispatch.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(LevelResItem, ResItem)

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

MY_END_NAMESPACE