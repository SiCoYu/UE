#pragma once

#include <string>

/**
 * @brief 系统设置
 */
class SystemSetting
{
public:
    static std::string USERNAME;
	static std::string PASSWORD;

public:
	void setString(std::string key, std::string value);
	std::string getString(std::string key);
};