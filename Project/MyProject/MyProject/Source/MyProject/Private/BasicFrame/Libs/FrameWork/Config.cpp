#include "MyProject.h"
#include "Config.h"

MY_BEGIN_NAMESPACE(MyNS)

std::string Config::StreamingAssets = "StreamingAssets/";
std::string Config::UiModelLayer = "UiModel";

Config::Config()
{
	this->mIp = "192.168.122.253";
	this->mPort = 10002;
	this->mZone = 30;

	this->mWebIP = "http://127.0.0.1/UnityServer/";
	this->mWebPort = 80;
	this->mNetLogPhp = "/netlog/NetLog.php";

	this->mResLoadType = ResLoadType::eLoadDisc;
	this->mPathList[(int)ResLoadType::ePathScene] = "Scenes/";
	this->mPathList[(int)ResLoadType::ePathSceneXml] = "Scenes/Xml/";
	this->mPathList[(int)ResPathType::ePathModule] = "Module/";
	this->mPathList[(int)ResPathType::ePathComUI] = "UI/";
	this->mPathList[(int)ResPathType::ePathComUIScene] = "UIScene/";
	this->mPathList[(int)ResPathType::ePathBeingPath] = "Being/";
	this->mPathList[(int)ResPathType::ePathAIPath] = "AI/";
	this->mPathList[(int)ResPathType::ePathTablePath] = "Table/";
	this->mPathList[(int)ResPathType::ePathLangXml] = "Languages/";
	this->mPathList[(int)ResPathType::ePathXmlCfg] = "XmlConfig/";
	this->mPathList[(int)ResPathType::ePathModel] = "Model/";
	this->mPathList[(int)ResPathType::ePathMaterial] = "Model/Materials/";
	this->mPathList[(int)ResPathType::ePathBuildImage] = "Image/Build/";
	this->mPathList[(int)ResPathType::ePathCardImage] = "Image/Card/";
	this->mPathList[(int)ResPathType::ePathWord] = "Word/";
	this->mPathList[(int)ResPathType::ePathAudio] = "Sound/";
	this->mPathList[(int)ResPathType::ePathAtlas] = "Atlas/";
	this->mPathList[(int)ResPathType::ePathSpriteAni] = "Effect/SpriteEffect/";
	this->mPathList[(int)ResPathType::ePathSceneAnimatorController] = "Animation/Scene/";
	this->mPathList[(int)ResPathType::ePathLuaScript] = "LuaScript/";
	this->mPathList[(int)ResPathType::ePathSkillAction] = "SkillAction/";

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