#include "MyProject.h"
#include "SystemFrameData.h"

void SystemFrameData::nextFrame(float delta)
{
	++m_totalFrameCount;
	++m_curFrameCount;
	m_curTime += delta;

	if (m_curTime > 1.0f)
	{
		m_fps = (int)(m_curFrameCount / m_curTime);
		m_curFrameCount = 0;
		m_curTime = 0;

		//Ctx.m_instance.m_logSys.log(string.Format("当前帧率 {0}", m_fps));
	}
}