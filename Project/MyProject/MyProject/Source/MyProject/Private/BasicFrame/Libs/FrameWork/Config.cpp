#include "MyProject.h"
#include "Config.h"

MY_BEGIN_NAMESPACE(MyNS)

std::string Config::StreamingAssets = "StreamingAssets/";
std::string Config::UIModelLayer = "UIModel";

Config::Config()
{
	this->mIp = "192.168.122.253";
	this->mPort = 10002;
	this->mZone = 30;

	this->mWebIP = "http://127.0.0.1/UnityServer/";
	this->mWebPort = 80;
	this->mNetLogPhp = "/netlog/NetLog.php";

	this->mResLoadType = eLoadDisc;
	this->mPathList[(int)ePathScene] = "Scenes/";
	this->mPathList[(int)ePathSceneXml] = "Scenes/Xml/";
	this->mPathList[(int)ePathModule] = "Module/";
	this->mPathList[(int)ePathComUI] = "UI/";
	this->mPathList[(int)ePathComUIScene] = "UIScene/";
	this->mPathList[(int)ePathBeingPath] = "Being/";
	this->mPathList[(int)ePathAIPath] = "AI/";
	this->mPathList[(int)ePathTablePath] = "Table/";
	this->mPathList[(int)ePathLangXml] = "Languages/";
	this->mPathList[(int)ePathXmlCfg] = "XmlConfig/";
	this->mPathList[(int)ePathModel] = "Model/";
	this->mPathList[(int)ePathMaterial] = "Model/Materials/";
	this->mPathList[(int)ePathBuildImage] = "Image/Build/";
	this->mPathList[(int)ePathCardImage] = "Image/Card/";
	this->mPathList[(int)ePathWord] = "Word/";
	this->mPathList[(int)ePathAudio] = "Sound/";
	this->mPathList[(int)ePathAtlas] = "Atlas/";
	this->mPathList[(int)ePathSpriteAni] = "Effect/SpriteEffect/";
	this->mPathList[(int)ePathSceneAnimatorController] = "Animation/Scene/";
	this->mPathList[(int)ePathLuaScript] = "LuaScript/";
	this->mPathList[(int)ePathSkillAction] = "SkillAction/";

	std::string value;
	value = std::string("prefab");
	this->mPakExtNameList.add(value);
	value = std::string("png");
	this->mPakExtNameList.add(value);
	value = std::string("shader");
	this->mPakExtNameList.add(value);
	value = std::string("unity");
	this->mPakExtNameList.add(value);
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

MY_END_NAMESPACE