#ifndef __MByteBuffer_H
#define __MByteBuffer_H

#include <vector>
#include <list>
#include <string>
#include <map>

#include "MyProject.h"
#include "ByteConverter.h"
#include "Error.h"
#include "SystemEndian.h"
#include "DynBuffer.h"
#include "MEncode.h"
#include "BufferCV.h"

template <class T> class DynBuffer;

class MByteBuffer
{
public:
	// int m_id;        // ����ʹ��
	// bool m_startTest;        // ��ʼ����ʹ��

protected:
	DynBuffer<char>* m_dynBuff;
	uint32 m_pos;          // ��ǰ���Զ�ȡ��λ������
	SysEndian m_endian;          // ���С��

	char m_padBytes[8];

	//LuaCSBridgeByteBuffer m_luaCSBridgeByteBuffer;        // Lua �еĻ�����

public:
	MByteBuffer(uint32 initCapacity = BufferCV::INIT_CAPACITY, uint32 maxCapacity = BufferCV::MAX_CAPACITY, SysEndian endian = SysEndian::eSys_LITTLE_ENDIAN);
	DynBuffer<char>* getDynBuff();
	uint32 getBytesAvailable();
	SysEndian getEndian();
	void setEndian(SysEndian value);
	uint32 getLength();
	void setLength(uint32 value);
	void setPos(uint32 pos);
	uint32 getPos();
	//LuaCSBridgeByteBuffer* getLuaCSBridgeByteBuffer();
	//void setLuaCSBridgeByteBuffer(LuaCSBridgeByteBuffer* value);
	void clear();

protected:
	// ����Ƿ����㹻�Ĵ�С������չ
	bool canWrite(uint32 delta);
	// ��ȡ���
	bool canRead(uint32 delta);
	void extendDeltaCapicity(uint32 delta);
	void advPos(uint32 num);
	void advPosAndLen(uint32 num);

public:
	void incPosDelta(int delta);        // ��� pos delta ����
	void decPosDelta(int delta);		// ���� pos delta ����
	// ѹ��
	//uint32 compress(uint32 len_ = 0, CompressionAlgorithm algorithm = CompressionAlgorithm.ZLIB);
	// ��ѹ
	//uint uncompress(uint32 len_ = 0, CompressionAlgorithm algorithm = CompressionAlgorithm.ZLIB);
	// ���ܣ�ʹ�� des �Գ����ּ����㷨������8�ֽڲ��룬���ܻᵼ�±䳤
	//uint encrypt(CryptContext cryptContext, uint len_ = 0);
	// ���ܣ����ڱ��� 8 �ֽڶ������
	//void decrypt(CryptContext cryptContext, uint len_ = 0);
	MByteBuffer& readBoolean(bool& tmpBool);
	MByteBuffer& readInt8(char& tmpByte);
	MByteBuffer& readUnsignedInt8(char& tmpByte);
	MByteBuffer& readInt16(short& tmpShort);
	MByteBuffer& readUnsignedInt16(uint16& tmpUshort);
	MByteBuffer& readInt32(int& tmpInt);
	MByteBuffer& readUnsignedInt32(uint32& tmpUint);
	MByteBuffer& readInt64(long& tmpLong);
	MByteBuffer& readUnsignedInt64(unsigned long& tmpUlong);
	MByteBuffer& readFloat(float& tmpFloat);
	MByteBuffer& readDouble(double& tmpDouble);
	MByteBuffer& readMultiByte(std::string& tmpStr, uint32 len, MEncode charSet);
	// ������ֽڶ�ȡ��û�д�С�˵�����
	MByteBuffer readBytes(char* tmpBytes, uint32 len);
	// ���Ҫʹ�� writeInt8 ��ֱ��ʹ�� writeMultiByte �������
	void writeInt8(char value);
	void writeUnsignedInt8(uint8 value);
	void writeInt16(short value);
	void writeUnsignedInt16(uint16 value);
	void writeInt32(int value);
	void writeUnsignedInt32(uint32 value, bool bchangeLen = true);
	void writeInt64(long value);
	void writeUnsignedInt64(unsigned long value);
	void writeFloat(float value);
	void writeDouble(double value);
	// д���ֽڣ� bchangeLen �Ƿ�ı䳤��
	void writeBytes(char* value, uint32 start, uint32 len, bool bchangeLen = true);
	// д���ַ���
	void writeMultiByte(std::string& value, MEncode charSet, int len);

protected:
	// �滻�Ѿ��е�һ������
	void replace(char* srcBytes, uint32 srcStartPos = 0, uint32 srclen_ = 0, uint32 destStartPos = 0, uint32 destlen_ = 0);

public:
	void insertUnsignedInt32(uint32 value);
	MByteBuffer& readUnsignedLongByOffset(unsigned long& tmpUlong, uint32 offset);
	//bool check();
};

#endif