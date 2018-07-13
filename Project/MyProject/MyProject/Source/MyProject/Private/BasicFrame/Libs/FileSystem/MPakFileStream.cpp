#include "MyProject.h"
#include "MPakFileStream.h"
#include "MPakFileSystem.h"

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
	assetName = TEXT("/Engine/") + leftStr + TEXT(".") + leftStr;

	return assetName;
}

bool MPakFileStream::_mountPakToFileSystem(FString& pakFileFullPath, FString& mountPoint)
{
	bool ret = false;

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	FPakPlatformFile* PakPlatformFile = new FPakPlatformFile();
	PakPlatformFile->Initialize(&PlatformFile, TEXT(""));
	FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile);

	if (PakPlatformFile->Mount(*pakFileFullPath, 0, *mountPoint))
	{
		ret = true;
	}

	return ret;
}

void MPakFileStream::mount()
{
	if (this->_mountPakToFileSystem(this->mPakFilePath, this->mMountPoint))
	{
		this->mMountState = MMountState::eSuccess;

		FPakFile pakFile(*this->mPakFilePath, false);
		pakFile.SetMountPoint(*this->mMountPoint);
		pakFile.FindFilesAtPath(this->mFileList, *pakFile.GetMountPoint(), true, false, true);
	}
	else
	{
		this->mMountState = MMountState::eFail;
	}
}

FString MPakFileStream::getSoftPathStrByIndex(int index)
{
	FString ret;
	ret = this->mFileList[index];
	return ret;
}

int MPakFileStream::getSoftPathCount()
{
	return this->mFileList.Num();
}

MY_END_NAMESPACE