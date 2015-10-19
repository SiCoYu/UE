#include "MyProject.h"
#include "PrefabResBase.h"
#include "ResItem.h"

UIAssetRes::UIAssetRes()
{

}

void UIAssetRes::initImpl(ResItem* res)
{
	m_go = res.getObject(res.getPrefabName()) as GameObject;
	base.initImpl(res);
}

GameObject UIAssetRes::InstantiateObject(std::string resName)
{
	m_retGO = null;

	if (null == m_go)
	{
		Ctx.m_instance.m_logSys.log("prefab 为 null");
	}
	else
	{
		m_retGO = GameObject.Instantiate(m_go) as GameObject;
		if (null == m_retGO)
		{
			Ctx.m_instance.m_logSys.log("不能实例化数据");
		}
	}
	return m_retGO;
}

GameObject UIAssetRes::getObject()
{
	return m_go;
}

void UIAssetRes::unload() override
{
	if (m_go != null)
	{
		//UtilApi.UnloadAsset(m_go);      // 强制卸载资源数据
		//UtilApi.DestroyImmediate(m_go, true);
		UtilApi.UnloadUnusedAssets();
		m_go = null;
	}
	m_retGO = null;
	base.unload();
}