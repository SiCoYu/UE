#include "MyProject.h"
#include "UtilConvert.h"
#include <sstream>	// stringstream
#include <string>     // std::string, std::stoi

MY_BEGIN_NAMESPACE(MyNS)

std::string UtilConvert::convInt2Str(int value)
{
	std::string ret;
	stringstream stream;
	stream << value;
	ret = stream.str();   //此处也可以用 stream>>string_temp  
	return ret;
}

int UtilConvert::convStr2Int(std::string value)
{
	int ret = 0;
	std::stoi(value, nullptr, 10);
	return ret;
}

MY_END_NAMESPACE