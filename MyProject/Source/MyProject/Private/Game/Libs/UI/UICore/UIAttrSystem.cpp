#include "MyProject.h"
#include "UIAttrSystem.h"
#include "UIAttrItem.h"
#include "UtilContainers.h"

UIAttrSystem::UIAttrSystem()
{

}

std::string UIAttrSystem::getPath(UIFormID id)
{
	if (UtilMap::ContainsKey(m_id2AttrDic, id))
	{
		return m_id2AttrDic[id]->m_widgetPath;
	}

	return "";
}

// ͨ��·����ȡ
UIFormID UIAttrSystem::GetFormIDByPath(std::string resPath, ResPathType pathType)
{
	for(auto keyValue : m_id2AttrDic)
	{
		if (ePathComUI == pathType)
		{
			if (m_id2AttrDic[keyValue.first]->m_widgetPath == resPath)
			{
				return keyValue.first;
			}
		}
		else if (ePathCodePath == pathType)
		{
			if (m_id2AttrDic[keyValue.first]->m_codePath == resPath)
			{
				return keyValue.first;
			}
		}
	}

	return (UIFormID)0;       // Ĭ�Ϸ������ֵ
}