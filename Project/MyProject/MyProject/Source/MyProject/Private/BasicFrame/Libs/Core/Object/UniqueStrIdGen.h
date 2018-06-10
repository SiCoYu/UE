#pragma once

#include <string>
#include "MClassInfo.h"
#include "MClassMacros.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class UniqueStrIdGen : public UniqueNumIdGen
{
	M_DECLARE_CLASS(UniqueStrIdGen, UniqueNumIdGen)

public:
	std::string PlayerPrefix = "PL";
	std::string PlayerChildPrefix = "PC";
	std::string AbandonPlanePrefix = "AP";
	std::string BoomPlanePrefix = "BP";
	std::string RobotPrefix = "RT";
	std::string SnowBlockPrefix = "SM";
	std::string PlayerTargetPrefix = "PT";
	std::string ScoreEffectPrefix = "SE";
	std::string MeteStonePrefix = "MS";
	std::string GroundEntityPrefix = "GE";

protected:
	std::string mPrefix;
	std::string mRetId;

public:
	UniqueStrIdGen(string prefix, uint baseUniqueId);
	
	std::string genNewStrId();
	std::string getCurStrId();
	std::string genStrIdById(uint id);
};

MY_END_NAMESPACE