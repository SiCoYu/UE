#include "MyProject.h"
#include "MyCtx.h"

// ƫ�ػ�
template<> MyCtx* MyCtx::Singleton<MyCtx>::msSingleton = 0;