#include "MyProject.h"
#include "Endian.h"

EEndian SystemEndian::msEndian = ENDIANNESS == 'l' ? eBIG_ENDIAN : eLITTLE_ENDIAN;	// 决定系统大小端