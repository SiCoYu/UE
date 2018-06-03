#ifndef __MEndian_H
#define __MEndian_H

/**
 * @brief 系统大小端定义
 */
enum class MEndian
{
	eBIG_ENDIAN,         // 大端
	eLITTLE_ENDIAN,      // 小端
};

static union
{ 
	char c[4]; 
	unsigned long mylong; 
} endian_test = { { 'l', '?', '?', 'b' } };

// (如果ENDIANNESS == 'l',是字母'l'，不是数字'1'，表示系统为little endian,'b'表示big endian )
#define ENDIANNESS ((char)endian_test.mylong)

class SystemEndian
{
public:
	static MEndian msEndian;
};

#endif