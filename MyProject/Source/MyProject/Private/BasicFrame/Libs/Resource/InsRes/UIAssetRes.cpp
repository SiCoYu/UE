#include "MyProject.h"
#include "UIAssetRes.h"
#include "ResItem.h"
#include "EngineApi.h"
#include "Common.h"

UIAssetRes::UIAssetRes()
{

}

void UIAssetRes::initImpl(ResItem* res)
{
	//m_go = res.getObject(res.getPrefabName()) as GameObject;
	//base.initImpl(res);
}

UObject* UIAssetRes::InstantiateObject(std::string resName)
{
	m_retGO = nullptr;

	if (nullptr == m_go)
	{
		g_pLogSys->log("prefab 为 null");
	}
	else
	{
		// m_retGO = GameObject.Instantiate(m_go) as GameObject;
		if (nullptr == m_retGO)
		{
			g_pLogSys->log("不能实例化数据");
		}
	}
	return m_retGO;
}

UObject* UIAssetRes::getObject()
{
	return m_go;
}

void UIAssetRes::unload()
{
	if (m_go != nullptr)
	{
		//UtilApi.UnloadAsset(m_go);      // 强制卸载资源数据
		//UtilApi.DestroyImmediate(m_go, true);
		EngineApi::UnloadUnusedAssets();
		m_go = nullptr;
	}
	m_retGO = nullptr;
	InsResBase::unload();
}