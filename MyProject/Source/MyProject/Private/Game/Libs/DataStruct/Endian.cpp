#include "MyProject.h"
#include "Endian.h"

EEndian SystemEndian::m_sEndian = ENDIANNESS == 'l' ? eBIG_ENDIAN : eLITTLE_ENDIAN;	// ����ϵͳ��С��