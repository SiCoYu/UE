#include "MyProject.h"
#include "UtilConvert.h"
#include <sstream>	// stringstream
#include <string>     // std::string, std::stoi

MY_BEGIN_NAMESPACE(MyNS)

std::string UtilConvert::mConvRetStr = "";

std::string& UtilConvert::convInt2Str(int value)
{
	UtilConvert::mConvRetStr = "";

	std::stringstream stream;
	stream << value;
	UtilConvert::mConvRetStr = stream.str();   //此处也可以用 stream>>string_temp  

	return UtilConvert::mConvRetStr;
}

int UtilConvert::convStr2Int(std::string value)
{
	int ret = 0;
	std::stoi(value, nullptr, 10);
	return ret;
}

std::string& UtilConvert::convFloat2Str(float value)
{
	UtilConvert::mConvRetStr = "";

	std::stringstream stream;
	stream << value;
	UtilConvert::mConvRetStr = stream.str();   //此处也可以用 stream>>string_temp  

	return UtilConvert::mConvRetStr;
}

std::string& UtilConvert::convBool2Str(bool value)
{
	UtilConvert::mConvRetStr = "";

	std::stringstream stream;
	stream << value;
	UtilConvert::mConvRetStr = stream.str();   //此处也可以用 stream>>string_temp  

	return UtilConvert::mConvRetStr;
}

MY_END_NAMESPACE