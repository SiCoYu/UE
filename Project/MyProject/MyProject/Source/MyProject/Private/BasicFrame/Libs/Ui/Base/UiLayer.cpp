#include "MyProject.h"
#include "UiLayer.h"
#include "Form.h"
#include "MClassFactory.h"

MY_BEGIN_NAMESPACE(MyNS)

M_IMPLEMENT_AND_REGISTER_CLASS(UiLayer, GObject)

UiLayer::UiLayer(UiLayerId layerId)
{

}

void UiLayer::init()
{

}

void UiLayer::dispose()
{
	this->mWinDic.clear();
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
	UiFormId formId = form->getId();
	return this->mWinDic[formId] != nullptr;
}

void UiLayer::removeForm(UForm* form)
{
	UiFormId formId = form->getId();

	if (this->mWinDic[formId] != nullptr)
	{
		this->mWinDic.remove(formId);
	}
}

UiLayerId UiLayer::getLayerId()
{
	return this->mLayer;
}

void UiLayer::addForm(UForm* form)
{
	UiFormId formId = form->getId();

	this->mWinDic.add(formId, form);
}

void UiLayer::onStageReSize()
{
	Iterator itBegin, itEnd;

	itBegin = this->mWinDic.getData().begin();
	itEnd = this->mWinDic.getData().end();

	for (; itBegin != itEnd; ++itBegin)
	{
		//itBegin->second->onStageReSize();
	}
}

void UiLayer::closeAllForm()
{
	Iterator itBegin, itEnd;

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