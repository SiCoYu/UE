#include "MyProject.h"
#include "DownloadItem.h"
#include "ResLoadState.h"
#include "MyMemoryConstructorFlag.h"
#include "MyMemoryAllocatorConfig.h"
#include "MyMemoryDefaultAlloc.h"

DownloadItem::DownloadItem()
{
	this->mResLoadType = eLoadWeb;
	this->mRefCountResLoadResultNotify = MY_NEW RefCountResLoadResultNotify();
	this->mAllLoadResEventDispatch = MY_NEW ResEventDispatch();
}

DownloadItem::~DownloadItem()
{
	
}

RefCountResLoadResultNotify* DownloadItem::getRefCountResLoadResultNotify()
{
	return this->mRefCountResLoadResultNotify;
}

void DownloadItem::setRefCountResLoadResultNotify(RefCountResLoadResultNotify* value)
{
	this->mRefCountResLoadResultNotify = value;
}

ResEventDispatch* DownloadItem::getAllLoadResEventDispatch()
{
	return this->mAllLoadResEventDispatch;
}

void DownloadItem::setAllLoadResEventDispatch(ResEventDispatch* value)
{
	this->mAllLoadResEventDispatch = value;
}

void DownloadItem::reset()
{
	this->mLoadPath = "";
	this->mDownloadType = eHttpWeb;

	this->mBytes = nullptr;
}

std::string DownloadItem::getLoadPath()
{
	return this->mLoadPath;
}

void DownloadItem::setLoadPath(std::string value)
{
	this->mLoadPath = value;
}

std::string DownloadItem::getOrigPath()
{
	return this->mOrigPath;
}

void DownloadItem::setOrigPath(std::string value)
{
	this->mOrigPath = value;
}

DownloadType DownloadItem::getDownloadType()
{
	return this->mDownloadType;
}

void DownloadItem::setDownloadType(DownloadType value)
{
	this->mDownloadType = value;
}

bool DownloadItem::hasSuccessLoaded()
{
    return this->mRefCountResLoadResultNotify->getResLoadState()->hasSuccessLoaded();
}

bool DownloadItem::hasFailed()
{
    return this->mRefCountResLoadResultNotify->getResLoadState()->hasFailed();
}

void DownloadItem::setResUniqueId(std::string value)
{
	this->mResUniqueId = value;
}

std::string DownloadItem::getResUniqueId()
{
    return this->mResUniqueId;
}

char* DownloadItem::getBytes()
{
    return this->mBytes;
}

std::string DownloadItem::getText()
{
    return this->mText;
}

void DownloadItem::init()
{

}

void DownloadItem::failed()
{

}

// 这个是卸载，因为有时候资源加载进来可能已经不用了，需要直接卸载掉
void DownloadItem::unload()
{

}

void DownloadItem::setLoadParam(DownloadParam* param)
{
    this->setLoadPath(param->mLoadPath);
    this->setOrigPath(param->mOrigPath);
    this->setDownloadType(param->mDownloadType);
    this->mResLoadType = param->mResLoadType;
    this->mResPackType = param->mResPackType;
    this->mVersion = param->mVersion;
    this->mIsWriteFile = param->mIsWriteFile;
    this->mFileLen = param->mFileLen;
    this->setResUniqueId(param->mResUniqueId);
}

void DownloadItem::load()
{
	this->mRefCountResLoadResultNotify->getResLoadState()->setLoading();
}

void DownloadItem::runTask()
{

}

void DownloadItem::handleResult()
{

}

// 加载完成写入本地文件系统
void DownloadItem::writeFile()
{
    
}