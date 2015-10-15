#include "MyProject.h"
#include "FrameTimerItem.h"

FrameTimerItem::FrameTimerItem()
{
	m_internal = 1;
	m_totalFrameCount = 1;
	m_curFrame = 0;
	m_curLeftFrame = 0;
	m_bInfineLoop = false;
	m_timerDisp = nullptr;
	m_disposed = false;
}

void FrameTimerItem::OnFrameTimer()
{
	if (m_disposed)
	{
		return;
	}

	++m_curFrame;
	++m_curLeftFrame;

	//if (m_preFrame == m_curFrame)
	//{
	//    Ctx.m_instance.m_logSys.log("aaaaaaaafadfsasdf");
	//}

	//m_curFrame = m_preFrame;

	if (m_bInfineLoop)
	{
		if (m_curLeftFrame == m_internal)
		{
			m_curLeftFrame = 0;

			if (m_timerDisp != null)
			{
				m_timerDisp(this);
			}
		}
	}
	else
	{
		if (m_curFrame == m_totalFrameCount)
		{
			m_disposed = true;
			if (m_timerDisp != null)
			{
				m_timerDisp(this);
			}
		}
		else
		{
			if (m_curLeftFrame == m_internal)
			{
				m_curLeftFrame = 0;
				if (m_timerDisp != null)
				{
					m_timerDisp(this);
				}
			}
		}
	}
}

void FrameTimerItem::reset()
{
	m_curFrame = 0;
	m_curLeftFrame = 0;
	m_disposed = false;
}

void FrameTimerItem::setClientDispose()
{

}

bool FrameTimerItem::getClientDispose()
{
	return false;
}