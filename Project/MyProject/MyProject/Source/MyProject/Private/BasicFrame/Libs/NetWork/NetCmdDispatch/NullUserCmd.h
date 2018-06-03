#ifndef __NullUserCmd_H
#define __NullUserCmd_H

#include "Platform.h"		// int8
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

class MByteBuffer;

/**
 * @brief 
 */
enum class NullUserCmdCV
{
	TIME_USERCMD = 2,
	DATA_USERCMD = 3,
};

class NullUserCmd
{
public:
    uint8 byCmd;
    uint8 byParam;
    uint32 dwTimestamp;

public:
	virtual void serialize(MByteBuffer* bu);
	virtual void derialize(MByteBuffer* bu);
};

MY_END_NAMESPACE

#endif