#include "MyProject.h"
#include "LocalFileSys.h"

LocalFileSys::LocalFileSys()
{
	
}

// 获取本地可以读取的目录，但是不能写
std::string LocalFileSys::getLocalReadDir()
{
	return "";
}

// 获取本地可以写的目录
std::string LocalFileSys::getLocalWriteDir()
{
	return m_persistentDataPath;
}

void LocalFileSys::modifyLoadParam(std::string resPath, LoadParam* param)
{
//#if PKG_RES_LOAD
//	param.m_origPath = resPath;             // 记录原始的资源名字
//
//	string retPath = resPath;
//
//	if ("Module/AutoUpdate.prefab" == resPath)       // 自动更新模块更新还没有实现
//	{
//		param.m_resLoadType = ResLoadType.eStreamingAssets;
//	}
//	else
//	{
//		// 获取包的名字
//		if (Ctx.m_instance.m_pPakSys.path2PakDic.ContainsKey(resPath))
//		{
//			retPath = Ctx.m_instance.m_pPakSys.path2PakDic[resPath].m_pakName;
//		}
//
//		if (param != null)
//		{
//			Ctx.m_instance.m_localFileSys.getAbsPathByRelPath(ref retPath, ref param.m_resLoadType);
//		}
//		else
//		{
//			ResLoadType tmp = ResLoadType.eStreamingAssets;
//			Ctx.m_instance.m_localFileSys.getAbsPathByRelPath(ref retPath, ref tmp);
//		}
//	}
//	param.m_path = retPath;
//	param.m_pakPath = param.m_path;
//#elif UnPKG_RES_LOAD
//	if (param != null)
//	{
//		param.m_resLoadType = ResLoadType.eStreamingAssets;
//	}
//	param.m_path = resPath;
//#else
//	param.m_path = resPath;
//#endif
}