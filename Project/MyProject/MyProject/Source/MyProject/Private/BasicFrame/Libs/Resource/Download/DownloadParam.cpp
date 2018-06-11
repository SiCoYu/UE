#include "MyProject.h"
#include "DownloadParam.h"

MY_BEGIN_NAMESPACE(MyNS)

DownloadParam::DownloadParam()
{
    this->reset();
}

void DownloadParam::init()
{

}

void DownloadParam::dispose()
{

}

void DownloadParam::reset()
{
	this->mResLoadType = ResLoadType::eLoadWeb;
	this->mDownloadType = DownloadType::eHttpWeb;
	this->mIsWriteFile = true;
	this->mFileLen = 0;
	this->mVersion = "";
}

void DownloadParam::setPath(std::string origPath)
{
	this->mOrigPath = origPath;
	this->mLoadPath = mOrigPath;
	this->mLogicPath = mOrigPath;
	this->mResUniqueId = mOrigPath;
	this->mVersion = "4";

    //mExtName = UtilPath.getFileExt(mOrigPath);

    //if(mExtName == UtilSysLibWrap.UNITY3D)
    //{
    //    mResPackType = eBundleType;
    //}
    //else
    //{
    //    mResPackType = eDataType;
    //}
}

MY_END_NAMESPACE