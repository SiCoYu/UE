#include "ResLoadState.h"

ResLoadState::ResLoadState()
{
    m_resLoadState = eNotLoad;
}

CVResLoadState ResLoadState::getResLoadState()
{
	return m_resLoadState;
}
void ResLoadState::setResLoadState(CVResLoadState value)
{
	m_resLoadState = value;
}

void ResLoadState::reset()
{
    m_resLoadState = eNotLoad;
}

// 是否加载完成，可能成功可能失败
bool ResLoadState::hasLoaded()
{
    return m_resLoadState == eFailed || m_resLoadState == eLoaded;
}

bool ResLoadState::hasSuccessLoaded()
{
    return m_resLoadState == eLoaded;
}

bool ResLoadState::hasFailed()
{
    return m_resLoadState == eFailed;
}

// 没有加载或者正在加载中
bool ResLoadState::hasNotLoadOrLoading()
{
    return (m_resLoadState == eLoading || m_resLoadState == eNotLoad);
}

void ResLoadState::setSuccessLoaded()
{
    m_resLoadState = eLoaded;
}

void ResLoadState::setFailed()
{
    m_resLoadState = eFailed;
}

void ResLoadState::setLoading()
{
    m_resLoadState = eLoading;
}

void ResLoadState::copyFrom(ResLoadState& rhv)
{
    m_resLoadState = rhv.getResLoadState();
}