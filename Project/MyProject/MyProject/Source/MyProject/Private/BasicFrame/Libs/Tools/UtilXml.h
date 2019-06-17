#ifndef __UtilXml_H
#define __UtilXml_H

#include "CString.h"
#include "UnrealString.h"	// FString
#include "NameTypes.h"		// FName
#include "Internationalization/Text.h"	// FText
#include "PlatformDefine.h"

class FXmlFile;
class FXmlNode;

MY_BEGIN_NAMESPACE(MyNS)

/**
 * @ref https://www.cnblogs.com/litmin/p/7447398.html
 * @ref https://blog.csdn.net/u014532636/article/details/72832520
 */
class UtilXml
{
	static bool loadXmlFromFile(FString& absolutePath, FXmlFile** xmlFile);
	static bool loadXmlFromStr(FString& absolutePath, FXmlFile** xmlFile);
	static FXmlNode* getRootNode(FXmlFile* xmlFile);
	static bool getNodeAttrStr(FXmlNode* xmlNode, FString inKey, FString& outValue);
};

MY_END_NAMESPACE

#endif