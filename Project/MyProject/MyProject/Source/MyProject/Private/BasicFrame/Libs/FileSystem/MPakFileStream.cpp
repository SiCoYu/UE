#include "MyProject.h"
#include "MPakFileStream.h"
#include "GenericPlatform/GenericPlatformFile.h"	// IPlatformFile
#include "HAL/PlatformFilemanager.h"		// FPlatformFileManager
#include "IPlatformFilePak.h"			// FPakPlatformFile \ FPakFile
#include "MPakFileSystem.h"
#include "MFileSystem.h"
#include "UtilEngineWrap.h"

MY_BEGIN_NAMESPACE(MyNS)

MPakFileStream::MPakFileStream()
{
	this->mMountState = MMountState::eNull;
}

void MPakFileStream::init()
{

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
	//assetName = MFileSystem::msEngineContentPathPrefix + leftStr + TEXT(".") + leftStr + UtilEngineWrap::msClassObjectSuffix;
	assetName = MFileSystem::msEngineContentPathPrefix + leftStr + TEXT(".") + leftStr;

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

MY_END_NAMESPACE