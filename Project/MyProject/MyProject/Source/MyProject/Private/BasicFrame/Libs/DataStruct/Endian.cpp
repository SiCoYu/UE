#include "MyProject.h"
#include "Endian.h"

EEndian SystemEndian::m_sEndian = ENDIANNESS == 'l' ? eBIG_ENDIAN : eLITTLE_ENDIAN;	// 决定系统大小端