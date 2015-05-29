#include "MyProject.h"
#include "UILayer.h"

UILayer::UILayer()
{

}

std::map<UIFormID, UFormBase*>& UILayer::getWinDic()
{
	return m_winDic;
}

USceneComponent& UILayer::getLayerTrans()
{
	return *m_layerTrans;
}

USceneComponent& UILayer::setLayerTrans(USceneComponent* rhv)
{
	m_layerTrans = rhv
}

void UILayer::setGoName(std::string& rhv)
{
	m_goName = rhv;
}

bool hasForm(Form form)
{
	return m_winDic.ContainsKey(form.id);
}

void removeForm(Form form)
{
	if (m_winDic.ContainsKey(form.id))
	{
		m_winDic.Remove(form.id);
	}
}

UILayerID layerID
{
get
{
	return m_layer;
}
}

void addForm(Form form)
{
	m_winDic[form.id] = form;
}

void onStageReSize()
{
	foreach(Form form in m_winDic.Values)
	{
		form.onStageReSize();
	}
}

void closeAllForm()
{
	foreach(Form form in m_winDic.Values)
	{
		form.exit();
	}
}

void findLayerGOAndTrans()
{
	m_layerTrans = Ctx.m_instance.m_layerMgr.m_path2Go[m_goName].transform;
}