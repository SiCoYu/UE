#include "MyProject.h"
#include "Endian.h"

EEndian SystemEndian::msEndian = (ENDIANNESS == 'l' ? EEndian::eBIG_ENDIAN : EEndian::eLITTLE_ENDIAN);	// 决定系统大小端