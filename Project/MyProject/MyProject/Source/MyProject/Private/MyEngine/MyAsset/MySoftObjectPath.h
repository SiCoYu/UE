#pragma once

#include <string>

#include "UObject/SoftObjectPath.h"	// FStringAssetReference\FSoftObjectPath
// UE$ 4.22 warning C4996: 'UObjectHeaderDeprecatedWarning': Including UObject.h has been deprecated. Please include Object.h instead. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
//#include "UObject/UObject.h"		// UObject
#include "UObject/Object.h"		// UObject

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

	FSoftObjectPath& getNativeSoftObjectPath();
};

MY_END_NAMESPACE