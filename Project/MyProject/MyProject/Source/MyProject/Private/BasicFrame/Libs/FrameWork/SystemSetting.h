#pragma once

#include <string>
#include "GObject.h"

/**
 * @brief 系统设置
 */
class SystemSetting : public GObject
{
public:
    static std::string USERNAME;
	static std::string PASSWORD;

public:
	void init();
	void dispose();

	void setString(std::string key, std::string value);
	std::string getString(std::string key);
};