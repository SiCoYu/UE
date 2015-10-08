#ifndef __stNullUserCmd_H
#define __stNullUserCmd_H

#include "MyProject.h"		// int8

class ByteBuffer;

/**
 * @brief 
 */
enum class EnstNullUserCmd
{
	TIME_USERCMD = 2,
	DATA_USERCMD = 3,
	PROPERTY_USERCMD = 4,
	CHAT_USERCMD = 14,
	SELECT_USERCMD = 24,
	LOGON_USERCMD = 104,
	HERO_CARD_USERCMD = 162,
};

class stNullUserCmd
{
public:
    int8 byCmd;
    int8 byParam;
    uint32 dwTimestamp;

public:
	virtual void serialize(ByteBuffer* bu);
	virtual void derialize(ByteBuffer* bu);
};


#endif