#include "MyProject.h"
#include "DownloadParam.h"

public DownloadParam::DownloadParam()
{
    reset();
}

void DownloadParam::reset()
{
    mResLoadType = eLoadWeb;
    mDownloadType = eHttpWeb;
    mIsWriteFile = true;
    mFileLen = 0;
	mVersion = "";
}

void DownloadParam::setPath(std::string origPath)
{
    mOrigPath = origPath;
    mLoadPath = mOrigPath;
    mLogicPath = mOrigPath;
    mResUniqueId = mOrigPath;
    mVersion = "4";

    //mExtName = UtilPath.getFileExt(mOrigPath);

    if(mExtName == UtilApi.UNITY3D)
    {
        mResPackType = eBundleType;
    }
    else
    {
        mResPackType = eDataType;
    }
}