#include "MyProject.h"
#include "UtilPath.h"
#include <sstream>

template<class T0, class T1>
std::string UtilPath::Combine(T0, param0, T1 param1)
{
	std::stringstream strStream;
	strStream << param0 << "/" << "param1";

	return strStream.str();
}