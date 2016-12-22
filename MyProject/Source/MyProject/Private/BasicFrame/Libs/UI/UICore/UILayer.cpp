#include "MyProject.h"
#include "UILayer.h"
#include "Form.h"

UILayer::UILayer(UILayerID layerID)
{

}

std::map<UIFormId, UForm*>& UILayer::getWinDic()
{
	return mWinDic;
}

FSlateRenderTransform& UILayer::getLayerTrans()
{
	return *mLayerTrans;
}

void UILayer::setLayerTrans(FSlateRenderTransform* rhv)
{
	mLayerTrans = rhv;
}

void UILayer::setGoName(std::string& rhv)
{
	mGoName = rhv;
}

bool UILayer::hasForm(UForm* form)
{
	return mWinDic[form->getId()] != nullptr;
}

void UILayer::removeForm(UForm* form)
{
	if (mWinDic[form->getId()] != nullptr)
	{
		//mWinDic.erase(form->getId());
	}
}

UILayerID UILayer::getLayerID()
{
	return mLayer;
}

void UILayer::addForm(UForm* form)
{
	mWinDic[form->getId()] = form;
}

void UILayer::onStageReSize()
{
	std::map<UIFormId, UForm*>::iterator itBegin, itEnd;
	itBegin = mWinDic.begin();
	itEnd = mWinDic.end();
	for (; itBegin != itEnd; ++itBegin)
	{
		//itBegin->second->onStageReSize();
	}
}

void UILayer::closeAllForm()
{
	std::map<UIFormId, UForm*>::iterator itBegin, itEnd;
	itBegin = mWinDic.begin();
	itEnd = mWinDic.end();
	for (; itBegin != itEnd; ++itBegin)
	{
		//itBegin->second->exit();
	}
}

void UILayer::findLayerGOAndTrans()
{
	//mLayerTrans = Ctx.m_instance.m_layerMgr.m_path2Go[mGoName].transform;
}