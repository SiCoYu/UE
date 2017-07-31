#include "MyProject.h"
#include "ResLoadState.h"

ResLoadState::ResLoadState()
{
    this->mResLoadState = eNotLoad;
}

CVResLoadState ResLoadState::getResLoadState()
{
	return this->mResLoadState;
}
void ResLoadState::setResLoadState(CVResLoadState value)
{
	this->mResLoadState = value;
}

void ResLoadState::reset()
{
	this->mResLoadState = eNotLoad;
}

// 是否加载完成，可能成功可能失败
bool ResLoadState::hasLoaded()
{
    return this->mResLoadState == eFailed || this->mResLoadState == eLoaded;
}

bool ResLoadState::hasSuccessLoaded()
{
    return this->mResLoadState == eLoaded;
}

bool ResLoadState::hasFailed()
{
    return this->mResLoadState == eFailed;
}

// 没有加载或者正在加载中
bool ResLoadState::hasNotLoadOrLoading()
{
    return (this->mResLoadState == eLoading || this->mResLoadState == eNotLoad);
}

void ResLoadState::setSuccessLoaded()
{
	this->mResLoadState = eLoaded;
}

void ResLoadState::setFailed()
{
	this->mResLoadState = eFailed;
}

void ResLoadState::setLoading()
{
	this->mResLoadState = eLoading;
}

void ResLoadState::copyFrom(ResLoadState* rhv)
{
	this->mResLoadState = rhv->getResLoadState();
}