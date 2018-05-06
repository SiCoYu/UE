#include "MyProject.h"
#include "UiLayer.h"
#include "Form.h"

UiLayer::UiLayer(UiLayerId layerID)
{

}

std::map<UiFormId, UForm*>& UiLayer::getWinDic()
{
	return this->mWinDic;
}

FSlateRenderTransform& UiLayer::getLayerTrans()
{
	return *this->mLayerTrans;
}

void UiLayer::setLayerTrans(FSlateRenderTransform* rhv)
{
	this->mLayerTrans = rhv;
}

void UiLayer::setActorName(std::string& rhv)
{
	this->mActorName = rhv;
}

bool UiLayer::hasForm(UForm* form)
{
	return this->mWinDic[form->getId()] != nullptr;
}

void UiLayer::removeForm(UForm* form)
{
	if (this->mWinDic[form->getId()] != nullptr)
	{
		//mWinDic.erase(form->getId());
	}
}

UiLayerId UiLayer::getLayerID()
{
	return this->mLayer;
}

void UiLayer::addForm(UForm* form)
{
	this->mWinDic[form->getId()] = form;
}

void UiLayer::onStageReSize()
{
	std::map<UiFormId, UForm*>::iterator itBegin, itEnd;
	itBegin = this->mWinDic.begin();
	itEnd = this->mWinDic.end();
	for (; itBegin != itEnd; ++itBegin)
	{
		//itBegin->second->onStageReSize();
	}
}

void UiLayer::closeAllForm()
{
	std::map<UiFormId, UForm*>::iterator itBegin, itEnd;
	itBegin = this->mWinDic.begin();
	itEnd = this->mWinDic.end();
	for (; itBegin != itEnd; ++itBegin)
	{
		//itBegin->second->exit();
	}
}

void UiLayer::findLayerGOAndTrans()
{
	//mLayerTrans = Ctx.m_instance.m_layerMgr.m_path2Go[mActorName].transform;
}