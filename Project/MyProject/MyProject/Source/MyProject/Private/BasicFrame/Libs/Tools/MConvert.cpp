#include "MyProject.h"
#include "MConvert.h"
#include <sstream>	// stringstream

MY_BEGIN_NAMESPACE(MyNS)

std::string MConvert::convInt2Str(int value)
{
	std::string ret;
	stringstream stream;
	stream << value;
	ret = stream.str();   //此处也可以用 stream>>string_temp  
	return ret;
}

MY_END_NAMESPACE