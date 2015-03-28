#ifndef __BYTEBUFFER_H
#define __BYTEBUFFER_H

#include <vector>
#include <list>
#include <string>
#include <map>

#include "MyProject.h"
#include "ByteConverter.h"
#include "Error.h"
#include "SystemEndian.h"
#include "MStorageBuffer.h"
#include "MEncode.h"

class ByteBufferException
{
    public:
        ByteBufferException(bool _add, size_t _pos, size_t _esize, size_t _size)
            : add(_add), pos(_pos), esize(_esize), size(_size)
        {
            PrintPosError();
        }

        void PrintPosError() const;
    private:
        bool add;
        size_t pos;
        size_t esize;
        size_t size;
};

template<class T>
struct MUnused
{
    MUnused() {}
};

class ByteBuffer
{
protected:
	SysEndian m_sysEndian;

public:
	// constructor
	ByteBuffer(size_t len);
	~ByteBuffer();

	void setEndian(SysEndian endian);
	void clear();

	// 放入的值一定和系统大小端一样的
	template <typename T>
	void put(size_t pos, T value);

	ByteBuffer& writeUnsignedInt8(uint8 value);
	ByteBuffer& writeUnsignedInt16(uint16 value);
	ByteBuffer& writeUnsignedInt32(uint32 value);
	ByteBuffer& writeUnsignedInt64(uint64 value);
	// signed as in 2e complement
	ByteBuffer& writeInt8(int8 value);
	ByteBuffer& writeInt16(int16 value);
	ByteBuffer& writeInt32(int32 value);
	ByteBuffer& writeInt64(int64 value);
	// floating points
	ByteBuffer& writeFloat(float value);
	ByteBuffer& writeDouble(double value);
	// 写入 UTF-8 字符串，并且字符串中有 '\0' ，自己不用单独添加
	ByteBuffer& writeMultiByte(const std::string& value, size_t len);
	//ByteBuffer& writeMultiByte(const char* str, size_t len)
	ByteBuffer& writeBytes(const char* str, size_t startPos, size_t len);
	ByteBuffer& readBoolean(bool& value);
	ByteBuffer& readUnsignedInt8(uint8& value);
	ByteBuffer& readUnsignedInt16(uint16& value);
	ByteBuffer& readUnsignedInt32(uint32& value);
	ByteBuffer& readUnsignedInt64(uint64& value);
	// signed as in 2e complement
	ByteBuffer& readInt8(int8& value);
	ByteBuffer& readInt16(int16& value);
	ByteBuffer& readInt32(int32& value);
	ByteBuffer& readInt64(int64& value);
	ByteBuffer& readFloat(float& value);
	ByteBuffer& readDouble(double& value);
	ByteBuffer& readMultiByte(std::string& value, size_t len, MEncode::MEncode encode = MEncode::eUTF8);
	ByteBuffer& readMultiByte(char* value, size_t len, MEncode::MEncode encode = MEncode::eUTF8);

	template<class T>
	ByteBuffer& readUnused(MUnused<T> const&);

	uint8 operator[](size_t pos) const;
	size_t pos() const;
	size_t pos(size_t pos_);

	// 根据类型跳过
	template<typename T>
	void read_skip();

	// 根据大小跳过
	void read_skip(size_t skip);

	template<typename T>
	void write_skip();

	// 根据大小跳过
	void write_skip(size_t skip);

	template <typename T>
	T read();

	// 读取出来的一定是和系统大小端一样的
	template <typename T>
	T read(size_t pos) const;

	void read(uint8* dest, size_t len);
	const uint8* getStorage() const;
	size_t size() const;
	void setSize(size_t len);
	bool empty() const;
	size_t capacity();
	void readAddPos(int delta);
	void writeAddPos(int delta);
	void setCapacity(std::size_t newCapacity);

	/**
	*@brief 能否添加 num 长度的数据
	*/
	bool canAddData(uint32 num);
	// 在最后添加
	void append(const std::string& str);
	void append(const char* src, size_t cnt);

	template<class T>
	void append(const T* src, size_t cnt);

	void append(const uint8* src, size_t cnt);
	// 仅仅移动写指针，并不添加内容
	void append(size_t cnt);
	void append(const ByteBuffer& buffer);
	void put(size_t pos, const uint8* src, size_t cnt);
	char* rd_ptr();
	size_t avaliableBytes();
	void print_storage() const;
	void textlike() const;
	void hexlike() const;
	void writeFile(FILE* file);

private:
	// 添加的一定是和系统大小端相同的
	// limited for internal use because can "append" any unexpected type (like pointer and etc) with hard detection problem
	template <typename T>
	void append(T value);

protected:
	size_t m_pos;		// 读取写入位置
	MStorageBuffer* m_pStorageBuffer;
	char m_encryptKey[8];
	char m_decryptKey[8];
};


#endif