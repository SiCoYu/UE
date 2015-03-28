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

	// �����ֵһ����ϵͳ��С��һ����
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
	// д�� UTF-8 �ַ����������ַ������� '\0' ���Լ����õ������
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

	// ������������
	template<typename T>
	void read_skip();

	// ���ݴ�С����
	void read_skip(size_t skip);

	template<typename T>
	void write_skip();

	// ���ݴ�С����
	void write_skip(size_t skip);

	template <typename T>
	T read();

	// ��ȡ������һ���Ǻ�ϵͳ��С��һ����
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
	*@brief �ܷ���� num ���ȵ�����
	*/
	bool canAddData(uint32 num);
	// ��������
	void append(const std::string& str);
	void append(const char* src, size_t cnt);

	template<class T>
	void append(const T* src, size_t cnt);

	void append(const uint8* src, size_t cnt);
	// �����ƶ�дָ�룬�����������
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
	// ��ӵ�һ���Ǻ�ϵͳ��С����ͬ��
	// limited for internal use because can "append" any unexpected type (like pointer and etc) with hard detection problem
	template <typename T>
	void append(T value);

protected:
	size_t m_pos;		// ��ȡд��λ��
	MStorageBuffer* m_pStorageBuffer;
	char m_encryptKey[8];
	char m_decryptKey[8];
};


#endif