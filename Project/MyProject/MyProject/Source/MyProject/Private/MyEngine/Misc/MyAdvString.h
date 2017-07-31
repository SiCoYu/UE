#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

/**
 * @brief https://wiki.unrealengine.com/String_Manipulation_in_c%2B%2B_for_beginers
 */

class BadConversion : public std::runtime_error 
{
public:
	BadConversion(std::string const& s)
		: std::runtime_error(s)
	{
	
	}
};

inline std::string ToString(double x)
{
	std::ostringstream o;
	if (!(o << x))
		throw BadConversion("ToString(double)");

	return o.str();
}

inline std::string ToString(float x)
{
	std::ostringstream o;
	if (!(o << x))
		throw BadConversion("ToString(float)");

	return o.str();
}

inline std::string ToString(int x)
{
	std::ostringstream o;
	if (!(o << x))
		throw BadConversion("ToString(int)");

	return o.str();
}

inline std::string ToString(short x)
{
	std::ostringstream o;
	if (!(o << x))
		throw BadConversion("ToString(short)");

	return o.str();
}

inline std::string ToString(long x)
{
	std::ostringstream o;
	if (!(o << x))
		throw BadConversion("ToString(long)");

	return o.str();
}

inline std::string ToString(bool x)
{
	if (x)
	{
		return "true";
	}
	else
	{
		return "false";
	}
}

inline FString ToFString(std::string x)
{
	FString f(x.c_str());
	return f;
}

inline void PrintFStr(FString text)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, text);
}

inline void PrintFStrRed(FString text)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red, text);
}

inline void PrintFStrGreen(FString text)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text);
}

inline void PrintFStrBlue(FString text)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Blue, text);
}

inline void PrintStr(std::string text)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, ToFString(text));
}

inline void PrintStrRed(std::string text)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Red, ToFString(text));
}

inline void PrintStrGreen(std::string text)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, ToFString(text));
}

inline void PrintStrBlue(std::string text)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Blue, ToFString(text));
}