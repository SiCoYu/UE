#ifndef __MByteBuffer_H
#define __MByteBuffer_H

#include <vector>
#include <list>
#include <string>
#include <map>

#include "MyProject.h"
#include "Error.h"
#include "Endian.h"
#include "DynBuffer.h"
#include "MEncode.h"
#include "BufferCV.h"
#include "IDispatchObject.h"
#include "GObject.h"
#include "PlatformDefine.h"

MY_BEGIN_NAMESPACE(MyNS)

template <class T> class DynBuffer;

class MByteBuffer : public GObject, public IDispatchObject
{
public:
	// int mId;        // ����ʹ��
	// bool m_startTest;        // ��ʼ����ʹ��

protected:
	DynBuffer<char>* mDynBuffer;
	uint32 mPos;          // ��ǰ���Զ�ȡ��λ������
	EEndian mEndian;          // ���С��

	char m_padBytes[8];

	//LuaCSBridgeByteBuffer m_luaCSBridgeByteBuffer;        // Lua �еĻ�����

public:
	MByteBuffer(
		uint32 initCapacity = BufferCV::INIT_CAPACITY, 
		uint32 maxCapacity = BufferCV::MAX_CAPACITY, 
		EEndian endian = eLITTLE_ENDIAN
	);
	DynBuffer<char>* getDynBuffer();
	uint32 getBytesAvailable();
	EEndian getEndian();
	void setEndian(EEndian value);
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

	void incLenDelta(int delta);
	void decLenDelta(int delta);
	// ѹ��
	//uint32 compress(uint32 len_ = 0, CompressionAlgorithm algorithm = CompressionAlgorithm.ZLIB);
	// ��ѹ
	//uint uncompress(uint32 len_ = 0, CompressionAlgorithm algorithm = CompressionAlgorithm.ZLIB);
	// ���ܣ�ʹ�� des �Գ����ּ����㷨������8�ֽڲ��룬���ܻᵼ�±䳤
	//uint encrypt(CryptContext cryptContext, uint len_ = 0);
	// ���ܣ����ڱ��� 8 �ֽڶ������
	//void decrypt(CryptContext cryptContext, uint len_ = 0);
	MByteBuffer& readBoolean(bool& tmpBool);
	MByteBuffer& readInt8(int8& tmpByte);
	MByteBuffer& readUnsignedInt8(uint8& tmpByte);
	MByteBuffer& readInt16(int16& tmpShort);
	MByteBuffer& readUnsignedInt16(uint16& tmpUshort);
	MByteBuffer& readInt32(int32& tmpInt);
	MByteBuffer& readUnsignedInt32(uint32& tmpUint);
	MByteBuffer& readInt64(int64& tmpLong);
	MByteBuffer& readUnsignedInt64(uint64& tmpUlong);
	MByteBuffer& readFloat(float& tmpFloat);
	MByteBuffer& readDouble(double& tmpDouble);
	MByteBuffer& readMultiByte(std::string& tmpStr, uint32 len, MEncode charSet);
	// ������ֽڶ�ȡ��û�д�С�˵�����
	MByteBuffer& readBytes(char* tmpBytes, uint32 len);
	// ���Ҫʹ�� writeInt8 ��ֱ��ʹ�� writeMultiByte �������
	void writeInt8(int8 value);
	void writeUnsignedInt8(uint8 value);
	void writeInt16(int16 value);
	void writeUnsignedInt16(uint16 value);
	void writeInt32(int32 value);
	void writeUnsignedInt32(uint32 value, bool bchangeLen = true);
	void writeInt64(int64 value);
	void writeUnsignedInt64(uint64 value);
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
	MByteBuffer& readUnsignedLongByOffset(uint64& tmpUlong, uint32 offset);
	//bool check();
};

MY_END_NAMESPACE

#endif