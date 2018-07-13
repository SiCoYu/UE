#pragma once

#include "Containers/Array.h"			// TArray
#include "Containers/UnrealString.h"	// FString
#include "GObject.h"
#include "MMountState.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MPakFileStream : public GObject
{
protected:
	FString mPakFilePath;
	FString mMountPoint;
	MMountState mMountState;
	TArray<FString> mFileList;

public:
	MPakFileStream();

	void init();
	void dispose();

	void setPakFilePath(FString& value);
	void setMountPath(FString& value);
	void mount();

protected:
	FString _getSoftPathStr(FString& fileFullPathInPak);
	bool _mountPakToFileSystem(FString& pakFileFullPath, FString& mountPoint);
};

MY_END_NAMESPACE