#ifndef __UIATTRSYSTEM_H
#define __UIATTRSYSTEM_H

#include <map>
#include "UIFormId.h"
#include <string>
#include "ResPathType.h"

class UIAttrItem;

class UIAttrSystem
{
public:
	std::map<UIFormId, UIAttrItem*> mId2AttrDic;

public:
	UIAttrSystem();
	void init();
	std::string getPath(UIFormId id);
	// 通过路径获取
	UIFormId GetFormIDByPath(std::string resPath, ResPathType pathType);
};

#endif				// __FORMATTRSYSTEM_H