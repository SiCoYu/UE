#include "stNullUserCmd.h"

void stNullUserCmd::serialize(ByteBuffer* bu)
{
	bu->writeUnsignedInt8(byCmd);
	bu->writeUnsignedInt8(byParam);
	dwTimestamp = UtilApi.getUTCSec();
	bu.writeUnsignedInt32(dwTimestamp);
}

void stNullUserCmd::derialize(ByteBuffer* bu)
{
	bu.readUnsignedInt8(byCmd);
	bu.readUnsignedInt8(byParam);
	bu.readUnsignedInt32(dwTimestamp);
}