#ifndef __MEndian_H
#define __MEndian_H

/**
 * @brief ϵͳ��С�˶���
 */
enum class MEndian
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
	static MEndian msEndian;
};

#endif