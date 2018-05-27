#include "MyProject.h"
#include "NullUserCmd.h"
#include "UtilEngineWrap.h"
#include "MByteBuffer.h"

void NullUserCmd::serialize(MByteBuffer* bu)
{
	bu->writeUnsignedInt8(byCmd);
	bu->writeUnsignedInt8(byParam);
	dwTimestamp = UtilEngineWrap::getUTCSec();
	bu->writeUnsignedInt32(dwTimestamp);
}

void NullUserCmd::derialize(MByteBuffer* bu)
{
	bu->readUnsignedInt8(byCmd);
	bu->readUnsignedInt8(byParam);
	bu->readUnsignedInt32(dwTimestamp);
}