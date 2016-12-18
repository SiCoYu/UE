#include "MyProject.h"
#include "ResLoadState.h"

ResLoadState::ResLoadState()
{
    mResLoadState = eNotLoad;
}

CVResLoadState ResLoadState::getResLoadState()
{
	return mResLoadState;
}
void ResLoadState::setResLoadState(CVResLoadState value)
{
	mResLoadState = value;
}

void ResLoadState::reset()
{
    mResLoadState = eNotLoad;
}

// 是否加载完成，可能成功可能失败
bool ResLoadState::hasLoaded()
{
    return mResLoadState == eFailed || mResLoadState == eLoaded;
}

bool ResLoadState::hasSuccessLoaded()
{
    return mResLoadState == eLoaded;
}

bool ResLoadState::hasFailed()
{
    return mResLoadState == eFailed;
}

// 没有加载或者正在加载中
bool ResLoadState::hasNotLoadOrLoading()
{
    return (mResLoadState == eLoading || mResLoadState == eNotLoad);
}

void ResLoadState::setSuccessLoaded()
{
    mResLoadState = eLoaded;
}

void ResLoadState::setFailed()
{
    mResLoadState = eFailed;
}

void ResLoadState::setLoading()
{
    mResLoadState = eLoading;
}

void ResLoadState::copyFrom(ResLoadState* rhv)
{
    mResLoadState = rhv->getResLoadState();
}