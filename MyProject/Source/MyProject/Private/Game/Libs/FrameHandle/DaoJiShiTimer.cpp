#include "MyProject.h"
#include "DaoJiShiTimer.h"

void DaoJiShiTimer::OnTimer(float delta)
{
	if (m_disposed)
	{
		return;
	}

	m_curTime -= delta;
	m_curLeftTimer += delta;

	if (m_bInfineLoop)
	{
		checkAndDisp();
	}
	else
	{
		if (m_curTime <= 0)
		{
			disposeAndDisp();
		}
		else
		{
			checkAndDisp();
		}
	}
}

void DaoJiShiTimer::reset()
{
	m_curTime = m_totalTime;
	m_curLeftTimer = 0;
	m_disposed = false;
}