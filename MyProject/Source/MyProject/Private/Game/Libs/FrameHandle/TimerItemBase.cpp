#include "MyProject.h"
#include "TimerItemBase.h"

TimerItemBase::TimerItemBase()
{
	m_internal = 1;
	m_totalTime = 1;
	m_curTime = 0;
	m_bInfineLoop = false;
	m_curLeftTimer = 0;
	m_timerDisp = nullptr;
	m_disposed = false;
}

void TimerItemBase::OnTimer(float delta)
{
	if (m_disposed)
	{
		return;
	}

	m_curTime += delta;
	m_curLeftTimer += delta;

	if (m_bInfineLoop)
	{
		checkAndDisp();
	}
	else
	{
		if (m_curTime >= m_totalTime)
		{
			disposeAndDisp();
		}
		else
		{
			checkAndDisp();
		}
	}
}

void TimerItemBase::disposeAndDisp()
{
	m_disposed = true;
	if (!m_timerDisp.empty())
	{
		m_timerDisp(this);
	}
}

void TimerItemBase::checkAndDisp()
{
	if (m_curLeftTimer >= m_internal)
	{
		m_curLeftTimer = m_curLeftTimer - m_internal;

		if (!m_timerDisp.empty())
		{
			m_timerDisp(this);
		}
	}
}

void TimerItemBase::reset()
{
	m_curTime = 0;
	m_curLeftTimer = 0;
	m_disposed = false;
}

void TimerItemBase::setClientDispose()
{

}

bool TimerItemBase::getClientDispose()
{
	return false;
}