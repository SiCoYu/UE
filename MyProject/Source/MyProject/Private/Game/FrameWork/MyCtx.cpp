#include "MyProject.h"
#include "MyCtx.h"

// ƫ�ػ�
template<> MyCtx* MyCtx::Singleton<MyCtx>::msSingleton = 0;

void MyCtx::initUIMgr(IUIManager* uiMgr)
{
	m_uiMgr = uiMgr;
}
