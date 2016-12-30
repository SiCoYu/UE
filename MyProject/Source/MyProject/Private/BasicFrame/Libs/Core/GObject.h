#pragma once

#include<string>

class GObject
{
protected:
	std::string mTypeId;     // 名字

public:
	GObject();

public:
	std::string getTypeId();
};