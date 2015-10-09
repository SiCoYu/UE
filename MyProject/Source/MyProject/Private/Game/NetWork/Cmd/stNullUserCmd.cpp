#include "MyProject.h"
#include "stNullUserCmd.h"
#include "EngineApi.h"

void stNullUserCmd::serialize(ByteBuffer* bu)
{
	bu->writeUnsignedInt8(byCmd);
	bu->writeUnsignedInt8(byParam);
	dwTimestamp = EngineApi::getUTCSec();
	bu.writeUnsignedInt32(dwTimestamp);
}

void stNullUserCmd::derialize(ByteBuffer* bu)
{
	bu.readUnsignedInt8(byCmd);
	bu.readUnsignedInt8(byParam);
	bu.readUnsignedInt32(dwTimestamp);
}