#include "MyProject.h"
#include "UiLayer.h"
#include "Form.h"

UiLayer::UiLayer(UiLayerId layerID)
{

}

std::map<UiFormId, UForm*>& UiLayer::getWinDic()
{
	return mWinDic;
}

FSlateRenderTransform& UiLayer::getLayerTrans()
{
	return *mLayerTrans;
}

void UiLayer::setLayerTrans(FSlateRenderTransform* rhv)
{
	mLayerTrans = rhv;
}

void UiLayer::setGoName(std::string& rhv)
{
	mGoName = rhv;
}

bool UiLayer::hasForm(UForm* form)
{
	return mWinDic[form->getId()] != nullptr;
}

void UiLayer::removeForm(UForm* form)
{
	if (mWinDic[form->getId()] != nullptr)
	{
		//mWinDic.erase(form->getId());
	}
}

UiLayerId UiLayer::getLayerID()
{
	return mLayer;
}

void UiLayer::addForm(UForm* form)
{
	mWinDic[form->getId()] = form;
}

void UiLayer::onStageReSize()
{
	std::map<UiFormId, UForm*>::iterator itBegin, itEnd;
	itBegin = mWinDic.begin();
	itEnd = mWinDic.end();
	for (; itBegin != itEnd; ++itBegin)
	{
		//itBegin->second->onStageReSize();
	}
}

void UiLayer::closeAllForm()
{
	std::map<UiFormId, UForm*>::iterator itBegin, itEnd;
	itBegin = mWinDic.begin();
	itEnd = mWinDic.end();
	for (; itBegin != itEnd; ++itBegin)
	{
		//itBegin->second->exit();
	}
}

void UiLayer::findLayerGOAndTrans()
{
	//mLayerTrans = Ctx.m_instance.m_layerMgr.m_path2Go[mGoName].transform;
}