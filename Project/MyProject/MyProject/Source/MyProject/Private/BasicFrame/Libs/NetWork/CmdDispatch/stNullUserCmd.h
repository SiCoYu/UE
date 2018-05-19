#ifndef __stNullUserCmd_H
#define __stNullUserCmd_H

#include "Platform.h"		// int8

class MByteBuffer;

/**
 * @brief 
 */
enum class NullUserCmdCV
{
	TIME_USERCMD = 2,
	DATA_USERCMD = 3,
};

class stNullUserCmd
{
public:
    uint8 byCmd;
    uint8 byParam;
    uint32 dwTimestamp;

public:
	virtual void serialize(MByteBuffer* bu);
	virtual void derialize(MByteBuffer* bu);
};


#endif