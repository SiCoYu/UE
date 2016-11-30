#include "MyProject.h"
#include "Config.h"
#include "UtilContainers.h"

std::string Config::StreamingAssets = "StreamingAssets/";
std::string Config::UIModelLayer = "UIModel";

Config::Config()
{
	m_ip = "192.168.122.253";
	m_port = 10002;
	m_zone = 30;

	m_webIP = "http://127.0.0.1/UnityServer/";
	m_webPort = 80;
	m_netLogPhp = "/netlog/NetLog.php";

	m_resLoadType = eLoadDisc;
	m_pathLst[(int)ePathScene] = "Scenes/";
	m_pathLst[(int)ePathSceneXml] = "Scenes/Xml/";
	m_pathLst[(int)ePathModule] = "Module/";
	m_pathLst[(int)ePathComUI] = "UI/";
	m_pathLst[(int)ePathComUIScene] = "UIScene/";
	m_pathLst[(int)ePathBeingPath] = "Being/";
	m_pathLst[(int)ePathAIPath] = "AI/";
	m_pathLst[(int)ePathTablePath] = "Table/";
	m_pathLst[(int)ePathLangXml] = "Languages/";
	m_pathLst[(int)ePathXmlCfg] = "XmlConfig/";
	m_pathLst[(int)ePathModel] = "Model/";
	m_pathLst[(int)ePathMaterial] = "Model/Materials/";
	m_pathLst[(int)ePathBuildImage] = "Image/Build/";
	m_pathLst[(int)ePathCardImage] = "Image/Card/";
	m_pathLst[(int)ePathWord] = "Word/";
	m_pathLst[(int)ePathAudio] = "Sound/";
	m_pathLst[(int)ePathAtlas] = "Atlas/";
	m_pathLst[(int)ePathSpriteAni] = "Effect/SpriteEffect/";
	m_pathLst[(int)ePathSceneAnimatorController] = "Animation/Scene/";
	m_pathLst[(int)ePathLuaScript] = "LuaScript/";
	m_pathLst[(int)ePathSkillAction] = "SkillAction/";

	std::string value;
	value = std::string("prefab");
	UtilVector::Add(m_pakExtNameList, value);
	value = std::string("png");
	UtilVector::Add(m_pakExtNameList, value);
	value = std::string("shader");
	UtilVector::Add(m_pakExtNameList, value);
	value = std::string("unity");
	UtilVector::Add(m_pakExtNameList, value);
}