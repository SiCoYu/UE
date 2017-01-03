#pragma once

#include <string>

/**
* @brief œµÕ≥…Ë÷√
*/
class LuaSystem
{
public:
	static std::string USERNAME;
	static std::string PASSWORD;

public:
	void setString(std::string key, std::string value);
	std::string getString(std::string key);
};