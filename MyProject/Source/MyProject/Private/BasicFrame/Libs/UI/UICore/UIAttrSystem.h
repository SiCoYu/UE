#ifndef __UIATTRSYSTEM_H
#define __UIATTRSYSTEM_H

#include <map>
#include "UIFormID.h"
#include <string>
#include "ResPathType.h"

class UIAttrItem;

class UIAttrSystem
{
public:
	std::map<UIFormID, UIAttrItem*> m_id2AttrDic;

public:
	UIAttrSystem();
	std::string getPath(UIFormID id);
	// 通过路径获取
	UIFormID GetFormIDByPath(std::string resPath, ResPathType pathType);
};

#endif				// __FORMATTRSYSTEM_H