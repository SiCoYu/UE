#include "MyProject.h"
#include "Config.h"
#include "UtilContainers.h"

std::string Config::StreamingAssets = "StreamingAssets/";
std::string Config::UIModelLayer = "UIModel";

Config::Config()
{
	mIp = "192.168.122.253";
	mPort = 10002;
	mZone = 30;

	mWebIP = "http://127.0.0.1/UnityServer/";
	mWebPort = 80;
	mNetLogPhp = "/netlog/NetLog.php";

	mResLoadType = eLoadDisc;
	mPathList[(int)ePathScene] = "Scenes/";
	mPathList[(int)ePathSceneXml] = "Scenes/Xml/";
	mPathList[(int)ePathModule] = "Module/";
	mPathList[(int)ePathComUI] = "UI/";
	mPathList[(int)ePathComUIScene] = "UIScene/";
	mPathList[(int)ePathBeingPath] = "Being/";
	mPathList[(int)ePathAIPath] = "AI/";
	mPathList[(int)ePathTablePath] = "Table/";
	mPathList[(int)ePathLangXml] = "Languages/";
	mPathList[(int)ePathXmlCfg] = "XmlConfig/";
	mPathList[(int)ePathModel] = "Model/";
	mPathList[(int)ePathMaterial] = "Model/Materials/";
	mPathList[(int)ePathBuildImage] = "Image/Build/";
	mPathList[(int)ePathCardImage] = "Image/Card/";
	mPathList[(int)ePathWord] = "Word/";
	mPathList[(int)ePathAudio] = "Sound/";
	mPathList[(int)ePathAtlas] = "Atlas/";
	mPathList[(int)ePathSpriteAni] = "Effect/SpriteEffect/";
	mPathList[(int)ePathSceneAnimatorController] = "Animation/Scene/";
	mPathList[(int)ePathLuaScript] = "LuaScript/";
	mPathList[(int)ePathSkillAction] = "SkillAction/";

	std::string value;
	value = std::string("prefab");
	UtilVector::Add(mPakExtNameList, value);
	value = std::string("png");
	UtilVector::Add(mPakExtNameList, value);
	value = std::string("shader");
	UtilVector::Add(mPakExtNameList, value);
	value = std::string("unity");
	UtilVector::Add(mPakExtNameList, value);
}

Config::~Config()
{

}

void Config::init()
{

}

void Config::dispose()
{

}