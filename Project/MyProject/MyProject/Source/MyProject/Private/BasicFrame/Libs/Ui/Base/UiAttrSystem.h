#ifndef __UiAttrSystem_H
#define __UiAttrSystem_H

#include <map>
#include "UiFormId.h"
#include "FormType.h"
#include <string>
#include "ResPathType.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

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
	// ͨ��·����ȡ
	UiFormId GetFormIDByPath(std::string resPath, ResPathType pathType);

protected:
	void addItem(
		UiFormId formId, 
		std::string widgetPath, 
		FormType formType, 
		UMGOuterType outerType
	);
};

MY_END_NAMESPACE

#endif				// __UiAttrSystem_H