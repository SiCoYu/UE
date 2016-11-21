#ifndef __ENDIAN_H
#define __ENDIAN_H

/**
 * @brief ϵͳ��С�˶���
 */
enum EEndian
{
	eBIG_ENDIAN,         // ���
	eLITTLE_ENDIAN,      // С��
};

static union { char c[4]; unsigned long mylong; } endian_test = { { 'l', '?', '?', 'b' } };
#define ENDIANNESS ((char)endian_test.mylong)	// (���ENDIANNESS == 'l',����ĸ'l'����������'1'����ʾϵͳΪlittle endian,'b'��ʾbig endian )

class SystemEndian
{
public:
	static EEndian m_sEndian;
};

#endif