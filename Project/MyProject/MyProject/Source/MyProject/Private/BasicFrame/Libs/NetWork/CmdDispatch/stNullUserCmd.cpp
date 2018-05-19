#include "MyProject.h"
#include "stNullUserCmd.h"
#include "UtilEngineWrap.h"
#include "MByteBuffer.h"

void stNullUserCmd::serialize(MByteBuffer* bu)
{
	bu->writeUnsignedInt8(byCmd);
	bu->writeUnsignedInt8(byParam);
	dwTimestamp = UtilEngineWrap::getUTCSec();
	bu->writeUnsignedInt32(dwTimestamp);
}

void stNullUserCmd::derialize(MByteBuffer* bu)
{
	bu->readUnsignedInt8(byCmd);
	bu->readUnsignedInt8(byParam);
	bu->readUnsignedInt32(dwTimestamp);
}