#include "MyProject.h"
#include "DataResItem.h"
#include "LoadItem.h"

void DataResItem::init(LoadItem* item)
{
	ResItem::init(item);
	m_refCountResLoadResultNotify->getLoadResEventDispatch()->dispatchEvent(this);
}