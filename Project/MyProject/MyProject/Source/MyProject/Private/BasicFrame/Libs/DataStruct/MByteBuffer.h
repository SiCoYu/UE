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
	// int mId;        // 测试使用
	// bool m_startTest;        // 开始测试使用

protected:
	DynBuffer<char>* mDynBuffer;
	uint32 mPos;          // 当前可以读取的位置索引
	EEndian mEndian;          // 大端小端

	char m_padBytes[8];

	//LuaCSBridgeByteBuffer m_luaCSBridgeByteBuffer;        // Lua 中的缓冲区

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
	// 检查是否有足够的大小可以扩展
	bool canWrite(uint32 delta);
	// 读取检查
	bool canRead(uint32 delta);
	void extendDeltaCapicity(uint32 delta);
	void advPos(uint32 num);
	void advPosAndLen(uint32 num);

public:
	void incPosDelta(int delta);        // 添加 pos delta 数量
	void decPosDelta(int delta);		// 减少 pos delta 数量

	void incLenDelta(int delta);
	void decLenDelta(int delta);
	// 压缩
	//uint32 compress(uint32 len_ = 0, CompressionAlgorithm algorithm = CompressionAlgorithm.ZLIB);
	// 解压
	//uint uncompress(uint32 len_ = 0, CompressionAlgorithm algorithm = CompressionAlgorithm.ZLIB);
	// 加密，使用 des 对称数字加密算法，加密8字节补齐，可能会导致变长
	//uint encrypt(CryptContext cryptContext, uint len_ = 0);
	// 解密，现在必须 8 字节对齐解密
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
	// 这个是字节读取，没有大小端的区别
	MByteBuffer& readBytes(char* tmpBytes, uint32 len);
	// 如果要使用 writeInt8 ，直接使用 writeMultiByte 这个函数
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
	// 写入字节， bchangeLen 是否改变长度
	void writeBytes(char* value, uint32 start, uint32 len, bool bchangeLen = true);
	// 写入字符串
	void writeMultiByte(std::string& value, MEncode charSet, int len);

protected:
	// 替换已经有的一段数据
	void replace(char* srcBytes, uint32 srcStartPos = 0, uint32 srclen_ = 0, uint32 destStartPos = 0, uint32 destlen_ = 0);

public:
	void insertUnsignedInt32(uint32 value);
	MByteBuffer& readUnsignedLongByOffset(uint64& tmpUlong, uint32 offset);
	//bool check();
};

MY_END_NAMESPACE

#endif