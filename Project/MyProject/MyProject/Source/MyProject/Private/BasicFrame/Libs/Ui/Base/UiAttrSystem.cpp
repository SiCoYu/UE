#include "MyProject.h"
#include "UiAttrItem.h"
#include "UtilContainers.h"
#include "UiFormId.h"
#include "UiAttrSystem.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"

UiAttrSystem::UiAttrSystem()
{

}

void UiAttrSystem::init()
{
	this->addItem(
		NSFormId::eUiTestUMG, 
		"WidgetBlueprint'/Game/MyAsset/Ui/UiTestUMG/UiTestUMG.UiTestUMG_C'", 
		NSFormType::eUMG,
		NSFormType::ePlayerController);
	this->addItem(
		NSFormId::eUiFunctionBar,
		"WidgetBlueprint'/Game/MyAsset/Ui/UiFunctionBar/UiFunctionBar.UiFunctionBar_C'",
		NSFormType::eUMG,
		NSFormType::ePlayerController);
}

void UiAttrSystem::dispose()
{

}

std::string UiAttrSystem::getPath(UiFormId id)
{
	if (UtilMap::ContainsKey(this->mId2AttrDic, id))
	{
		return mId2AttrDic[id]->mWidgetPath;
	}

	return "";
}

// 通过路径获取
UiFormId UiAttrSystem::GetFormIDByPath(std::string resPath, ResPathType pathType)
{
	for(auto keyValue : this->mId2AttrDic)
	{
		if (ePathComUI == pathType)
		{
			if (this->mId2AttrDic[keyValue.first]->mWidgetPath == resPath)
			{
				return keyValue.first;
			}
		}
		else if (ePathCodePath == pathType)
		{
			if (this->mId2AttrDic[keyValue.first]->mCodePath == resPath)
			{
				return keyValue.first;
			}
		}
	}

	return (UiFormId)0;       // 默认返回最大值
}

void UiAttrSystem::addItem(
	UiFormId formId, 
	std::string widgetPath, 
	FormType formType, 
	UMGOuterType outerType
)
{
	UiAttrItem* item = nullptr;

	item = MY_NEW UiAttrItem();
	this->mId2AttrDic[formId] = item;
	item->mWidgetPath = widgetPath;
	item->mFormType = formType;
	item->mUMGOuterType = outerType;
}