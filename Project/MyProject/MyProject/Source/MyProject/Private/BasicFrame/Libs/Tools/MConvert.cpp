#include "MyProject.h"
#include "MConvert.h"
#include <sstream>	// stringstream

MY_BEGIN_NAMESPACE(MyNS)

std::string MConvert::convInt2Str(int value)
{
	std::string ret;
	stringstream stream;
	stream << value;
	ret = stream.str();   //�˴�Ҳ������ stream>>string_temp  
	return ret;
}

MY_END_NAMESPACE