#include "MyProject.h"
#include "MCondition.h"
#include "MMutex.h"
#include "MEvent.h"
#include "MLock.h"

MCondition::MCondition(std::string name)
{
    m_pMMutex = new MMutex();
    m_pMEvent = new MEvent();
    m_canEnterWait = true;      // 允许进入等待状态
}

MCondition::~MCondition()
{
	delete m_pMMutex;
	delete m_pMEvent;
}

bool MCondition::getCanEnterWait()
{
    return m_canEnterWait;
}

void MCondition::wait()
{
	m_pMMutex->Lock();
    if (m_canEnterWait)
    {
		m_pMMutex->Unlock();   // 这个地方需要释放锁，否则 notifyAll 进不来
        m_pMEvent->Wait();
        m_pMEvent->Reset();      // 重置信号
    }
    else
    {
        m_canEnterWait = true;
		m_pMMutex->Unlock();
    }
}

void MCondition::notifyAll()
{
	MLock mlock(m_pMMutex);

    if (m_canEnterWait) // 如果 m_canEnterWait == false，必然不能进入等待
    {
        m_canEnterWait = false;
        m_pMEvent->Set();        // 唤醒线程
    }
}