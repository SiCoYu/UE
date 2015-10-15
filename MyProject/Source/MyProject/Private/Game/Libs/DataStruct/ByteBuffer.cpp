#include "MyProject.h"
#include "ByteBuffer.h"

#include <sstream>
#include "DynBufResizePolicy.h"

void ByteBufferException::PrintPosError() const
{
	
}

// constructor
ByteBuffer::ByteBuffer(size_t initCapacity, size_t maxCapacity) : m_pos(0)
{
	m_dynBuff = new DynBuffer<char>(initCapacity, maxCapacity);
	m_sysEndian = eSys_LITTLE_ENDIAN;		// 默认是小端
}

ByteBuffer::~ByteBuffer()
{
	if (m_dynBuff)
	{
		delete m_dynBuff;
	}
}

void ByteBuffer::setEndian(SysEndian endian)
{
	m_sysEndian = endian;
}

void ByteBuffer::clear()
{
	m_dynBuff->m_size = 0;
	m_pos = 0;
}

// 放入的值一定和系统大小端一样的
template <typename T>
void ByteBuffer::put(size_t pos, T value)
{
	if (sSysEndian != m_sysEndian)
	{
		EndianConvert(value);
	}
	put(pos, (uint8*)&value, sizeof(value));
}

ByteBuffer& ByteBuffer::writeUnsignedInt8(uint8 value)
{
	append<uint8>(value);
	return *this;
}

ByteBuffer& ByteBuffer::writeUnsignedInt16(uint16 value)
{
	append<uint16>(value);
	return *this;
}

ByteBuffer& ByteBuffer::writeUnsignedInt32(uint32 value)
{
	append<uint32>(value);
	return *this;
}

ByteBuffer& ByteBuffer::writeUnsignedInt64(uint64 value)
{
	append<uint64>(value);
	return *this;
}

// signed as in 2e complement
ByteBuffer& ByteBuffer::writeInt8(int8 value)
{
	append<int8>(value);
	return *this;
}

ByteBuffer& ByteBuffer::writeInt16(int16 value)
{
	append<int16>(value);
	return *this;
}

ByteBuffer& ByteBuffer::writeInt32(int32 value)
{
	append<int32>(value);
	return *this;
}

ByteBuffer& ByteBuffer::writeInt64(int64 value)
{
	append<int64>(value);
	return *this;
}

// floating points
ByteBuffer& ByteBuffer::writeFloat(float value)
{
	append<float>(value);
	return *this;
}

ByteBuffer& ByteBuffer::writeDouble(double value)
{
	append<double>(value);
	return *this;
}

// 写入 UTF-8 字符串，并且字符串中有 '\0' ，自己不用单独添加
ByteBuffer& ByteBuffer::writeMultiByte(const std::string& value, size_t len)
{
	if (len > value.length())
	{
		append((uint8 const*)value.c_str(), value.length());
		append(len - value.length());
	}
	else
	{
		append((uint8 const*)value.c_str(), len);
	}
	return *this;
}

// 不能使用strlen 之类的字符串函数，因为 str 中可能有 '\0'
ByteBuffer& ByteBuffer::writeBytes(const char* str, size_t startPos, size_t len)
{
	if (str)
	{
		append(str + startPos, len);
	}
	else
	{
		append(len);
	}
	return *this;
}

ByteBuffer& ByteBuffer::readBoolean(bool& value)
{
	value = read<char>() > 0 ? true : false;
	return *this;
}

ByteBuffer& ByteBuffer::readUnsignedInt8(uint8& value)
{
	value = read<uint8>();
	return *this;
}

ByteBuffer& ByteBuffer::readUnsignedInt16(uint16& value)
{
	value = read<uint16>();
	return *this;
}

ByteBuffer& ByteBuffer::readUnsignedInt32(uint32& value)
{
	value = read<uint32>();
	return *this;
}

ByteBuffer& ByteBuffer::readUnsignedInt64(uint64& value)
{
	value = read<uint64>();
	return *this;
}

// signed as in 2e complement
ByteBuffer& ByteBuffer::readInt8(int8& value)
{
	value = read<int8>();
	return *this;
}

ByteBuffer& ByteBuffer::readInt16(int16& value)
{
	value = read<int16>();
	return *this;
}

ByteBuffer& ByteBuffer::readInt32(int32& value)
{
	value = read<int32>();
	return *this;
}

ByteBuffer& ByteBuffer::readInt64(int64& value)
{
	value = read<int64>();
	return *this;
}

ByteBuffer& ByteBuffer::readFloat(float& value)
{
	value = read<float>();
	return *this;
}

ByteBuffer& ByteBuffer::readDouble(double& value)
{
	value = read<double>();
	return *this;
}

ByteBuffer& ByteBuffer::readMultiByte(std::string& value, size_t len, MEncode::MEncode encode)
{
	value.clear();
	if (len)		// 如果不为 0 ，就读取指定数量
	{
		size_t readNum = 0;	// 已经读取的数量
		while (getPos() < getSize() && readNum < len) // prevent crash at wrong string format in packet
		{
			char c = read<char>();
			value += c;
			++readNum;
		}
	}
	else				// 如果为 0 ，就一直读取，直到遇到第一个 '\0'
	{
		while (getPos() < getSize()) // prevent crash at wrong string format in packet
		{
			char c = read<char>();
			if (c == 0)
				break;
			value += c;
		}
	}

	return *this;
}

ByteBuffer& ByteBuffer::readMultiByte(char* value, size_t len, MEncode::MEncode encode)
{
	size_t readNum = 0;	// 已经读取的数量
	char c = 0;
	if (len)		// 如果不为 0 ，就读取指定数量
	{
		while (getPos() < getSize() && readNum < len)                         // prevent crash at wrong string format in packet
		{
			c = read<char>();
			value[readNum] = c;
			++readNum;
		}
	}
	else				// 如果为 0 ，就一直读取，直到遇到第一个 '\0'
	{
		while (getPos() < getSize()) // prevent crash at wrong string format in packet
		{
			c = read<char>();
			if (c == 0)
			{
				break;
			}
			value[readNum] = c;
			++readNum;
		}
	}

	return *this;
}

template<class T>
ByteBuffer& ByteBuffer::readUnused(MUnused<T> const&)
{
	read_skip<T>();
	return *this;
}

uint8 ByteBuffer::operator[](size_t pos) const
{
	return read<uint8>(pos);
}

size_t ByteBuffer::getPos() const 
{ 
	return m_pos; 
}

size_t ByteBuffer::setPos(size_t pos_)
{
	m_pos = pos_;
	return m_pos;
}

uint32 ByteBuffer::getBytesAvailable()
{
	return (m_dynBuff->getSize() - m_pos);
}

void ByteBuffer::incPosDelta(int delta)
{
	m_pos += delta;
}

void ByteBuffer::decPosDelta(int delta)
{
	m_pos -= delta;
}

// 根据大小跳过
void ByteBuffer::read_skip(size_t skip)
{
	if (m_pos + skip > getSize())
	{
		throw ByteBufferException(false, m_pos, skip, getSize());
	}
	m_pos += skip;
}

// 根据大小跳过
void ByteBuffer::write_skip(size_t skip)
{
	append(skip);
}

// 根据类型跳过
template<typename T>
void ByteBuffer::read_skip()
{
	read_skip(sizeof(T));
}

template<typename T>
void ByteBuffer::write_skip()
{
	write_skip(sizeof(T));
}

template <typename T>
T ByteBuffer::read()
{
	T r = read<T>(m_pos);
	readAddPos(sizeof(T));
	return r;
}

// 读取出来的一定是和系统大小端一样的
template <typename T>
T ByteBuffer::read(size_t pos) const
{
	if (pos + sizeof(T) > getSize())
		throw ByteBufferException(false, pos, sizeof(T), getSize());
	T val = *((T const*)&m_dynBuff->m_buff[pos]);
	if (sSysEndian != m_sysEndian)
	{
		EndianConvert(val);
	}
	return val;
}

void ByteBuffer::read(uint8* dest, size_t len)
{
	if (m_pos + len > getSize())
	{
		throw ByteBufferException(false, m_pos, len, getSize());
	}
	memcpy(dest, &m_dynBuff->m_buff[m_pos], len);
	readAddPos(len);
}

const uint8* ByteBuffer::getBuff() const
{
	return (uint8*)m_dynBuff->m_buff;
}

DynBuffer* ByteBuffer::getDynBuff()
{
	return m_dynBuff;
}

size_t ByteBuffer::getSize() const
{
	if (m_dynBuff != nullptr)
	{
		return m_dynBuff->m_size;
	}

	return 0;
}

void ByteBuffer::setSize(size_t len)
{
	m_dynBuff->setSize(len);
}

size_t ByteBuffer::getLength()
{
	return this->getSize();
}

bool ByteBuffer::empty() const
{
	return m_dynBuff->m_size == 0;
}

size_t ByteBuffer::capacity()
{
	return m_dynBuff->m_iCapacity;
}

size_t ByteBuffer::maxCapacity()
{
	return m_dynBuff->m_iMaxCapacity;
}

void ByteBuffer::readAddPos(int delta)
{
	m_pos += delta;
}

void ByteBuffer::writeAddPos(int delta)
{
	m_pos += delta;
	m_dynBuff->m_size += delta;
}

void ByteBuffer::setCapacity(std::size_t newCapacity)
{
	m_dynBuff->setCapacity(newCapacity);
}

/**
*@brief 能否添加 num 长度的数据
*/
bool ByteBuffer::canAddData(uint32 num)
{
	return m_dynBuff->canAddData(num);
}

// 在最后添加
void ByteBuffer::append(const std::string& str)
{
	append((uint8 const*)str.c_str(), str.size() + 1);
}

void ByteBuffer::append(const char* src, size_t cnt)
{
	return append((const uint8*)src, cnt);
}

template<class T>
void ByteBuffer::append(const T* src, size_t cnt)
{
	return append((const uint8*)src, cnt * sizeof(T));
}

void ByteBuffer::append(const uint8* src, size_t cnt)
{
	if (!cnt)
	{
		return;
	}

	if (!canAddData(cnt))
	{
		uint32 closeSize = DynBufResizePolicy::getCloseSize(cnt + getSize(), capacity(), maxCapacity());
		setCapacity(closeSize);
	}
	//memcpy(&m_pStorageBuffer->m_storage[m_pos], src, cnt);
	memmove(&m_dynBuff->m_buff[m_pos], src, cnt);	// 同一块内存方式覆盖
	writeAddPos(cnt);
}

// 仅仅移动写指针，并不添加内容
void ByteBuffer::append(size_t cnt)
{
	if (!cnt)
	{
		return;
	}

	if (!canAddData(cnt))
	{
		uint32 closeSize = DynBufResizePolicy::getCloseSize(cnt + getSize(), capacity(), maxCapacity());
		setCapacity(closeSize);
	}
	writeAddPos(cnt);
}

void ByteBuffer::append(const ByteBuffer& buffer)
{
	if (buffer.getPos())
	{
		append(buffer.getBuff(), buffer.getSize());
	}
}

void ByteBuffer::put(size_t pos, const uint8* src, size_t cnt)
{
	if (!canAddData(cnt))
	{
		throw ByteBufferException(true, pos, cnt, getSize());
	}
	memcpy(&m_dynBuff->m_buff[pos], src, cnt);
}

char* ByteBuffer::rd_ptr()
{
	return m_dynBuff->m_buff + m_pos;
}

size_t ByteBuffer::avaliableBytes()
{
	return m_dynBuff->m_size - m_pos;
}

void ByteBuffer::print_storage() const
{
    std::ostringstream ss;
    ss <<  "STORAGE_SIZE: " << getSize() << "\n";
    ss << "         ";

    for (size_t i = 0; i < getSize(); ++i)
        ss << uint32(read<uint8>(i)) << " - ";
}

void ByteBuffer::textlike() const
{
    std::ostringstream ss;
    ss <<  "STORAGE_SIZE: " << getSize() << "\n";

    ss << "         ";

    for (size_t i = 0; i < getSize(); ++i)
        ss << read<uint8>(i);
}

void ByteBuffer::hexlike() const
{
    std::ostringstream ss;
    ss <<  "STORAGE_SIZE: " << getSize() << "\n";

    ss << "         ";

    size_t j = 1, k = 1;

    for (size_t i = 0; i < getSize(); ++i)
    {
        if ((i == (j * 8)) && ((i != (k * 16))))
        {
            ss << "| ";
            ++j;
        }
        else if (i == (k * 16))
        {
            ss << "\n";

            ss << "         ";

            ++k;
            ++j;
        }

        char buf[4];
        _snprintf(buf, 4, "%02X", read<uint8>(i));
        ss << buf << " ";
    }
}

void ByteBuffer::writeFile(FILE* file)
{
	fwrite((void*)&m_dynBuff->m_buff[0], sizeof(char), this->getSize(), file);
}

template <typename T>
void ByteBuffer::append(T value)
{
	if (sSysEndian != m_sysEndian)
	{
		EndianConvert(value);
	}
	append((uint8*)&value, sizeof(value));
}

template<>
inline void ByteBuffer::read_skip<char*>()
{
	std::string temp;
	this->readMultiByte(temp, 0);
}

template<>
inline void ByteBuffer::read_skip<char const*>()
{
	read_skip<char*>();
}

template<>
inline void ByteBuffer::read_skip<std::string>()
{
	read_skip<char*>();
}