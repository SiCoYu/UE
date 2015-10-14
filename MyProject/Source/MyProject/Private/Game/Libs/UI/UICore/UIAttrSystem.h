#ifndef __UIATTRSYSTEM_H
#define __UIATTRSYSTEM_H

#include <map>
#include "UIFormID.h"

class UIAttrItem;

class UIAttrSystem
{
protected:
	std::map<UIFormID::UIFormID, UIAttrItem*> m_id2AttrDic;

public:
	UIAttrSystem();
};

#endif				// __FORMATTRSYSTEM_H