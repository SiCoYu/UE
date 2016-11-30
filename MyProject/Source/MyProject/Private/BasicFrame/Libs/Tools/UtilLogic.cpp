#include "MyProject.h"
#include "UtilLogic.h"
#include "UtilStr.h"

std::string UtilLogic::convScenePath2LevelName(std::string& path)
{
	int slashIdx = UtilStr::LastIndexOf(path, "/");
	int dotIdx = UtilStr::IndexOf(path, ".");
	std::string retLevelName = "";
	if (slashIdx != -1)
	{
		if (dotIdx != -1)
		{
			retLevelName = UtilStr::Substring(path, slashIdx + 1, dotIdx - slashIdx - 1);
		}
		else
		{
			retLevelName = UtilStr::Substring(path, slashIdx + 1);
		}
	}
	else
	{
		retLevelName = path;
	}

	return retLevelName;
}