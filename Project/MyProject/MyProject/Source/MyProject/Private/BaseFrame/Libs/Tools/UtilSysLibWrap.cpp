#include "MyProject.h"
#include "UtilSysLibWrap.h"
#include <ctime>

MY_BEGIN_NAMESPACE(MyNS)

FVector UtilSysLibWrap::FAKE_POS = FVector(-1000, 0, -1000);

std::string UtilSysLibWrap::getRandomVersion()
{
	std::string ret = "";

	time_t curTime = time(NULL);
	ret = ctime(&curTime);

	return ret;
}

MY_END_NAMESPACE