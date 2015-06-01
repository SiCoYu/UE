#include "MyProject.h"
#include "UILayer.h"
#include "FormBase.h"

UILayer::UILayer(UILayerID layerID)
{

}

std::map<UIFormID, UFormBase*>& UILayer::getWinDic()
{
	return m_winDic;
}

FSlateRenderTransform& UILayer::getLayerTrans()
{
	return *m_layerTrans;
}

void UILayer::setLayerTrans(FSlateRenderTransform* rhv)
{
	m_layerTrans = rhv;
}

void UILayer::setGoName(std::string& rhv)
{
	m_goName = rhv;
}

bool UILayer::hasForm(UFormBase* form)
{
	return m_winDic[form->getFormId()] != nullptr;
}

void UILayer::removeForm(UFormBase* form)
{
	if (m_winDic[form->getFormId()] != nullptr)
	{
		m_winDic.erase(form->getFormId());
	}
}

UILayerID UILayer::getLayerID()
{
	return m_layer;
}

void UILayer::addForm(UFormBase* form)
{
	m_winDic[form->getFormId()] = form;
}

void UILayer::onStageReSize()
{
	std::map<UIFormID, UFormBase*>::iterator itBegin, itEnd;
	itBegin = m_winDic.begin();
	itEnd = m_winDic.end();
	for (; itBegin != itEnd; ++itBegin)
	{
		//itBegin->second->onStageReSize();
	}
}

void UILayer::closeAllForm()
{
	std::map<UIFormID, UFormBase*>::iterator itBegin, itEnd;
	itBegin = m_winDic.begin();
	itEnd = m_winDic.end();
	for (; itBegin != itEnd; ++itBegin)
	{
		//itBegin->second->exit();
	}
}

void UILayer::findLayerGOAndTrans()
{
	//m_layerTrans = Ctx.m_instance.m_layerMgr.m_path2Go[m_goName].transform;
}