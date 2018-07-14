#pragma once

#include "Containers/Array.h"			// TArray
#include "Containers/UnrealString.h"	// FString
#include "GObject.h"
#include "MMountState.h"
#include "MMountPosType.h"
#include "MPakAssetClassObjectType.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MPakFileStream : public GObject
{
protected:
	// 一定是相对目录，绝对目录是加载不了资源的
	FString mPakFilePath;
	FString mMountPoint;
	MMountState mMountState;
	MMountPosType mMountPosType;
	MPakAssetClassObjectType mPakAssetClassObjectType;
	TArray<FString> mFileList;

public:
	MPakFileStream();

	void init();
	void dispose();

	void setPakFilePath(FString& value);
	void setMountPath(FString& value);
	void mount();
	FString getSoftPathStrByIndex(int index);
	int getSoftPathCount();
	FString getAssetPathInPakByIndex(int index);

	void setMountPosType(MMountPosType value);

protected:
	FString _getSoftPathStr(FString& fileFullPathInPak);
};

MY_END_NAMESPACE