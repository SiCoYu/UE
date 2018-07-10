#include "MyProject.h"
#include "ResRedirectItem.h"

MY_BEGIN_NAMESPACE(MyNS)

ResRedirectItem::ResRedirectItem(std::string origPath = "", int redirect = (int)ResLoadType.eLoadResource)
{
	this->mOrigPath = origPath;
	this->mResLoadType = (ResLoadType)redirect;
}

bool ResRedirectItem::isRedirectR()
{
	return this->mResLoadType == ResLoadType.eLoadResource;
}

bool ResRedirectItem::isRedirectS()
{
	return this->mResLoadType == ResLoadType.eLoadStreamingAssets;
}

bool ResRedirectItem::isRedirectP()
{
	return this->mResLoadType == ResLoadType.eLoadLocalPersistentData;
}

bool ResRedirectItem::isRedirectW()
{
	return this->mResLoadType == ResLoadType.eLoadWeb;
}

MY_END_NAMESPACE