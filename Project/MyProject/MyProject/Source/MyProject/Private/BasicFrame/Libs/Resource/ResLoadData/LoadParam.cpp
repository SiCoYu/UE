#include "MyProject.h"
#include "LoadParam.h"
#include "UtilStr.h"
#include "UtilLogic.h"

MY_BEGIN_NAMESPACE(MyNS)

LoadParam::LoadParam()
{
	this->init();
}

LoadParam::~LoadParam()
{

}

void LoadParam::init()
{
	this->mPath = "";
	this->mOrigPath = "";
	this->mResUniqueId = "";
	this->mPathNoExt = "";

	this->mExtName = "prefab";
	this->mPrefabName = "";
	this->mLvlName = "";
	this->mSubPath = "";

	this->mVersion = "";
	this->mPakPath = "";
	this->mLoadRes = nullptr;
	this->mLoadInsRes = nullptr;

	this->mIsResNeedCoroutine = false;
	this->mIsLoadNeedCoroutine = false;
	this->mLoadEventHandle = EventDispatchDelegate();
	this->mResPackType = ResPackType::eNoneType;

	this->mResLoadType = ResLoadType::eLoadNum;
}

void LoadParam::setPath(std::string path)
{
	this->mPath = path;
	this->mLvlName = path;
}

std::string LoadParam::getPath()
{
	return this->mPath;
}

void LoadParam::setResUniqueId(std::string value)
{
	this->mResUniqueId = value;
}

std::string LoadParam::getResUniqueId()
{
	return this->mResUniqueId;
}

void LoadParam::setOrigPath(std::string value)
{
	this->mOrigPath = value;
}

std::string LoadParam::getOrigPath()
{
	return this->mOrigPath;
}

void LoadParam::setPathNoExt(std::string value)
{
	this->mPathNoExt = value;
}

std::string LoadParam::getPathNoExt()
{
	return this->mPathNoExt;
}

void LoadParam::setResPackType(ResPackType value)
{
	this->mResPackType = value;
}

ResPackType LoadParam::getResPackType()
{
	return this->mResPackType;
}

void LoadParam::setResLoadType(ResLoadType value)
{
	this->mResLoadType = value;
}

ResLoadType LoadParam::getResLoadType()
{
	return this->mResLoadType;
}

void LoadParam::setIsResNeedCoroutine(bool value)
{
	this->mIsResNeedCoroutine = value;
}

bool LoadParam::getIsResNeedCoroutine()
{
	return this->mIsResNeedCoroutine;
}

void LoadParam::setIsLoadNeedCoroutine(bool value)
{
	this->mIsLoadNeedCoroutine = value;
}

bool LoadParam::getIsLoadNeedCoroutine()
{
	return this->mIsLoadNeedCoroutine;
}

void LoadParam::setLoadEventHandle(EventDispatchDelegate value)
{
	this->mLoadEventHandle = value;
}

EventDispatchDelegate LoadParam::getLoadEventHandle()
{
	return this->mLoadEventHandle;
}

void LoadParam::setPrefabName(std::string value)
{
	this->mPrefabName = value;
}

std::string LoadParam::getPrefabName()
{
	return this->mPrefabName;
}

void LoadParam::setExtName(std::string value)
{
	this->mExtName = value;
}

std::string LoadParam::getExtName()
{
	return this->mExtName;
}

void LoadParam::setLvlName(std::string value)
{
	this->mLvlName = value;
}

std::string LoadParam::getLvlName()
{
	return this->mLvlName;
}

void LoadParam::setLoadRes(ResItem* value)
{
	this->mLoadRes = value;
}

ResItem* LoadParam::getLoadRes()
{
	return this->mLoadRes;
}

void LoadParam::setLoadInsRes(ResInsBase* value)
{
	this->mLoadInsRes = value;
}

ResInsBase* LoadParam::getLoadInsRes()
{
	return this->mLoadInsRes;
}

void LoadParam::resetDefault()          // 将数据清空，有时候上一次调用的时候的参数 m_loaded 还在，结果被认为是这一次的回调了
{
	//this->mLoadEventHandle = nullptr;
	//this->mVersion = "";
	//this->mExtName = "prefab";
	//this->mOrigPath = "";

	//this->mLoadRes = nullptr;
	//this->mLoadInsRes = nullptr;

	this->init();
}

// 解析目录
void LoadParam::resolvePath()
{
	int dotIdx = UtilStr::IndexOf(this->mPath, ".");
	int slashIdx = UtilStr::LastIndexOf(this->mPath, "/");

	if (-1 == dotIdx)       // 材质是没有扩展名字的
	{
		this->mExtName = "";
		this->mPathNoExt = mPath;

		if (-1 == slashIdx)  // 没有路径，只有一个文件名字
		{
			this->mPrefabName = mPath;
		}
		else
		{
			this->mPrefabName = UtilStr::Substring(mPath, slashIdx + 1);
		}
	}
	else
	{
		this->mExtName = UtilStr::Substring(this->mPath, dotIdx + 1);
		this->mPathNoExt = UtilStr::Substring(this->mPath, 0, dotIdx);

		if (-1 == slashIdx)  // 没有路径，只有一个文件名字
		{
			this->mPrefabName = UtilStr::Substring(this->mPath, 0, dotIdx);
		}
		else
		{
			this->mPrefabName = UtilStr::Substring(this->mPath, slashIdx + 1, dotIdx - slashIdx - 1);
		}
	}
}

void LoadParam::resolveLevel()
{
	this->resolvePath();

	int slashIdx = 0;
	if (UtilStr::IsNullOrEmpty(this->mOrigPath))
	{
		slashIdx = UtilStr::LastIndexOf(this->mPathNoExt, "/");
		if (slashIdx != -1)
		{
			this->mLvlName = UtilStr::Substring(this->mPathNoExt, slashIdx + 1);
		}
		else
		{
			this->mLvlName = this->mPathNoExt;
		}
	}
	else        // 如果是打包，需要从原始加载目录获取关卡名字
	{
		this->mLvlName = UtilLogic::convScenePath2LevelName(this->mOrigPath);
	}
}

MY_END_NAMESPACE