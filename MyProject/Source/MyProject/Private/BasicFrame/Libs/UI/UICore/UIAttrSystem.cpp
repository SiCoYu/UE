#include "MyProject.h"
#include "UIAttrItem.h"
#include "UtilContainers.h"
#include "UIFormId.h"
#include "UIAttrSystem.h"

UIAttrSystem::UIAttrSystem()
{

}

void UIAttrSystem::init()
{
	this->addItem(
		NSFormId::eUITestUMG, 
		"WidgetBlueprint'/Game/MyAsset/Blueprints/Umg/UITestUMG/NewWidgetBlueprint.NewWidgetBlueprint_C'", 
		NSFormType::eUMG,
		NSFormType::ePlayerController);
}

void UIAttrSystem::dispose()
{

}

std::string UIAttrSystem::getPath(UIFormId id)
{
	if (UtilMap::ContainsKey(mId2AttrDic, id))
	{
		return mId2AttrDic[id]->mWidgetPath;
	}

	return "";
}

// 通过路径获取
UIFormId UIAttrSystem::GetFormIDByPath(std::string resPath, ResPathType pathType)
{
	for(auto keyValue : mId2AttrDic)
	{
		if (ePathComUI == pathType)
		{
			if (mId2AttrDic[keyValue.first]->mWidgetPath == resPath)
			{
				return keyValue.first;
			}
		}
		else if (ePathCodePath == pathType)
		{
			if (mId2AttrDic[keyValue.first]->mCodePath == resPath)
			{
				return keyValue.first;
			}
		}
	}

	return (UIFormId)0;       // 默认返回最大值
}

void UIAttrSystem::addItem(UIFormId formId, std::string widgetPath, FormType formType, UMGOuterType outerType)
{
	UIAttrItem* item = nullptr;

	item = new UIAttrItem();
	mId2AttrDic[formId] = item;
	item->mWidgetPath = widgetPath;
	item->mFormType = formType;
	item->mUMGOuterType = outerType;
}