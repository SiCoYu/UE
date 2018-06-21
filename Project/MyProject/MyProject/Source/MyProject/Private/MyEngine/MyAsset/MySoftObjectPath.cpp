#include "MyProject.h"
#include "MySoftObjectPath.h"
#include "UtilStr.h"

MySoftObjectPath::MySoftObjectPath()
{

}

MySoftObjectPath::~MySoftObjectPath()
{

}

void setPath(FString Path)
{
	this->mNativeSoftObjectPath.SetPath(Path);
}

void setPath(std::string Path)
{
	this->mNativeSoftObjectPath.SetPath(UtilStr::ConvStdStr2FString(path));
}

UObject* MySoftObjectPath::tryLoad() const
{
	return this->mNativeSoftObjectPath.TryLoad();
}

UObject* MySoftObjectPath::resolveObject() const
{
	return this->mNativeSoftObjectPath.ResolveObject();
}