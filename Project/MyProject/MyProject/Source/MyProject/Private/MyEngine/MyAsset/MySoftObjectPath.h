#pragma once

#include <string>

#include "UObject/SoftObjectPath.h"	// FStringAssetReference\FSoftObjectPath
#include "UObject/UObject.h"		// UObject

#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MySoftObjectPath : public GObject
{
protected:
	FSoftObjectPath mNativeSoftObjectPath;

public:
	MySoftObjectPath();
	~MySoftObjectPath();

	void setPath(FString Path);
	void setPath(std::string Path);
	UObject* tryLoad() const;
	UObject* resolveObject() const;
};

MY_END_NAMESPACE