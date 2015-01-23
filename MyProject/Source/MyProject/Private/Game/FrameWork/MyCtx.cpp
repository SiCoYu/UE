#include "MyProject.h"
#include "MyCtx.h"

// Æ«ÌØ»¯
template<> MyCtx* MyCtx::Singleton<MyCtx>::msSingleton = 0;