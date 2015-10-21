#include "MyProject.h"
#include "SystemTimeData.h"
#include "EngineApi.h"

SystemTimeData::SystemTimeData()
{
	m_preTime = 0;
	m_curTime = 0;
	m_deltaSec = 0.0f;
}

float SystemTimeData::getDeltaSec()
{
	return m_deltaSec;
}

void SystemTimeData::setDeltaSec(float value)
{
	m_deltaSec = value;
}

long SystemTimeData::getCurTime()
{
	return m_curTime;
}
void SystemTimeData::setCurTime(long value)
{
	m_curTime = value;
}

void SystemTimeData::nextFrame()
{
	m_curTime = EngineApi::getUTCSec();
	if (m_preTime != 0.0f)     // 第一帧跳过，因为这一帧不好计算间隔
	{
		m_deltaSec = m_curTime - m_preTime;
	}
	else
	{
		m_deltaSec = 1 / 24;        // 每秒 24 帧
	}
	m_preTime = m_curTime;
}