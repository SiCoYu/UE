#include "MyProject.h"
#include "UiLayer.h"
#include "Form.h"

MY_BEGIN_NAMESPACE(MyNS)

UiLayer::UiLayer(UiLayerId layerId)
{

}

MDictionary<UiFormId, UForm*>& UiLayer::getWinDic()
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
		this->mWinDic.remove(form->getId());
	}
}

UiLayerId UiLayer::getLayerId()
{
	return this->mLayer;
}

void UiLayer::addForm(UForm* form)
{
	this->mWinDic.add(form->getId(), form);
}

void UiLayer::onStageReSize()
{
	typename MDictionary<UiFormId, UForm*>::Iterator itBegin, itEnd;
	itBegin = this->mWinDic.getData().begin();
	itEnd = this->mWinDic.getData().end();

	for (; itBegin != itEnd; ++itBegin)
	{
		//itBegin->second->onStageReSize();
	}
}

void UiLayer::closeAllForm()
{
	typename MDictionary<UiFormId, UForm*>::Iterator itBegin, itEnd;
	itBegin = this->mWinDic.getData().begin();
	itEnd = this->mWinDic.getData().end();

	for (; itBegin != itEnd; ++itBegin)
	{
		//itBegin->second->exit();
	}
}

void UiLayer::findLayerGOAndTrans()
{
	//mLayerTrans = Ctx.m_instance.m_layerMgr.m_path2Go[mActorName].transform;
}

MY_END_NAMESPACE