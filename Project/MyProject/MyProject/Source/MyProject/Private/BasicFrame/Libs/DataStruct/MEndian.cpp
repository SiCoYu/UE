#include "MyProject.h"
#include "MEndian.h"

MEndian SystemEndian::msEndian = (ENDIANNESS == 'l' ? MEndian::eBIG_ENDIAN : MEndian::eLITTLE_ENDIAN);	// 决定系统大小端