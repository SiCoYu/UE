#include "MyProject.h"
#include "MPakFileStream.h"
#include "GenericPlatform/GenericPlatformFile.h"	// IPlatformFile
#include "HAL/PlatformFilemanager.h"		// FPlatformFileManager
#include "IPlatformFilePak.h"			// FPakPlatformFile \ FPakFile
#include "MPakFileSystem.h"
#include "MFileSystem.h"
#include "UtilEngineWrap.h"
#include "UtilFileIO.h"

MY_BEGIN_NAMESPACE(MyNS)

MPakFileStream::MPakFileStream()
{
	this->mMountState = MMountState::eNull;
	this->mMountPosType = MMountPosType::eEngine;
	this->mPakAssetClassObjectType = MPakAssetClassObjectType::eObject;
}

void MPakFileStream::init()
{
	this->_resolveInfo();
}

void MPakFileStream::dispose()
{

}

void MPakFileStream::setPakFilePath(FString& value)
{
	this->mPakFilePath = value;
}

void MPakFileStream::setMountPath(FString& value)
{
	this->mMountPoint = value;
}

FString MPakFileStream::_getSoftPathStr(FString& fileFullPathInPak)
{
	FString assetName;
	FString leftStr;
	FString rightStr;

	FString assetShortName = FPackageName::GetShortName(fileFullPathInPak);
	assetShortName.Split(TEXT("."), &leftStr, &rightStr);

	// 挂载到 Project ，目前挂载到工程师不能读取的
	if (MMountPosType::eProject == this->mMountPosType)
	{
		if (MPakAssetClassObjectType::eObject == this->mPakAssetClassObjectType)
		{
			if (this->mMountRelPath.Len() > 0)
			{
				assetName = MFileSystem::msProjectContentPathPrefix + this->mMountRelPath + TEXT("/") + leftStr + TEXT(".") + leftStr;
			}
			else
			{
				assetName = MFileSystem::msProjectContentPathPrefix + leftStr + TEXT(".") + leftStr;
			}
		}
		else if (MPakAssetClassObjectType::eClass == this->mPakAssetClassObjectType)
		{
			if (this->mMountRelPath.Len() > 0)
			{
				assetName = MFileSystem::msProjectContentPathPrefix + this->mMountRelPath + TEXT("/") + leftStr + TEXT(".") + leftStr + UtilEngineWrap::msClassObjectSuffix;
			}
			else
			{
				assetName = MFileSystem::msProjectContentPathPrefix + leftStr + TEXT(".") + leftStr + UtilEngineWrap::msClassObjectSuffix;
			}
		}
	}
	else	// 挂在到 Engine，目前挂载到引擎是可以读取的
	{
		if (MPakAssetClassObjectType::eObject == this->mPakAssetClassObjectType)
		{
			if (this->mMountRelPath.Len() > 0)
			{
				assetName = MFileSystem::msEngineContentPathPrefix + this->mMountRelPath + TEXT("/") + leftStr + TEXT(".") + leftStr + UtilEngineWrap::msClassObjectSuffix;
			}
			else
			{
				assetName = MFileSystem::msEngineContentPathPrefix + leftStr + TEXT(".") + leftStr + UtilEngineWrap::msClassObjectSuffix;
			}
		}
		else if (MPakAssetClassObjectType::eClass == this->mPakAssetClassObjectType)
		{
			if (this->mMountRelPath.Len() > 0)
			{
				assetName = MFileSystem::msEngineContentPathPrefix + this->mMountRelPath + TEXT("/") + leftStr + TEXT(".") + leftStr;
			}
			else
			{
				assetName = MFileSystem::msEngineContentPathPrefix + leftStr + TEXT(".") + leftStr;
			}
		}
	}

	return assetName;
}

void MPakFileStream::mount()
{
	if (GPakFileSystem->mountPakFileSystem(this->mPakFilePath, this->mMountPoint))
	{
		this->mMountState = MMountState::eSuccess;

		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		FPakFile pakFile(&PlatformFile, *this->mPakFilePath, false);

		pakFile.SetMountPoint(*this->mMountPoint);
		pakFile.FindFilesAtPath(this->mFileList, *pakFile.GetMountPoint(), true, false, true);
	}
	else
	{
		this->mMountState = MMountState::eFail;
	}
}

// mPakFilePath : G:/UE/Project/MyProject/MyProject/Content/MyStreamingAssets/MultiOne.pak
// mMountPoint : G:/File/opensource/UnrealEngine-4.0/UnrealEngine-git/Engine/Content/
// getAssetPathInPakByIndex： G:/File/opensource/UnrealEngine-4.0/UnrealEngine-git/Engine/Content/pak/MyAsset/
FString MPakFileStream::getAssetPathInPakByIndex(int index)
{
	FString ret;
	ret = this->mFileList[index];
	return ret;
}

FString MPakFileStream::getSoftPathStrByIndex(int index)
{
	FString ret;
	ret = this->_getSoftPathStr(this->mFileList[index]);
	return ret;
}

int MPakFileStream::getSoftPathCount()
{
	return this->mFileList.Num();
}

void MPakFileStream::setMountPosType(MMountPosType value)
{
	this->mMountPosType = value;
}

void MPakFileStream::_resolveInfo()
{
	if (UtilFileIO::isBluePrints(this->mPakFilePath))
	{
		this->mPakAssetClassObjectType = MPakAssetClassObjectType::eClass;
	}
	else
	{
		this->mPakAssetClassObjectType = MPakAssetClassObjectType::eObject;
	}

	this->mMountRelPath = UtilFileIO::convStreamingAssetsPathToMountPath(this->mPakFilePath);

	if (this->mMountRelPath.Len() > 0)
	{
		this->mMountPoint = UtilFileIO::EngineContentDir(false) + this->mMountRelPath;
	}
	else
	{
		this->mMountPoint = UtilFileIO::EngineContentDir(false);
	}
}

MY_END_NAMESPACE