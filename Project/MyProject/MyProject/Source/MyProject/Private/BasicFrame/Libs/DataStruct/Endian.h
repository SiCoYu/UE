#ifndef __EEndian_H
#define __EEndian_H

/**
 * @brief 系统大小端定义
 */
enum EEndian
{
	eBIG_ENDIAN,         // 大端
	eLITTLE_ENDIAN,      // 小端
};

static union { char c[4]; unsigned long mylong; } endian_test = { { 'l', '?', '?', 'b' } };
#define ENDIANNESS ((char)endian_test.mylong)	// (如果ENDIANNESS == 'l',是字母'l'，不是数字'1'，表示系统为little endian,'b'表示big endian )

class SystemEndian
{
public:
	static EEndian msEndian;
};

#endif