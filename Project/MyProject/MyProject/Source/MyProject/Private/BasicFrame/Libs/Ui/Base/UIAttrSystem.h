#ifndef __UiAttrSystem_H
#define __UiAttrSystem_H

#include <map>
#include "UiFormId.h"
#include "FormType.h"
#include <string>
#include "ResPathType.h"

using namespace NSFormType;

class UiAttrItem;

class UiAttrSystem
{
public:
	std::map<UiFormId, UiAttrItem*> mId2AttrDic;

public:
	UiAttrSystem();
	void init();
	void dispose();

	std::string getPath(UiFormId id);
	// 通过路径获取
	UiFormId GetFormIDByPath(std::string resPath, ResPathType pathType);

protected:
	void addItem(UiFormId formId, std::string widgetPath, FormType formType, UMGOuterType outerType);
};

#endif				// __FORMATTRSYSTEM_H