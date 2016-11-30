#include "MyProject.h"
#include "LoadParam.h"
#include "UtilStr.h"
#include "UtilLogic.h"

std::string LoadParam::getPrefabName()
{
	return m_prefabName;
}

std::string LoadParam::getExtName()
{
	return m_extName;
}

std::string LoadParam::getLvlName()
{
	return m_lvlName;
}

void LoadParam::resetDefault()          // 将数据清空，有时候上一次调用的时候的参数 m_loaded 还在，结果被认为是这一次的回调了
{
	m_loadEventHandle = nullptr;
	m_version = "";
	m_extName = "prefab";
	m_origPath = "";

	m_loadRes = nullptr;
	m_loadInsRes = nullptr;
}

// 解析目录
void LoadParam::resolvePath()
{
	int dotIdx = UtilStr::IndexOf(m_path, ".");
	int slashIdx = UtilStr::LastIndexOf(m_path, "/");

	if (-1 == dotIdx)       // 材质是没有扩展名字的
	{
		m_extName = "";
		m_pathNoExt = m_path;

		if (-1 == slashIdx)  // 没有路径，只有一个文件名字
		{
			m_prefabName = m_path;
		}
		else
		{
			m_prefabName = UtilStr::Substring(m_path, slashIdx + 1);
		}
	}
	else
	{
		m_extName = UtilStr::Substring(m_path, dotIdx + 1);
		m_pathNoExt = UtilStr::Substring(m_path, 0, dotIdx);

		if (-1 == slashIdx)  // 没有路径，只有一个文件名字
		{
			m_prefabName = UtilStr::Substring(m_path, 0, dotIdx);
		}
		else
		{
			m_prefabName = UtilStr::Substring(m_path, slashIdx + 1, dotIdx - slashIdx - 1);
		}
	}
}

void LoadParam::resolveLevel()
{
	resolvePath();

	int slashIdx = 0;
	if (UtilStr::IsNullOrEmpty(m_origPath))
	{
		slashIdx = UtilStr::LastIndexOf(m_pathNoExt, "/");
		if (slashIdx != -1)
		{
			m_lvlName = UtilStr::Substring(m_pathNoExt, slashIdx + 1);
		}
		else
		{
			m_lvlName = m_pathNoExt;
		}
	}
	else        // 如果是打包，需要从原始加载目录获取关卡名字
	{
		m_lvlName = UtilLogic::convScenePath2LevelName(m_origPath);
	}
}