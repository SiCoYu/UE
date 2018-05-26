#ifndef __LogSys_H
#define __LogSys_H

#include "UnrealString.h"		// FString
#include <string>
#include "GObject.h"

class LogSys : public GObject
{
public:
	LogSys();
	~LogSys();

public:
	void init();
	void dispose();

	//void log(FString message);
	void log(std::string message);
	void error(std::string message);
};

#endif