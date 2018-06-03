#include "MyProject.h"
#include "MEndian.h"

MY_BEGIN_NAMESPACE(MyNS)

MEndian SystemEndian::msEndian = (ENDIANNESS == 'l' ? MEndian::eBIG_ENDIAN : MEndian::eLITTLE_ENDIAN);	// 决定系统大小端

MY_END_NAMESPACE