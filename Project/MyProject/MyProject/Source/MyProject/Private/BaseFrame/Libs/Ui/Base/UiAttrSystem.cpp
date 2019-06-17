#include "MyProject.h"
#include "UiAttrSystem.h"
#include "UiAttrItem.h"
#include "UiFormId.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"
#include "MClassFactory.h"
#include "SafePointer.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(UiAttrSystem, GObject)

UiAttrSystem::UiAttrSystem()
{

}

void UiAttrSystem::init()
{
	this->addItem(
		UiFormId::eUiTestUMG,
		"WidgetBlueprint'/Game/MyAsset/Ui/UiTestUMG/UiTestUMG.UiTestUMG_C'", 
		FormType::eUMG,
		UMGOuterType::ePlayerController);
	this->addItem(
		UiFormId::eUiFunctionBar,
		"WidgetBlueprint'/Game/MyAsset/Ui/UiFunctionBar/UiFunctionBar.UiFunctionBar_C'",
		FormType::eUMG,
		UMGOuterType::ePlayerController);
}

void UiAttrSystem::dispose()
{
	Iterator curIte = this->mId2AttrDic.begin();
	Iterator endIte = this->mId2AttrDic.end();

	while (curIte != endIte)
	{
		MY_SAFE_DISPOSE(curIte->second);
		++curIte;
	}

	this->mId2AttrDic.clear();
}

std::string UiAttrSystem::getPath(UiFormId id)
{
	std::string ret = "";

	if (this->mId2AttrDic.containsKey(id))
	{
		ret = this->mId2AttrDic[id]->mWidgetPath;
	}

	return ret;
}

// 通过路径获取
UiFormId UiAttrSystem::GetFormIDByPath(std::string resPath, ResPathType pathType)
{
	UiFormId formId;

	for(auto keyValue : this->mId2AttrDic.getData())
	{
		formId = keyValue.first;

		if (ResPathType::ePathComUI == pathType)
		{
			if (this->mId2AttrDic[formId]->mWidgetPath == resPath)
			{
				return keyValue.first;
			}
		}
		else if (ResPathType::ePathCodePath == pathType)
		{
			if (this->mId2AttrDic[formId]->mCodePath == resPath)
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

MY_END_NAMESPACE