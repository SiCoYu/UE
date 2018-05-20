#include "MyProject.h"
#include "ResLoadState.h"

ResLoadState::ResLoadState()
{
    this->mResLoadState = ResLoadStateCV::eNotLoad;
}

ResLoadStateCV ResLoadState::getResLoadState()
{
	return this->mResLoadState;
}
void ResLoadState::setResLoadState(ResLoadStateCV value)
{
	this->mResLoadState = value;
}

void ResLoadState::reset()
{
	this->mResLoadState = ResLoadStateCV::eNotLoad;
}

// 是否加载完成，可能成功可能失败
bool ResLoadState::hasLoaded()
{
    return this->mResLoadState == ResLoadStateCV::eFailed || 
		   this->mResLoadState == ResLoadStateCV::eLoaded;
}

bool ResLoadState::hasSuccessLoaded()
{
    return this->mResLoadState == ResLoadStateCV::eLoaded;
}

bool ResLoadState::hasFailed()
{
    return this->mResLoadState == ResLoadStateCV::eFailed;
}

// 没有加载或者正在加载中
bool ResLoadState::hasNotLoadOrLoading()
{
    return (this->mResLoadState == ResLoadStateCV::eLoading || 
		    this->mResLoadState == ResLoadStateCV::eNotLoad);
}

void ResLoadState::setSuccessLoaded()
{
	this->mResLoadState = ResLoadStateCV::eLoaded;
}

void ResLoadState::setFailed()
{
	this->mResLoadState = ResLoadStateCV::eFailed;
}

void ResLoadState::setLoading()
{
	this->mResLoadState = ResLoadStateCV::eLoading;
}

// 成功实例化
void ResLoadState::setSuccessIns()
{
	this->mResLoadState = ResLoadStateCV::eInsSuccess;
}

// 实例化失败
void ResLoadState::setInsFailed()
{
	this->mResLoadState = ResLoadStateCV::eInsFailed;
}

// 正在实例化
void ResLoadState::setInsing()
{
	this->mResLoadState = ResLoadStateCV::eInsing;
}

// 是否成功实例化
bool ResLoadState::hasSuccessIns()
{
	return (this->mResLoadState == ResLoadStateCV::eInsSuccess);
}

// 是否实例化失败
bool ResLoadState::hasInsFailed()
{
	return (this->mResLoadState == ResLoadStateCV::eInsFailed);
}

// 是否正在实例化
bool ResLoadState::hasInsing()
{
	return (this->mResLoadState == ResLoadStateCV::eInsing);
}

void ResLoadState::copyFrom(ResLoadState* rhv)
{
	this->mResLoadState = rhv->getResLoadState();
}