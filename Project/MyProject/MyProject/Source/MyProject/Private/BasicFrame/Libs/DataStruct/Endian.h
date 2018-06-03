#ifndef __EEndian_H
#define __EEndian_H

/**
 * @brief ϵͳ��С�˶���
 */
enum EEndian
{
	eBIG_ENDIAN,         // ���
	eLITTLE_ENDIAN,      // С��
};

static union
{ 
	char c[4]; 
	unsigned long mylong; 
} endian_test = { { 'l', '?', '?', 'b' } };

// (���ENDIANNESS == 'l',����ĸ'l'����������'1'����ʾϵͳΪlittle endian,'b'��ʾbig endian )
#define ENDIANNESS ((char)endian_test.mylong)

class SystemEndian
{
public:
	static EEndian msEndian;
};

#endif