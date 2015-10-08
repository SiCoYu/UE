#ifndef __LogSys_H
#define __LogSys_H

#include "MyProject.h"		// FString

class LogSys
{
public:
	LogSys();
	~LogSys();

	void log(FString message);
};

#endif