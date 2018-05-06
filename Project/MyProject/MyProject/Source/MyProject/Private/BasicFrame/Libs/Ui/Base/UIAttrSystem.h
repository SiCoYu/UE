#ifndef __UIATTRSYSTEM_H
#define __UIATTRSYSTEM_H

#include <map>
#include "UIFormId.h"
#include "FormType.h"
#include <string>
#include "ResPathType.h"

using namespace NSFormType;

class UIAttrItem;

class UIAttrSystem
{
public:
	std::map<UIFormId, UIAttrItem*> mId2AttrDic;

public:
	UIAttrSystem();
	void init();
	void dispose();

	std::string getPath(UIFormId id);
	// 通过路径获取
	UIFormId GetFormIDByPath(std::string resPath, ResPathType pathType);

protected:
	void addItem(UIFormId formId, std::string widgetPath, FormType formType, UMGOuterType outerType);
};

#endif				// __FORMATTRSYSTEM_H