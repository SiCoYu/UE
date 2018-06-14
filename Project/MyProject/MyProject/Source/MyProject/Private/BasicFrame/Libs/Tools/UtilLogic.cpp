#include "MyProject.h"
#include "UtilLogic.h"
#include "UtilStr.h"

MY_BEGIN_NAMESPACE(MyNS)

FVector UtilLogic::FAKE_POS = new FVector(-1000, 0, -1000);  // Ĭ�����ص����λ��

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

bool UtilLogic::isInFakePos(FVector pos)
{
	return UtilMath::isEqualVec3(pos, UtilLogic::FAKE_POS);
}

MY_END_NAMESPACE