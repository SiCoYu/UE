//#ifndef __UtilPath_H_
//#define __UtilPath_H_
//
//#include <string>
//#include <sstream>

template<class T0, class T1>
static std::string UtilPath::Combine(T0 param0, T1 param1)
{
	std::stringstream strStream;
	strStream << param0 << "/" << "param1";

	return strStream.str();
}

//#endif