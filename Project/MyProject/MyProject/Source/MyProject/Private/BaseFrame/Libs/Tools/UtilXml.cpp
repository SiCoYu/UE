#include "MyProject.h"
#include "UtilXml.h"
#include "UtilFileIO.h"
#include "XmlParser.h"

MY_BEGIN_NAMESPACE(MyNS)

bool UtilXml::loadXmlFromFile(FString& absolutePath, FXmlFile** xmlFile)
{
	bool ret = false;
	if (UtilFileIO::ExistFile(absolutePath))
	{
		ret = true;
		*xmlFile = new FXmlFile(absolutePath);
	}
	return ret;
}

bool UtilXml::loadXmlFromStr(FString& inStrContent, FXmlFile** xmlFile)
{
	bool ret = false;
	*xmlFile = new FXmlFile(inStrContent, EConstructMethod::ConstructFromBuffer);
	ret = (*xmlFile != nullptr);
	return ret;
}

FXmlNode* UtilXml::getRootNode(FXmlFile* xmlFile)
{
	return xmlFile->GetRootNode();
}

bool UtilXml::getNodeAttrStr(FXmlNode* xmlNode, FString inKey, FString& outValue)
{
	outValue = xmlNode->GetContent();
	return true;
}

MY_END_NAMESPACE